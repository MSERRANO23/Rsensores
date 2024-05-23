#include <WiFi.h>
#include <EspMQTTClient.h>

// Configuración
const char* wifiSSID = "";
const char* wifiPASS = "";
const char* mqttServerIP = "io.adafruit.com";
const char* io_Username = "MSERRANO17";
const char* io_Password = "";
const char* mqttClientName = "ESP_PROBANDO";
const int mqttPort = 1883;                               // Puerto para conexión segura
const char* topic = "MSERRANO17/feeds/sensores";         //topic para modificar la variable sensores
const char* activacion = "MSERRANO17/feeds/activacion";  //topic para leer la variable

// Crear instancia de cliente MQTT
EspMQTTClient client(wifiSSID, wifiPASS, mqttServerIP, io_Username, io_Password, mqttClientName, mqttPort);
int dato = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  while (client.isConnected()) {
    Serial.println("Trying");
    delay(2000);
  }
  Serial.println("Finish setup");
}

float anterior = 0.0;
String Active = "OFF";

void loop() {
  client.loop();
  client.subscribe(activacion, [](const String & payload) {
    Serial.println(payload);
    if (payload == "ON") {
      Active = "ON";
    } else {
      Active = "OFF";
      dato=0;
    }
  });
  if (Active == "ON") {
    Serial.println("Recepcion conseguida");
    dato++;
    client.publish(topic, String(dato));
  }
  delay(5000);
  if (dato >= 50) dato = 0;
}

void onConnectionEstablished() {
  Serial.println("Conexión MQTT establecida");
  // Aquí puedes agregar cualquier código que desees ejecutar una vez que la conexión MQTT se haya establecido.
}