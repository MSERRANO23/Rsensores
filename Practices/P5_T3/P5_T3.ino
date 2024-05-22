//Poner en hora el modulo
#include "WiFi.h"
#include "time.h"
// #include "WiFiClient.h"

const char* ssid = "";
const char* password = "";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

WiFiClient client;
const char* server = "";  //IP of phone or computer
const int port = 8008;    //select the port, the same of the app and code

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // connect to wifi
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
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
}

struct tm timeinfo;
int c=0;
bool flag = false;
char leido[15];

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    client.connect(server, port);
  } 
  if (client.available()) {
    c = client.read();
    Serial.println(c);
    if (c == 49) {
      flag = true;
    } 
    if(c == 48){
      flag = false;
      client.print("Finish comunication \n");
    }
  }
  if (flag == true) {
      delay(1000);
      printLocalTime();
    }
}

void printLocalTime() {
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  if (client.connected()) {
    client.print(&timeinfo, "%A, %B %d %Y %H:%M:%S\n\n\n\n");
  }
}