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
int dAcel = 0;
int dGiro = 0;

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
float max_giro = 0.0;
float min_giro = 20.0;
float acc_giro = 0.0;

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
  // Interrupción
  if (flag == true) {
    IMU.readAcceleration(x_acel, y_acel, z_acel);
    IMU.readGyroscope(x_giro, y_giro, z_giro);
    // Guardo la aceleracion en z
    za = -y_acel;  // acel en g
    // Guardo el giro en Y
    yg = z_giro;  // giro en dps

    //Serial.println("ok");
  }
  flag = false;

  // Maquina de estados
  // Cálculo de la derivada
  dAcel = (za - za_vec[i]) / tiempo_interrupcion;  // derivada subiendo o bajando < 1000
  dGiro = (yg - yg_vec[i]) / tiempo_interrupcion;  // derivada arriba o en reposo < 1000

  Serial.println(dAcel);
  Serial.println(dGiro);
  Serial.println("");

  // Estado 1: Reposo (Cuando la derivada de la aceleracion es 0 y aceleracion no supera un umbral por arriba (th1) y por abajo (th2))
  if (dAcel < umbral) {
    max_giro = 0;
    min_giro = 20;
    acc_giro = 0;

    s = 0;
    a = 0;
    if (p != 0) {
      tiempo_permanencia = p * tiempo_interrupcion;
    }
    p = 0;
    Serial.println("E1");
  }

  // Estado 2: Subida (Cuando la derivada de la aceleracion es mayor de 0 y aceleracion supera un umbral (th1) y no supera umbral (th3))
  else if (dAcel > umbral) {
    subida[s] = za;
    s++;
    p++;
    Serial.println("E2");
  }

  // Estado 3: Arriba (Cuando la derivada de la aceleracion es 0 y aceleracion supera un umbral por arriba (th4))
  else if (abs(dAcel) < umbral) {
    if (s != 0) {
      tiempo_subida = s * tiempo_interrupcion;
    }
    s = 0;
    arriba[a] = yg;
    a++;
    p++;
    Serial.println("E3");
  }

  // Estado 4: Bajada (Cuando la derivada de la aceleracion es menor de 0 y aceleracion no supera un umbral por arriba y por abajo)
  else if (dAcel < umbral) {
    a = 0;
    p++;

    if (max_giro == 0) {

      length = sizeof(arriba) / sizeof(arriba[0]);
      for (int j = 0; j < length; i++) {
        if (arriba[j] < min_giro) {
          min_giro = arriba[j];
        }
        if (arriba[j] > max_giro) {
          max_giro = arriba[j];
        }
        acc_giro += arriba[j];  //acumulado para el giro medio.
      }

      giro_max = max_giro * (tiempo_interrupcion);
      giro_min = min_giro * (tiempo_interrupcion);
      giro_med = acc_giro / length * tiempo_interrupcion;
      Serial.println("E4");
    }
  }

  if (i == 5000) {
    za_vec[0] = za;
    yg_vec[0] = yg;
    i = 0;

  } else {
    za_vec[i + 1] = za;
    yg_vec[i + 1] = yg;
    i++;
  }


  // Cambiar lo siguiente por lo de bluetooth

  Serial.println(tiempo_subida);
  Serial.println(tiempo_permanencia);
  Serial.println(giro_max);
  Serial.println(giro_min);
  Serial.println(giro_med);
  * /
}
