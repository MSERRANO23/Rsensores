#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"
#include <Arduino.h>

//Variables acelerometro
float xa, ya, za;

//Variables giroscopio
float xg, yg, zg;

//Variables magnetometro
float xm, ym, zm;

// Timer
BBTimer timer(BB_TIMER0);
int tint = 2000;  //Frecuencia 500 Hz,Periodo en us
bool flag = false;

void setup() {
  // Inicializar UART
  Serial.begin(9600);
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
  if(flag == true){
    // Leer sensores
    IMU.readAcceleration(xa, ya, za);
    Serial.print(xa);
    Serial.print(" ");
    Serial.print(ya);
    Serial.print(" ");
    Serial.print(za);
    Serial.print(" ");

    IMU.readGyroscope(xg, yg, zg);
    Serial.print(xg);
    Serial.print(" ");
    Serial.print(yg);
    Serial.print(" ");
    Serial.print(zg);
    Serial.print(" ");

    IMU.readMagneticField(xm, ym, zm);
    Serial.print(xm);
    Serial.print(" ");
    Serial.print(ym);
    Serial.print(" ");
    Serial.print(zm);
    Serial.print(" ");
    
  }
  flag = false;
}