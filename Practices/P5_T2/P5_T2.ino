//Poner en hora el modulo
#include "WiFi.h" 
#include "time.h"

const char* ssid       = "";
const char* password   = "";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // connect to wifi
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nCONNECTED");
  configTime(gmtOffset_sec, daylightOffset_sec,ntpServer);
  printLocalTime();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  printLocalTime();
  
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}