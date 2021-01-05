#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "index.h"

const char *ssid = "nasa";
const char *password = "melnikov";

ESP8266WebServer server(80);

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);  
}

void setup() {
  Serial.begin(115200);
  
  /*WiFi.begin(ssid, password);
Serial.println("");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  */
  
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/temp", doTemp);
  server.on("/", handleRoot);
  server.begin();
  
  Serial.println("started");
}

void doTemp(){  
  //gettemperature();       // read sensor
  String webString = "Temperature: " + String((int) 1.0)+" C";
  server.send(200, "text/plain", webString);   
}

void loop() {
  server.handleClient();
}
