#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// temperature
#include <OneWire.h>
#include <DallasTemperature.h>

#include "index.h"

const char *ssid = "nasa";
const char *password = "12345678";

ESP8266WebServer server(80);

/* Настройки IP адреса 
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
*/


// Data wire is plugged into pin 2 on the Arduino
// D4 = GPIO2 = 2
#define ONE_WIRE_BUS D4
// Создаем объект OneWire
OneWire oneWire(ONE_WIRE_BUS);
// Создаем объект DallasTemperature для работы с сенсорами, передавая ему ссылку на объект для работы с 1-Wire.
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

  Serial.print("Измеряем температуру...");
  dallasSensors.requestTemperatures(); // Просим ds18b20 собрать данные
  Serial.println("Выполнено");
  //  Запрос на получение сохраненного значения температуры
  // printTemperature(sensorAddress);

  Serial.println(dallasSensors.getTempCByIndex(0));

  delay(1000);

  server.handleClient();
}

// Вспомогательная функция печати значения температуры для устрйоства
void printTemperature(DeviceAddress deviceAddress){
  float tempC = dallasSensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}
