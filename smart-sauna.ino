#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// temperature
#include <OneWire.h>
#include <DallasTemperature.h>

// html template
#include "index.h"

const char *ssid = "nasa";
const char *password = "12345678";

ESP8266WebServer server(80);

/* Настройки IP адреса 
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
*/

#define sensorEnable D0
#define level1pin A0
#define temp1 D4
OneWire oneWire(temp1);
DallasTemperature dallasSensors(&oneWire);





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
  
  // Access Point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", handleRoot);server.on("/", handleRoot);
  server.on("/t1", getT1);
  server.on("/l1", getL1);
  server.begin();

  pinMode(sensorEnable, OUTPUT);

  Serial.println("started");
}


void handleRoot() {
  server.send(200, "text/html", index_html);  
}

float t1;
int l1;

void getT1() {  
  server.send(200, "text/plain", String(t1));   
}

void getL1() {
  server.send(200, "text/plain", String(l1));   
}


void loop() {
  digitalWrite(sensorEnable, HIGH);
  delay(1000);

  dallasSensors.requestTemperatures(); // Просим ds18b20 собрать данные
  t1 = dallasSensors.getTempCByIndex(0);
  Serial.println(t1);


  l1 = waterLevel(level1pin);
  Serial.println(l1);

  digitalWrite(sensorEnable, LOW);

  server.handleClient();
}



double L = 100.0; // длина трубки в см
// mpx5010pd
// 1 - Out
// 2 - Gnd
// 3 - Vcc
int waterLevel(int pin) {
  double p = analogRead(pin);

  // Давление водяного столба в кПа
  double h = (p / 1024 - 0.04) / 0.018 / 5.0; // kPa

  // Расчитываем поправку в см
  double l = L * h / (100.0 + h);

  int total = h * 10.0 + l;
  return total;
}
