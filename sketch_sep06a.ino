#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "index.h"

const char *ssid = "NASA";
const char *password;

ESP8266WebServer server(80);

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);  
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("started");
}

void loop() {
  server.handleClient();
}
