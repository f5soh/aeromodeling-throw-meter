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

/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

// 0 to 20.5dBm
float outputPower = 0;

MMA8452 mma;
double ref_angle, last_angle;
float angle_web, debat_web;
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

  Serial.println("Configuring access point...");

  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid); // No password
  WiFi.setOutputPower(outputPower);
  delay(500); 
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  /* Setup the DNS server redirecting all the domains to the apIP */
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);

  server.on("/", handleRoot);
  server.on("/setData", handleData);       // Receive request from webpage and change settings
  server.on("/readData", handleValues);    // Send values to be displayed in webpage
  server.on("/generate_204", handleRoot);  // Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleRoot);        // Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started"); 

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
  debat_web = debat;
  
  // DNS
  dnsServer.processNextRequest();
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
  server.send(200, "text/plane", String(angle_web,2) + ":" + String(int(debat_web)) + ":" + String(int(corde)));
}

/** Receive values from page */
void handleData() {
 String t_state = server.arg("Datastate");
 if(t_state == "0") {
    init_angle();
 }
 // Corde change
 if(t_state == "1") {
    corde++;
 }
 if(t_state == "-1") {
    corde--;
 }
 if(t_state == "10") {
    corde += 10;
 }
 if(t_state == "-10") {
    corde -= 10;
 }
 if(t_state == "301") {
    saveCorde();
 }
 if(t_state == "302") {
    loadCorde();
 }

 // Keep corde value between limits
 if (corde < 0) {
    corde = 0;
 } else if (corde > 200) {
    corde = 200;
 }
 // send new values after setting change
 handleValues(); 
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
    Serial.println("Request redirected to captive portal");
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
