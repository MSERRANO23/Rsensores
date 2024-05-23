#include <BBTimer.hpp>
#include <Arduino_LSM9DS1.h>

// Generacion del TIMER
BBTimer my_t0(BB_TIMER0);
bool flag = false;
int tiempo_interrupcion = 50;

//Variables acelerometro
float xa, ya, za;

void setup() {
  Serial.begin(9600);
  IMU.begin();
  my_t0.setupTimer(tiempo_interrupcion, interrupcion);
  my_t0.timerStart();
}

// Funcion de interrupcion cada 50 ms
void interrupcion() {
  flag = true;
}

void loop() {
  if (flag == true) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(xa, ya, za);
    }
    Serial.println(xa);
    Serial.println(ya);
    Serial.println(za);

    flag = false;
  }
}
