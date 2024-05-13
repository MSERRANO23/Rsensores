#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"
#include <Arduino.h>

//Variables acelerometro
float xA, yA, zA;

//Variables giroscopio
float xG, yG, zG;

//Variables magnetometro
float xM, yM, zM;

// Timer
BBTimer timer(BB_TIMER0);
int tint = 2000;  //Frecuencia 500 Hz,Periodo en us
bool flag = false;

void setup() {
  // Inicializar UART
  Serial.begin(115200);
  // Inicializar sensores
  IMU.begin();
  //Inicializar timer
  timer.setupTimer(tint, interrup);
  timer.timerStart();
}

void interrup() {
  flag = true;
}

void loop() {
  if (flag == true) {
    // Read values
    IMU.readAcceleration(xA, yA, zA);
    Serial.println(" X " + String(xA) + " Y " + String(yA) + " Z " + String(zA));
    IMU.readGyroscope(xG, yG, zG);
    Serial.println(" X " + String(xG) + " Y " + String(yG) + " Z " + String(zG));
    IMU.readMagneticField(xM, yM, zM);
    Serial.println(" X " + String(xM) + " Y " + String(yM) + " Z " + String(zM));
    Serial.println("----------------");
  }
  flag = false;
  delay(500);
}