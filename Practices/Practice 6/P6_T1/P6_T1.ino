//Crea un programa que cree dos tareas,
//una que parpadee un LED cada 200 ms y otra que
//envíe un “hola mundo” por la UART cada segundo.
#include <Arduino.h>
#define LED 25
#define LED2 26
float anterior = 0.0;
int dato = 0.0;
int i = 0;
int j = 0;
int paquete[10];
void setup() {
  Serial.begin(115200);
  delay(1000);
  xTaskCreate(Tarea1, "Tarea1", 10000, NULL, 1, NULL);  //lectura
  xTaskCreate(Tarea2, "Tarea2", 10000, NULL, 1, NULL);  //envio de datos
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  delay(5000);
}

void Tarea1(void* parameter) {
  for (;;) {
    dato = random(0, 145);
    paquete[i] = dato;
    i++;
    
    delay(100);  // Espera 100ms
  }
  Serial.println("Finalizando tarea 1");
  vTaskDelete(NULL);
}

void Tarea2(void* parameter) {
  for (;;) {

    for(j=0;j<10;j++)Serial.println(paquete[j]);
    Serial.println("-------------");
    i = 0;
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(800);
  }

  vTaskDelete(NULL);
}