/*
   Angle meter using a MMA8452 sensor and ESP01
   f5soh@free.fr - 2019

   Parts from:
   https://github.com/f5mmx/aeromodeling-throw-meter
   https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer/examples/CaptivePortalAdvanced

 */

#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#include <Wire.h>
#include <MMA8452.h> // MMA8452 library            from https://github.com/akupila/Arduino-MMA8452


#include "index.h" // HTML webpage contents with javascripts

#ifndef APSSID
#define APSSID "debat"
#define APPSK  "1234"
#endif

const char *softAP_ssid     = APSSID;
const char *softAP_password = APPSK;

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;

/* hostname for mDNS. Should work at least on windows. Try http://debat.local */
const char *myHostname = "debat";

// Web server
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

// Http client
HTTPClient http;

/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

/* Don't set this wifi credentials. They are configurated at runtime and stored on EEPROM */
char ssid[32]     = "";
char password[32] = "";
char softAP_ssid_eeprom[32] = "";

/** Should I connect to WLAN asap? */
boolean connect;

/** Last time I tried to connect to WLAN */
unsigned long lastConnectTry = 0;

/** Current WLAN status */
unsigned int status = WL_IDLE_STATUS;

// 0 to 20.5dBm
float outputPower   = 0;

// initial value: device is master (AP) by default
bool is_master = true;
String slaveDeviceIP = "";
String data;
unsigned long lastSent;
unsigned long lastReceived;
unsigned long sendEvery_ms = 300;
unsigned long timeOut_ms = 1500;

MMA8452 mma;
double ref_angle, last_angle;
float angle_web, throw_web, minthrow_web = 0, maxthrow_web = 0;
String str_angle2_web = "0", str_throw2_web = "0", str_minthrow2_web = "0", str_maxthrow2_web = "0", str_dual = "0";
int corde = 50, min_setting = 0, max_setting = 0, xoff_calibration = 0, yoff_calibration = 0, zoff_calibration = 0;
float x_offset = 0, y_offset = 0, z_offset = 0;
enum { X_AXIS = 0, Y_AXIS = 1, Z_AXIS = 2 };
byte axis;
bool invert_angle = false;

float x, y, z; // g measurements

#define NUM_SAMPLES 30
#define ALPHA       0.7

/**
 * Configure sensor and server
 */
void setup()
{
  // Configure I2C
  Wire.begin(0, 2); // Wire.begin([SDA], [SCL])
  Wire.setClock(400000); // 400KHz

  Serial.begin(9600);
  Serial.println("I2C config done");

  // try to retrieve a custom softAP_ssid
  loadCredentials();
  if (strlen(softAP_ssid_eeprom) > 0) {
    softAP_ssid = softAP_ssid_eeprom;
  }

  bool use_password = true;

  // set WiFi to station mode and check if annother device is running as AP
  WiFi.mode(WIFI_STA);
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("no networks found");
    is_master = true;
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      if (WiFi.SSID(i) == softAP_ssid) {
        Serial.println("Master device found!");
        is_master    = false;
        use_password = (WiFi.encryptionType(i) != ENC_TYPE_NONE);
        break;
      }
      delay(100);
    }
  }

  if (!is_master) {
    Serial.println("Connecting to AP...");
    // Connect to the AP device already running
    if (use_password) {
      WiFi.begin(softAP_ssid, APPSK);
    } else {
      WiFi.begin(softAP_ssid);
    }
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(300);
    }
    Serial.println(" Connected!!!\r");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/setData", handleMasterData); // Receive request from master and change settings
    // server.on("/readData", handleValues);    // Send values to be displayed in webpage
  } else {
    Serial.println("Configuring access point...");
    delay(300);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP(softAP_ssid); // No password
    delay(500);
    Serial.println("AP IP address: ");
    Serial.print(WiFi.softAPIP());

    /* Setup the DNS server redirecting all the domains to the apIP */
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", apIP);

    server.on("/", handleRoot);
    server.on("/setData", handleData); // Receive request from webpage and change settings
    server.on("/setSlaveData", handleSlaveData); // Receive sensor data from slave
    server.on("/readData", handleValues); // Send values to be displayed in webpage (master and slave if any)
    server.on("/readSettings", handleSettings);
    server.on("/readSysData", handleSystemData);
    server.on("/wifi", handleWifi);
    server.on("/wifisave", handleWifiSave);
    server.on("/generate_204", handleRoot); // Android captive portal. Maybe not needed. Might be handled by notFound handler.
    server.on("/fwlink", handleRoot); // Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
    server.onNotFound(handleNotFound);
  }

  httpUpdater.setup(&server);
  server.begin();
  Serial.println("HTTP server started");

  // Will be set to min and save power
  WiFi.setOutputPower(outputPower);

  // Request WLAN connect if there is a SSID
  connect = strlen(ssid) > 0;

  // Sensor configuration
  mma.setDataRate(MMA_400hz);
  mma.setRange(MMA_RANGE_2G);
  mma.setLowNoiseMode(true);

  delay(500);

  init_angle();
}

