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


#define ONE_WIRE_BUS D4
// Создаем объект OneWire
OneWire oneWire(ONE_WIRE_BUS);
// Создаем объект DallasTemperature для работы с сенсорами, передавая ему ссылку на объект для работы с 1-Wire.
DallasTemperature dallasSensors(&oneWire);

#define level1pin A0


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

  server.on("/", handleRoot);server.on("/", handleRoot);
  server.on("/temp", doTemp);
  server.begin();
  
  Serial.println("started");
}


void handleRoot() {
  server.send(200, "text/html", index_html);  
}

void doTemp(){  
  Serial.println("doTemp");
  //gettemperature();       // read sensor
  String webString = "Temperature: " + String((int) 1.0)+" C";
  server.send(200, "text/plain", webString);   
}

void loop() {

  dallasSensors.requestTemperatures(); // Просим ds18b20 собрать данные
  float t1 = dallasSensors.getTempCByIndex(0);
  Serial.println(t1);


  int l1 = waterLevel(level1pin);
  Serial.println(l1);

  delay(1000);

  server.handleClient();
}

// Вспомогательная функция печати значения температуры для устрйоства
void printTemperature(DeviceAddress deviceAddress){
  float tempC = dallasSensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
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
