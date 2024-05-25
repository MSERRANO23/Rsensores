// Librerias
#include <arduino.h>
#include "BBTimer.hpp"
#include "mbed.h"
#include <Arduino_LSM9DS1.h>
//#include <ArduinoBLE.h>
// Interrupcion
BBTimer my_t0(BB_TIMER0);
int tiempo_interrupcion = 20000;  //Frecuencia 500 Hz, periodo en us
bool flag = false;

// Variables
String estado;

float x_acel = 0.0;
float y_acel = 0.0;
float z_acel = 0.0;

float x_giro = 0.0;
float y_giro = 0.0;
float z_giro = 0.0;

float za = 0.0;
float yg = 0.0;

float max_giro = 10.0;
float min_giro = -0.0;
float giro_med = 0.0;
float giro_max = 0.0;
float giro_min = 0.0;

int a = 0;

float t_ini_subida = 0.0;
float t_arriba = 0.0;
float t_puntillas = 0.0;

//Elementos BT
/*BLEService Service("1001");
BLEStringCharacteristic Angle_MAX("2001", BLERead | BLENotify, 12);
BLEStringCharacteristic Angle_MIN("2002", BLERead | BLENotify, 12);
BLEStringCharacteristic Angle_MEAN("2003", BLERead | BLENotify, 12);
BLEStringCharacteristic puntillas_Completo("2004", BLERead | BLENotify, 12);
BLEStringCharacteristic puntillas_arriba("2005", BLERead | BLENotify, 20);
BLEByteCharacteristic caracteristicas("1001", BLERead | BLEWrite);
*/

// Rutina de interrupcion
void inter() {
  flag = true;
}  // end rutina interrupcion

void setup() {

  // Inicializar Serial
  Serial.begin(9600);

  // Inicializar IMU
  IMU.begin();

  // Inicializar interrupcion
  my_t0.setupTimer(tiempo_interrupcion, inter);
  my_t0.timerStart();

  // Inicializar estado
  estado = "Reposo";
  //Bluetooth inicio
  /*
  if (!BLE.begin()) {
    while (1)
      ;
  }
  BLE.setLocalName("HM");
  BLE.setAdvertisedService(Service);

  Service.addCharacteristic(Angle_MAX);
  Service.addCharacteristic(Angle_MEAN);
  Service.addCharacteristic(Angle_MIN);
  Service.addCharacteristic(puntillas_Completo);
  Service.addCharacteristic(puntillas_arriba);
  Service.addCharacteristic(caracteristicas);
*/
  //BLE.addService(Service);
  //BLE.advertise();
}  // end setUp

void loop() {

  /*BLEDevice central = BLE.central();
  if (central.connected()) {

    if (caracteristicas.written()) {
      bool activacion;
      if (caracteristicas.value() > 0) {
        activacion = true;
      } else {
        activacion = false;
      }
      if (activacion) {
        Serial.println("ON");
      } else {
        Serial.println("OFF");
      }
    }*/
  // Funcion de la Interrupción
  if (flag == true) {

    // Lectura de datos
    IMU.readAcceleration(x_acel, y_acel, z_acel);
    IMU.readGyroscope(x_giro, y_giro, z_giro);

    // Almacenamiento y procesado de la muestra tomada
    // Variable de interes: aceleracion en z
    za = -y_acel;  // acel en g
    //Serial.println(za);
    // Variable de interes: giro en Y
    yg = z_giro;  // giro en dps
    //Serial.println(yg);

  }  // end funcInter

  flag = false;

  // Maquina de estados
  //Serial.println(za);
  //Serial.println(yg);
  if (yg > 0.50 && yg < 1.5 && za < 1.1 && za > 0.90) {
    estado = "Reposo";
  }

  else if (yg > 4.5) {
    estado = "Bajando";
  }

  else if (yg < 2.0 && za < 0.94) {
    estado = "Arriba";
  }

  else if (yg < (-4.5)) {
    estado = "Subiendo";
  }



  if (estado == "Reposo") {

    // Calculo del tiempo total que ha estado de puntillas
    if (t_puntillas == 0.0 and t_ini_subida != 0) {
      t_puntillas = millis() - t_ini_subida;
    }

    // Mandar por BLE (t_puntillas, t_arriba, giro_max, giro_min, giro_med)
    if(!t_puntillas == 0.0){
    Serial.println(t_puntillas/1000);
    Serial.println(t_arriba/1000);
    Serial.println(giro_max);
    Serial.println(giro_min);
    Serial.println(giro_med);
    Serial.println(estado);
    }
    //Send BLE data
    //Angle_MAX.writeValue(String(giro_max));
    //Angle_MIN.writeValue(String(giro_min));
    //Angle_MEAN.writeValue(String(giro_med));
    //puntillas_Completo.writeValue(String(t_puntillas/1000));
    //puntillas_arriba.writeValue(String(t_arriba/1000));


    // Reset de las variables
    max_giro = 10.0;
    min_giro = 0.0;
    giro_med = 0.0;
    giro_max = 0.0;
    giro_min = 0.0;

    a = 0;

    t_ini_subida = 0.0;
    t_arriba = 0.0;
    t_puntillas = 0.0;
  }  // end Reposo

  else if (estado == "Subiendo") {

    // Calculo del momento que empieza a ponerse de puntillas
    if (t_ini_subida == 0.0) {
      t_ini_subida = millis();
    }
    Serial.println(estado);
  }  //end Subiendo

  else if (estado == "Arriba") {

    // Calculo de los angulos I
    if (yg > 0) {
      giro_med += yg;
    } else {
      giro_med += (-1.0) * yg;
    }
    a++;

    if (yg < min_giro) {
      min_giro = yg;
    }
    if (yg > max_giro) {
      max_giro = yg;
    }
    Serial.println(estado);
  }  // end Arriba

  else if (estado == "Bajando") {

    // Calculo del tiempo que ha estado arriba
    if (t_arriba == 0.0) {
      t_arriba = millis() - t_ini_subida;
    }

    // Calculo de los angulos II
    giro_min = min_giro * tiempo_interrupcion / 10000;
    giro_max = max_giro * tiempo_interrupcion / 10000;
    giro_med = giro_med * tiempo_interrupcion / (float)a / 10000;
    Serial.println(estado);
  }  // end Bajando
  delay(500);
  //}
  Serial.println("---------------");
}  // end loop
