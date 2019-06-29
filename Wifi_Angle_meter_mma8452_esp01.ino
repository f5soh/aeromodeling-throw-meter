/*
   Angle meter using a MMA8452 sensor and ESP01
   f5soh@free.fr - 2019

   Parts from:
   https://github.com/f5mmx/aeromodeling-throw-meter
   https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer/examples/CaptivePortalAdvanced
   
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#include <Wire.h>
#include <MMA8452.h>                  // MMA8452 library            from https://github.com/akupila/Arduino-MMA8452



#include "index.h" // HTML webpage contents with javascripts

#ifndef APSSID
#define APSSID "debat"
#define APPSK  "1234"
#endif

const char *softAP_ssid = APSSID;
const char *softAP_password = APPSK;

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;

/* hostname for mDNS. Should work at least on windows. Try http://debat.local */
const char *myHostname = "debat";

// Web server
ESP8266WebServer server(80);

// Http client
HTTPClient http;

/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

// 0 to 20.5dBm
float outputPower = 0;

// initial value: device is master (AP) by default
bool is_master = true;
String slaveDeviceIP = "";
String data;
unsigned long lastSent;
unsigned long lastReceived;
unsigned long sendEvery_ms = 400;
unsigned long timeOut_ms = 3000;

MMA8452 mma;
double ref_angle, last_angle;
float angle_web, throw_web, minthrow_web=0, maxthrow_web=0;
String str_angle2_web = "0", str_throw2_web = "0", str_minthrow2_web = "0", str_maxthrow2_web = "0", str_dual = "0";
int corde = 50;

#define NUM_SAMPLES  150
#define ALPHA        0.7

/**
 * Configure sensor and server
 */
void setup() {
  // Configure I2C
  Wire.begin(0,2);       // Wire.begin([SDA], [SCL])
  Wire.setClock(400000); // 400KHz
  
  Serial.begin(9600);
  Serial.println("I2C config done");

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
      if (WiFi.SSID(i) == APSSID) {
         Serial.println("Master device found!");
         is_master = false;
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
      WiFi.begin(APSSID, APPSK);
    } else {
      WiFi.begin(APSSID);
    }
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(300);
    }
    Serial.println(" Connected!!!\r");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/setData", handleSlaveData);       // Receive request from master and change settings
    // server.on("/readData", handleValues);    // Send values to be displayed in webpage
  } else {
      Serial.println("Configuring access point...");

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
      server.on("/setData", handleData);            // Receive request from webpage and change settings
      server.on("/setSlaveData", handle_slaveData); // Receive sensor data from slave
      server.on("/readData", handleValues);         // Send values to be displayed in webpage (master and slave if any)
      server.on("/generate_204", handleRoot);  // Android captive portal. Maybe not needed. Might be handled by notFound handler.
      server.on("/fwlink", handleRoot);        // Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
      server.onNotFound(handleNotFound);

      loadCorde();
  }
  
  server.begin();
  Serial.println("HTTP server started"); 
  
  // Will be set to min and save power
  WiFi.setOutputPower(outputPower); 

  // Sensor configuration 
  mma.setDataRate(MMA_400hz);
  mma.setRange(MMA_RANGE_2G);
  mma.setLowNoiseMode(true);

  delay(500);
  
  init_angle();
}

/**
 * Main loop
 */