void connectWifi()
{
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  int connRes = WiFi.waitForConnectResult();
  Serial.print("connRes: ");
  Serial.println(connRes);
}

/**
 * Main loop
 */
void loop()
{
  // Do measurements, result is filtered
  // Take around 11ms per 30 samples
  float angle = read_angle();

  compute_values(angle);

  if (is_master) {
    if (connect) {
      Serial.println("Connect requested");
      connect = false;
      connectWifi();
      lastConnectTry = millis();
    }
    {
      unsigned int s = WiFi.status();
      if (s == 0 && millis() > (lastConnectTry + 60000)) {
        /* If WLAN disconnected and idle try to connect */
        /* Don't set retry time too low as retry interfere the softAP operation */
        connect = true;
      }
      if (status != s) { // WLAN status change
        Serial.print("Status: ");
        Serial.println(s);
        status = s;
        if (s == WL_CONNECTED) {
          /* Just connected to WLAN */
          Serial.println("");
          Serial.print("Connected to ");
          Serial.println(ssid);
          Serial.print("IP address: ");
          Serial.println(WiFi.localIP());

          // Setup MDNS responder
          if (!MDNS.begin(myHostname)) {
            Serial.println("Error setting up MDNS responder!");
          } else {
            Serial.println("mDNS responder started");
            // Add service to MDNS-SD
            MDNS.addService("http", "tcp", 80);
          }
        } else if (s == WL_NO_SSID_AVAIL) {
          WiFi.disconnect();
        }
      }
      if (s == WL_CONNECTED) {
        MDNS.update();
      }
    }

    // DNS
    dnsServer.processNextRequest();

    // Check if slave still here
    if ((millis() - lastReceived) > timeOut_ms) {
      str_dual = "0"; // One sensor from master
    } else {
      str_dual = "1"; // Dual sensor
    }
  } else {
    // Slave send data to master
    if ((millis() - lastSent) > sendEvery_ms) {
      prepareSlaveData();
      sendSlaveData();
      lastSent = millis();
    }
  }

  // Web server
  server.handleClient();
}

/** Send main webpage */
void handleRoot()
{
  // server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate", true);
  // server.sendHeader("Pragma", "no-cache", true);
  // server.sendHeader("Expires", "-1", true);
  server.send_P(200, "text/html", MAIN_page, sizeof(MAIN_page)); // Send Main page
}

/** Send values to page */
void handleValues()
{
  server.send(200, "text/plane", String(int(corde)) + ":" + \
              String(angle_web, 2) + ":" + \
              String(throw_web, 1) + ":" + \
              String(minthrow_web, 1) + ":" + \
              String(maxthrow_web, 1) + ":" + \
              str_angle2_web + ":" + \
              str_throw2_web + ":" + \
              str_minthrow2_web + ":" + \
              str_maxthrow2_web + ":" + \
              str_dual + ":" + \
              String(x, 4) + ":" + \
              String(y, 4) + ":" + \
              String(z, 4)
              );
}

