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

#define sensor1 D0
#define sensor2 D1
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

  server.on("/", handleRoot);
  server.on("/t1", getT1);
  server.on("/l1", getL1);
  server.on("/t2", getT2);
  server.on("/l2", getL2);
  server.begin();

  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);

  Serial.println("started");
}


void handleRoot() {
  server.send(200, "text/html", index_html);  
}

int t1 = 0;
int l1 = 0;
int t2 = 0;
int l2 = 0;

void getT1() {  
  server.send(200, "text/plain", String(t1)); 
}

void getL1() {
  server.send(200, "text/plain", String(l1));   
}

void getT2() {  
  server.send(200, "text/plain", String(t2));   
}

void getL2() {
  server.send(200, "text/plain", String(l2));   
}

void loop() {
  readSensor(sensor1, &t1, &l1);
  readSensor(sensor2, &t2, &l2);

  server.handleClient();
}

void readSensor(int sensorPin, int *temp, int *level) {
    digitalWrite(sensorPin, LOW);
    delay(500);

    dallasSensors.requestTemperatures();
    *temp = (int) dallasSensors.getTempCByIndex(0);
    Serial.print(sensorPin);
    Serial.print(" - ");
    Serial.println(*temp);

    *level = waterLevel(level1pin);

    digitalWrite(sensorPin, HIGH);
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