void loop() { 
  double x_rot = 0;
  float angle_rad = 0, debat = 0;

  // compute angle variation vs. reference angle, find shortest way
  x_rot =  fmod((ref_angle - read_angle()) + 180, 360);
  if (x_rot < 0) {
     x_rot += 180;
  } else {
     x_rot -= 180;
  }
  //Serial.println("Ref:" + String(ref_angle,9) + " Angle:" + String(x_rot, 9));
  
  // angle filtering
  x_rot = (last_angle * ALPHA) + (x_rot * (1 - ALPHA));
  last_angle = x_rot;

  angle_rad = x_rot / 180 * M_PI;
  debat = sqrt(2 * sq(corde) - (2 * sq(corde) * cos(angle_rad)));         // throw computation in same units as chord

  angle_web = x_rot;
  throw_web = (angle_web < 0) ? debat * -1 : debat;
  
  if (throw_web > maxthrow_web) {
    maxthrow_web = throw_web;
  } else if(throw_web < minthrow_web) {
    minthrow_web = throw_web; 
  }  

  if (is_master) {
    // DNS
    dnsServer.processNextRequest();
    // Check if slave still here
    if ((millis() - lastReceived) > timeOut_ms) {
      str_dual = "0";
    } else {
      str_dual = "1";      
    }
  } else {
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
void handleRoot() {
 String s = MAIN_page; // Read HTML contents
 server.send(200, "text/html", s); // Send web page
}

/** Send values to page */
void handleValues() {
  server.send(200, "text/plane", String(int(corde)) + ":" + \
                                 String(angle_web, 2) + ":" + \ 
                                 String(throw_web, 1) + ":" + \
                                 String(minthrow_web, 1) + ":" + \
                                 String(maxthrow_web, 1) + ":" + \
                                 str_angle2_web + ":" + \ 
                                 str_throw2_web + ":" + \
                                 str_minthrow2_web + ":" + \
                                 str_maxthrow2_web + ":" + \
                                 str_dual);
}

/** Receive values from page */
void handleData() {
 if (!is_master) {
   return;
 }
 String t_state = server.arg("Datastate");
 int cmd = t_state.toInt();
 // Corde change
 if(cmd == 1) {
    corde++;
 }
 if(cmd == -1) {
    corde--;
 }
 if(cmd == 10) {
    corde += 10;
 }
 if(t_state == "-10") {
    corde -= 10;
 }
 if(cmd == 301) {
    saveCorde();
 }
 if(cmd == 302) {
    loadCorde();
 }
 if(cmd == 303) {
    minthrow_web = 0;
    maxthrow_web = 0;    
 }
 if(cmd == 304) {
    init_angle();
 }

 // Keep corde value between limits
 if (corde < 0) {
    corde = 0;
 } else if (corde > 200) {
    corde = 200;
 }

 server.send(200, "text/plain", "");
 server.client().stop();
 
 if (cmd > 302) {
   delay(10);
   sendToSlave(corde, cmd); 
 }

  // send new values after setting change
 handleValues();
}

void prepareSlaveData() {
  data = "angle2=" + String(angle_web, 2);
  data += "&throw2=" + String(throw_web, 1);
  data += "&minthrow2=" + String(minthrow_web, 1);
  data += "&maxthrow2=" + String(maxthrow_web, 1);
  data += "&chord=" + String(int(corde));
  // Serial.println("- data stream: "+data);
}

void sendSlaveData() {
  String serverURLData = "http://" + toStringIp(apIP)  + "/setSlaveData";
  http.setTimeout(200);  
  http.begin(serverURLData);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST(data);
  http.writeToStream(&Serial);
  http.end();
}

void sendToSlave(int chord, int cmd) {
  String slaveURL = "http://" + slaveDeviceIP  + "/setData";
  http.setTimeout(200); 
  http.begin(slaveURL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("chord=" + String(int(chord)) +"&cmd=" + String(int(cmd)));
  http.writeToStream(&Serial);
  http.end();
  //Serial.println("sendToSlave " + slaveURL + " " + chord + "cmd:" + String(int(cmd)));
}

void handleSlaveData() {
 String str = server.arg("cmd");
 int cmd = str.toInt();
 if (cmd == 303) {
  minthrow_web = 0;
  maxthrow_web = 0;    
 }
 if (cmd == 304) {
  init_angle();
 }
 str = server.arg("chord");
 
 server.send(200, "text/plain", "");
 server.client().stop();
 
 corde = str.toInt();
 //Serial.println("Received corde: " + String(corde) + " cmd=" + str);
 
}

// Handling the data from slave device
void handle_slaveData() {
  lastReceived = millis();
  if (slaveDeviceIP == "") {
    slaveDeviceIP = server.client().remoteIP().toString();
  }
  str_angle2_web = server.arg("angle2");
  str_throw2_web = server.arg("throw2");
  str_minthrow2_web = server.arg("minthrow2");
  str_maxthrow2_web = server.arg("maxthrow2");
  String chord_from_slave = server.arg("chord");
  
  server.send(200, "text/plain", "");
  server.client().stop();

  if (chord_from_slave.toInt() != corde) {
    delay(10);
    sendToSlave(corde, 0);
  }

}

void handleNotFound() {
  if (captivePortal()) { // If captive portal redirect instead of displaying the error page.
    return;
  }
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
}

/** Redirect to captive portal if we got a request for another domain. Return true in that case so the page handler do not try to handle the request again. */
boolean captivePortal() {
  if (!isIp(server.hostHeader()) && server.hostHeader() != (String(myHostname) + ".local")) {
    //Serial.println("Request redirected to captive portal");
    server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send(302, "text/plain", "");   // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
    return true;
  }
  return false;
}

/**
 * Utils
 */
/** Return the current rotation value along X axis - in degrees */
double read_angle() {                             
  float x, y, z;
  float x_accum = 0, y_accum = 0, z_accum = 0;
  for (int nn = 0;  nn < NUM_SAMPLES; nn++) {
    mma.getAcceleration(&x, &y, &z);
    x_accum += x;
    y_accum += y;
    z_accum += z;
  }

  x = x_accum / NUM_SAMPLES;
  y = y_accum / NUM_SAMPLES;
  z = z_accum / NUM_SAMPLES;

  return atan2(y, z) / M_PI * 180;
}

/** Initialize current angle as the reference angle */
void init_angle() {
  ref_angle = read_angle();                              
}
 
/** Is this an IP? */
boolean isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

/** IP to String */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

/** Load corde value from EEPROM */
void loadCorde() {
  EEPROM.begin(512);
  EEPROM.get(0, corde);
  char ok[2 + 1];
  EEPROM.get(0 + sizeof(corde), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    corde = 50;
  }
  Serial.println("Load corde: " + String(corde));

}

/** Save corde value to EEPROM */
void saveCorde() {
  Serial.println("Save corde: " + String(corde));
  EEPROM.begin(512);
  EEPROM.put(0, corde);
  char ok[2 + 1] = "OK";
  EEPROM.put(0 + sizeof(corde), ok);
  EEPROM.commit();
  EEPROM.end();
}