/** Send settings */
void handleSettings()
{
  loadSettings();
  loadCalibrations();
  server.send(200, "text/plane", String(int(corde)) + ":" + \
              String(int(min_setting)) + ":" + \
              String(int(max_setting)) + ":" + \
              String(axis) + ":" + \
              String(int(xoff_calibration)) + ":" + \
              String(int(yoff_calibration)) + ":" + \
              String(int(zoff_calibration)));
}

/** Send system data */
void handleSystemData()
{
  String arduinover = ESP.getCoreVersion();
  String sdkver     = ESP.getSdkVersion();

  arduinover.replace("_", ".");
  server.send(200, "text/plane", String(ESP.getFreeHeap()) + ":" + sdkver.substring(0, 5) + ":" + arduinover + ":" + ESP.getSketchMD5().substring(0, 6));
}

/** Receive values from page */
void handleData()
{
  if (!is_master) {
    return;
  }
  axis  = server.arg("axis").toInt();
  corde = server.arg("chord").toInt();
  min_setting = server.arg("min").toInt();
  max_setting = server.arg("max").toInt();
  xoff_calibration = server.arg("xoff").toInt();
  yoff_calibration = server.arg("yoff").toInt();
  zoff_calibration = server.arg("zoff").toInt();
  x_offset = (float)xoff_calibration / 10000;
  y_offset = (float)yoff_calibration / 10000;
  z_offset = (float)zoff_calibration / 10000;

  // Serial.println("Cmd=" + server.arg("cmd"));
  // Serial.println("Chord=" + server.arg("chord"));
  // Serial.println("Min=" + server.arg("min"));
  // Serial.println("Max=" + server.arg("max"));
  // Serial.println("Xoff=" + String(x_offset, 4));
  // Serial.println("Yoff=" + String(y_offset, 4));
  // Serial.println("Zoff=" + String(z_offset, 4));

  switch (server.arg("cmd").toInt()) {
  case 200:
    invert_angle = false;
    break;
  case 201:
    invert_angle = true;
    break;
  case 202:
    sendToSlave(corde, axis, 202); // slave: invert_angle = false;
    break;
  case 203:
    sendToSlave(corde, axis, 203); // slave: invert_angle = true;
    break;
  case 301:
    saveSettings();
    break;
  case 302:
    loadSettings();
    break;
  case 303:
    reset_minmax();
    sendToSlave(corde, axis, 303);
    break;
  case 304:
    init_angle();
    sendToSlave(corde, axis, 304);
    break;
  case 305:
    saveCalibrations();
    break;
  case 306:
    loadCalibrations();
    break;
  }

  server.send(200, "text/plain", "Master Ok");
  server.client().stop();

  // send new values after setting change
  handleValues();
}

void prepareSlaveData()
{
  data  = "angle2=" + String(angle_web, 2);
  data += "&throw2=" + String(throw_web, 1);
  data += "&minthrow2=" + String(minthrow_web, 1);
  data += "&maxthrow2=" + String(maxthrow_web, 1);
  data += "&chord=" + String(int(corde));
  data += "&axis=" + String(axis);
  // Serial.println("- data stream: "+data);
}

void sendSlaveData()
{
  String serverURLData = "http://" + toStringIp(apIP) + "/setSlaveData";

  http.setTimeout(200);
  http.begin(serverURLData);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST(data);
  // http.writeToStream(&Serial);
  http.end();
}

