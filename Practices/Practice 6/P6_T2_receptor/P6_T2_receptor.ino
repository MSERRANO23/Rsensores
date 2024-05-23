#include <Wire.h>
#include <Arduino.h>
#define LED 26

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  xTaskCreate(Tarea1, "Tarea1", 10000, NULL, 1, NULL);  //blinking
  xTaskCreate(Tarea2, "Tarea2", 10000, NULL, 1, NULL);  //hola mundo
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
void receiveEvent(int howMany) {
  char c = Wire.read();  // receive a character
  if (c == '0') {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  }
  if (c == '1') {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  }
}
void Tarea1(void* parameter) {
  for (;;) {
    int recibido = Wire.read();
    delay(100);
  }

  vTaskDelete(NULL);
}

void Tarea2(void* parameter) {
  for (;;) {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    Serial.println(recibido);
    delay(800);
  }
  vTaskDelete(NULL);
}