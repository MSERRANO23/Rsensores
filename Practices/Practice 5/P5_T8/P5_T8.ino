//Crear fichero JSON que genere cada 10 segundos datos inventados con sus unidades y la 
//marca temporal
#include "ArduinoJson.h"
#include "WiFi.h"
#include "time.h"

const char* ssid = "";
const char* password = "";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

WiFiClient client;
const char* server = "10.94.176.59";  //IP of phone or computer
const int port = 8008;    //select the port, the same of the app and code

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nCONNECTED");

  Serial.println("conectado a Wifi");
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  if (!client.connect(server, port)) {
    Serial.println("Fail to connect");
    return;
  } else {
    Serial.println("Success to connect");
  }
}

struct tm timeinfo;
StaticJsonDocument<200> doc;
void loop() {
  //StaticJsonDocument<200> doc;
  
  int temp = random(16.0, 30.0);
  //Serial.println("\n");
  //Serial.println(temp);
  doc["Temperatura"] = temp;
  //doc["Hora"] = &timeinfo;
  Serial.println("\n");
  delay(500);
  //serializeJson(doc,Serial);
  serializeJson(doc,client);
  //client.print(serializeJson(doc,Serial));
  client.print("\n");
  delay(2000);
}

void printLocalTime() {
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  /*if (client.connected()) {
    client.print(&timeinfo, "%A, %B %d %Y %H:%M:%S\n\n\n\n");
  }*/
}