void sendToSlave(int chord, byte axis, int cmd)
{
  String slaveURL = "http://" + slaveDeviceIP + "/setData";

  http.setTimeout(200);
  http.begin(slaveURL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("chord=" + String(int(chord)) + "&axis=" + String(axis) + "&cmd=" + String(int(cmd)));
  // http.writeToStream(&Serial);
  http.end();
  // Serial.println("sendToSlave " + slaveURL + " " + chord + "cmd:" + String(int(cmd)));
}

void handleMasterData()
{
  corde = server.arg("chord").toInt();
  axis  = server.arg("axis").toInt();

  switch (server.arg("cmd").toInt()) {
  case 202:
    invert_angle = false;
    break;
  case 203:
    invert_angle = true;
    break;
  case 303:
    reset_minmax();
    break;
  case 304:
    init_angle();
    break;
  }

  server.send(200, "text/plain", "Slave Ok");
  server.client().stop();

  // Serial.println("Received corde: " + String(corde) + " cmd=" + str);
}

// Handling the data from slave device
void handleSlaveData()
{
  lastReceived      = millis();
  if (slaveDeviceIP == "") {
    slaveDeviceIP = server.client().remoteIP().toString();
  }
  str_angle2_web    = server.arg("angle2");
  str_throw2_web    = server.arg("throw2");
  str_minthrow2_web = server.arg("minthrow2");
  str_maxthrow2_web = server.arg("maxthrow2");

  server.send(200, "text/plain", "Master Ok");
  server.client().stop();

  if ((server.arg("chord").toInt() != corde) || (server.arg("axis").toInt() != axis)) {
    delay(10);
    sendToSlave(corde, axis, 0);
  }
}

/** Wifi config page handler */
void handleWifi()
{
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  String Page;
  Page += F(
    "<html><head></head><body>"
    "<h1>Wifi config</h1><hr align='left' width='50%'>");
  if (server.client().localIP() == apIP) {
    Page += String(F("<p>You are connected through the soft AP: ")) + softAP_ssid + F("</p>");
  } else {
    Page += String(F("<p>You are connected through the wifi network: ")) + ssid + F("</p>");
  }
  Page +=
    String(F(
             "<table width='50%'><tr><th bgcolor='#99ff99' align='left'>SoftAP config</th><th bgcolor='#ff9900' align='left'>WLAN config</th></tr>\r\n"
             "<tr><td bgcolor='#99ff99'>SSID ")) + String(softAP_ssid) +
    F("</td><td bgcolor='#ff9900'>SSID ") + String(ssid) +
    F("</td></tr>\r\n<tr><td bgcolor='#99ff99'>IP ") + toStringIp(WiFi.softAPIP()) +
    F("</td><td bgcolor='#ff9900'>IP ") + toStringIp(WiFi.localIP()) +
    F("</td></tr>\r\n</table>"
      "\r\n<hr align='left' width='50%'>"
      "<table width='50%'><tr><th align='left'>WLAN list (refresh if any missing)</th></tr>");
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      Page += String(F("\r\n<tr><td bgcolor='#ff9900'>SSID ")) + WiFi.SSID(i) + ((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? F(" ") : F(" *")) + F(" (") + WiFi.RSSI(i) + F("dBm)</td></tr>");
    }
  } else {
    Page += F("<tr><td>No WLAN found</td></tr>");
  }
  Page += F(
    "</table>"
    "\r\n<hr align='left' width='50%'><form method='POST' action='wifisave'>"
    "<h4>Set custom AP SSID (default is 'debat'):</h4>"
    "<input type='text' placeholder='AP_SSID' name='s'/>"
    "<h4>Connect to network:</h4>"
    "<input type='text' placeholder='network' name='n'/>"
    "<br /><input type='password' placeholder='password' name='p'/>"
    "<br /><input type='submit' value='Store Wifi settings'/></form>"
    "<p>You may want to <a href='/'>return to the ESP Angle meter page</a>.</p>"
    "</body></html>");
  server.send(200, "text/html", Page);
  server.client().stop(); // Stop is needed because we sent no content length
}

/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave()
{
  Serial.println("Wifi save");
  server.arg("s").toCharArray(softAP_ssid_eeprom, sizeof(softAP_ssid_eeprom) - 1);
  server.arg("n").toCharArray(ssid, sizeof(ssid) - 1);
  server.arg("p").toCharArray(password, sizeof(password) - 1);
  server.sendHeader("Location", "wifi", true);
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.client().stop(); // Stop is needed because we sent no content length
  saveCredentials();
  connect = strlen(ssid) > 0; // Request WLAN connect with new credentials if there is a SSID
}

