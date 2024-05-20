#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"

// Variables
int estado = 0;
int i = 0;
int a = 0;  //arriba
int s = 0;  //subiendo
int p = 0;  //permaneciendo
int length = 0;

// Derivadas
float dAcel = 0;
float dGiro = 0;

// Umbrales
int umbral = 1000;

// Generacion del TIMER
BBTimer my_t0(BB_TIMER0);
int tiempo_interrupcion = 2000;  //Frecuencia 500 Hz, periodo en us
bool flag = false;

//Variables acelerometro
float x_acel, y_acel, z_acel, za;
float za_vec[5000];  //, ya[15000]; Cambio de ejes

//Variables giroscopio
float x_giro, y_giro, z_giro, yg;
float yg_vec[5000];  //, zg[15000]; Cambio de ejes

//Vectores y variables de guradado de datos
float subida[500];
float arriba[500];

// Calculo del giro maximo
float max_giro = 0;
float min_giro = 20;
float acc_giro = 0;

// Variables a mandar
float tiempo_subida = 0.0;
float tiempo_permanencia = 0.0;
float giro_max = 0.0;
float giro_min = 0.0;
float giro_med = 0.0;

// Rutina de interrupcion cada 2 ms
void inter() {
  flag = true;
}

void setup() {
  Serial.begin(9600);
  IMU.begin();
  my_t0.setupTimer(tiempo_interrupcion, inter);
  my_t0.timerStart();

  //Inicializar vectores
  za_vec[0] = 0.0;
  yg_vec[0] = 0.0;

  //añadir incializacion BT
}

void loop() {
  Serial.println("----------------------");
  // Interrupción
  if (flag == true) {
    IMU.readAcceleration(x_acel, y_acel, z_acel);
    IMU.readGyroscope(x_giro, y_giro, z_giro);
    // Guardo la aceleracion en z
    za = -y_acel;  // acel en g
    // Guardo el giro en Y
    yg = z_giro;  // giro en dps

    
  }
  flag = false;
  Serial.println(za);
  Serial.println(yg);
  Serial.println("++++++++++");
  // Maquina de estados
  // Cálculo de la derivada
  dAcel = (za - za_vec[i-1]) / tiempo_interrupcion;  // derivada subiendo o bajando < 1000
  dGiro = (yg - yg_vec[i-1]) / tiempo_interrupcion;  // derivada arriba o en reposo < 1000
  Serial.println(dAcel*1000);
  Serial.println(dGiro*1000);
  delay(500);
  yg_vec[i] = yg;
  za_vec[i] = za;
  Serial.println(za_vec[i-1]);
  Serial.println(yg_vec[i-1]);
  Serial.println(i);
  i++;
  // derivada de giro < 6 para considerar que no varia
  //derivada de aceleración < 0.3 para considerar que no varia
  
}
