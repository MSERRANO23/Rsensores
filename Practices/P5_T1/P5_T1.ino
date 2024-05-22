// comprobar la conectivida haciendo un Ping a Google
#include <WiFi.h>
#include "ESPping.h"

const char* ssid = "";
const char* password = "";
//Direccion de google para el ping
const char* host = "10.158.134.30";

void setup(){
  Serial.begin(115200);
  delay(10);
  // show details of the connection
  Serial.println();
  Serial.print("conectando a ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  Serial.println("++++++++++++++Fin de setup+++++++++");
}

void loop(){
   // Realizar un ping a Google DNS
 Serial.print("Realizando ping a ");
 Serial.println(host);
  
 // Configura el ping
 int pingResult = Ping.ping(host);
  
 // Verificar el resultado
 if (pingResult >= 0) {
    Serial.print("Resultado del ping: ");
    Serial.print(pingResult);
    Serial.println(" ms");
 } else {
    Serial.println("No se pudo realizar el ping");
 }

 delay(5000);
}