void handleNotFound()
{
  String message = F("File Not Found\n\n");

  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");

  for (uint8_t i = 0; i < server.args(); i++) {
    message += String(F(" ")) + server.argName(i) + F(": ") + server.arg(i) + F("\n");
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(404, "text/plain", message);
  // Print uri not handled
  Serial.println(server.uri());
}

/** Redirect to captive portal if we got a request for another domain. Return true in that case so the page handler do not try to handle the request again. */
boolean captivePortal()
{
  if (!isIp(server.hostHeader()) && server.hostHeader() != (String(myHostname) + ".local")) {
    // Serial.println("Request redirected to captive portal");
    server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send(302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
    return true;
  }
  return false;
}

/**
 * Utils
 */
/** Return the current rotation value along X axis - in degrees */
double read_angle()
{
  float x_accum = 0, y_accum = 0, z_accum = 0;

  for (int nn = 0; nn < NUM_SAMPLES; nn++) {
    mma.getAcceleration(&x, &y, &z);
    x_accum += x;
    y_accum += y;
    z_accum += z;
  }

  x  = x_accum / NUM_SAMPLES;
  y  = y_accum / NUM_SAMPLES;
  z  = z_accum / NUM_SAMPLES;

  // apply g offset
  x -= x_offset;
  y -= y_offset;
  z -= z_offset;

  // Serial.println("Samples: " + String(x,3) + ":" + String(y,3) + ":" + String(z, 3));

  switch (axis) {
  case Y_AXIS:
    return atan2(x, z) / M_PI * 180;

  case Z_AXIS:
    return atan2(x, y) / M_PI * 180;

  case X_AXIS:
  default:
    return atan2(y, z) / M_PI * 180;
  }
}

void compute_values(float angle)
{
  double x_rot = 0;
  float angle_rad = 0, debat = 0;

  // compute angle variation vs. reference angle, find shortest way
  x_rot = fmod((ref_angle - angle) + 180, 360);
  if (x_rot < 0) {
    x_rot += 180;
  } else {
    x_rot -= 180;
  }
  // Serial.println("Ref:" + String(ref_angle,9) + " Angle:" + String(x_rot, 9));

  // angle filtering
  x_rot      = (last_angle * ALPHA) + (x_rot * (1 - ALPHA));
  last_angle = x_rot;

  angle_rad  = x_rot / 180 * M_PI;
  debat      = sqrt(2 * sq(corde) - (2 * sq(corde) * cos(angle_rad)));         // throw computation in same units as chord

  // invert angle displayed if needed
  angle_web  = (invert_angle) ? -x_rot : x_rot;
  throw_web  = (angle_web < 0) ? debat * -1 : debat;

  if (throw_web > maxthrow_web) {
    maxthrow_web = throw_web;
  } else if (throw_web < minthrow_web) {
    minthrow_web = throw_web;
  }
}

/** Reset min/max throw values */
void reset_minmax()
{
  minthrow_web = 0;
  maxthrow_web = 0;
  Serial.println("Reset min/max\r");
}

/** Initialize current angle as the reference angle */
void init_angle()
{
  ref_angle = read_angle();
  Serial.println("Init angle\r");
}

/** Is this an IP? */
boolean isIp(String str)
{
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

/** IP to String */
String toStringIp(IPAddress ip)
{
  String res = "";

  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

/** Load settings from EEPROM */
void loadSettings()
{
  // 4 + 4 + 4 + 1
  EEPROM.begin(512);
  EEPROM.get(0, corde);
  EEPROM.get(0 + sizeof(corde), min_setting);
  EEPROM.get(0 + sizeof(corde) + sizeof(min_setting), max_setting);
  EEPROM.get(0 + sizeof(corde) + sizeof(min_setting) + sizeof(max_setting), axis);
  char ok[2 + 1];
  EEPROM.get(0 + sizeof(corde) + sizeof(min_setting) + sizeof(max_setting) + sizeof(axis), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    // Something is wrong, back to defaults
    corde = 50;
    min_setting = 15;
    max_setting = 15;
    axis  = X_AXIS;
  }
  Serial.println("Load settings: " + String(corde) + "/" + String(min_setting) + "/" + String(max_setting) + "/" + axis + "/" + String(sizeof(axis)));
}

/** Save settings to EEPROM */
void saveSettings()
{
  // 4 + 4 + 4 + 1
  Serial.println("Save settings: " + String(corde) + "/" + String(min_setting) + "/" + String(max_setting) + "/" + axis);
  EEPROM.begin(512);
  EEPROM.put(0, corde);
  EEPROM.put(0 + sizeof(corde), min_setting);
  EEPROM.put(0 + sizeof(corde) + sizeof(min_setting), max_setting);
  EEPROM.put(0 + sizeof(corde) + sizeof(min_setting) + sizeof(max_setting), axis);
  char ok[2 + 1] = "OK";
  EEPROM.put(0 + sizeof(corde) + sizeof(min_setting) + sizeof(max_setting) + sizeof(axis), ok);
  EEPROM.commit();
  EEPROM.end();
}

/** Load calibrations from EEPROM */
void loadCalibrations()
{
  // 4 + 4 + 4
  EEPROM.begin(512);
  EEPROM.get(32, xoff_calibration);
  EEPROM.get(32 + sizeof(xoff_calibration), yoff_calibration);
  EEPROM.get(32 + sizeof(xoff_calibration) + sizeof(yoff_calibration), zoff_calibration);
  char ok[2 + 1];
  EEPROM.get(32 + sizeof(xoff_calibration) + sizeof(yoff_calibration) + sizeof(zoff_calibration), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    xoff_calibration = 0;
    yoff_calibration = 0;
    zoff_calibration = 0;
  }
  Serial.println("Load calibrations: " + String(xoff_calibration) + "/" + String(yoff_calibration) + "/" + String(zoff_calibration));
}

/** Save calibrations to EEPROM */
void saveCalibrations()
{
  // 4 + 4 + 4
  Serial.println("Save calibrations: " + String(xoff_calibration) + "/" + String(yoff_calibration) + "/" + String(zoff_calibration));
  EEPROM.begin(512);
  EEPROM.put(32, xoff_calibration);
  EEPROM.put(32 + sizeof(xoff_calibration), yoff_calibration);
  EEPROM.put(32 + sizeof(xoff_calibration) + sizeof(yoff_calibration), zoff_calibration);
  char ok[2 + 1] = "OK";
  EEPROM.put(32 + sizeof(xoff_calibration) + sizeof(yoff_calibration) + sizeof(zoff_calibration), ok);
  EEPROM.commit();
  EEPROM.end();
}

/** Load WLAN credentials and AP_ssid from EEPROM */
void loadCredentials()
{
  // 32 + 32 + 32
  EEPROM.begin(512);
  EEPROM.get(64, ssid);
  EEPROM.get(64 + sizeof(ssid), password);
  EEPROM.get(64 + sizeof(ssid) + sizeof(password), softAP_ssid_eeprom);
  char ok[2 + 1];
  EEPROM.get(64 + sizeof(ssid) + sizeof(password) + sizeof(softAP_ssid_eeprom), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    ssid[0]     = 0;
    password[0] = 0;
    softAP_ssid_eeprom[0] = 0;
  }
  Serial.println("Recovered credentials:");
  Serial.println(ssid);
  Serial.println(strlen(password) > 0 ? "********" : "<no password>");
}

/** Store WLAN credentials and AP_ssid to EEPROM */
void saveCredentials()
{
  // 32 + 32 + 32
  EEPROM.begin(512);
  EEPROM.put(64, ssid);
  EEPROM.put(64 + sizeof(ssid), password);
  EEPROM.put(64 + sizeof(ssid) + sizeof(password), softAP_ssid_eeprom);
  char ok[2 + 1] = "OK";
  EEPROM.put(64 + sizeof(ssid) + sizeof(password) + sizeof(softAP_ssid_eeprom), ok);
  EEPROM.commit();
  EEPROM.end();
}
