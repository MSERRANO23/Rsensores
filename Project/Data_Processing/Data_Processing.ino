#include <Arduino_LSM9DS1.h>
#include <BBTimer.hpp>

// Variables
int estado = 0;
int i = 0;
int a = 0;
int s = 0;
int p = 0;

// Derivadas
int dAcel = 0;
int dGiro = 0;

// Umbrales
int umbral = 1000;

// Generacion del TIMER
BBTimer my_t0(BB_TIMER0);
int tiempo_interrupcion = 2;  //Frecuencia 500 Hz
bool flag = false;

//Variables acelerometro
float x_acel, y_acel, z_acel, za;
float za_vec[5000];  //, ya[15000];

//Variables giroscopio
float x_giro, y_giro, z_giro, yg;
float yg_vec[5000];  //, zg[15000];

// Rutina de interrupcion cada 2 ms
void inter() {
  flag = true;
}

void setup() {
  Serial.begin(9600);
  IMU.begin();
  my_t0.setupTimer(tiempo_interrupcion, inter);
  my_t0.timerStart();
}

void loop() {

  // Interrupción
  if(flag == true){
    IMU.readAcceleration(x_acel, y_acel, z_acel);
    IMU.readGyroscope(x_giro, y_giro, z_giro);
    // Guardo la aceleracion en z
    za = -y_acel; // acel en g
    // Guardo el giro en Y
    yg = z_giro; // giro en dps
  }
  flag = false;

  // Maquina de estados
  // Cálculo de la derivada
  dAcel = (za - za[i]) / tiempo_interrupcion; // derivada subiendo o bajando < 1000
  dGiro = (yg - yg[i]) / tiempo_interrupcion; // derivada arriba o en reposo < 1000

  // Estado 1: Reposo (Cuando la derivada de la aceleracion es 0 y aceleracion no supera un umbral por arriba (th1) y por abajo (th2))
  if(dGiro < 1000){
    s = 0;
    a = 0;
    if (p != 0){
      tiempo_permanencia = p * t_interrupcion;
    }
    p = 0;

  }

  // Estado 2: Subida (Cuando la derivada de la aceleracion es mayor de 0 y aceleracion supera un umbral (th1) y no supera umbral (th3))
  if(dAcel < 1000){
    subida[s] = za;
    s++;
    p++;
  }

  // Estado 3: Arriba (Cuando la derivada de la aceleracion es 0 y aceleracion supera un umbral por arriba (th4))
  if(dGiro < 1000){
    if (s != 0){
      tiempo_subida = s * t_interrupcion;
    }
    s = 0;
    arriba[a] = yg;
    a++;
    p++;
  }

  // Estado 4: Bajada (Cuando la derivada de la aceleracion es menor de 0 y aceleracion no supera un umbral por arriba y por abajo)
  if(dAcel < 1000){
    a = 0;    
    p++;
    // Calculo del giro maximo
    float max = -0.5;
    float min = 20;
    float acc = 0;

    for(int j = 0; j<length(arriba)-1;i++){
      if (arriba[j] < min){
        min = arriba[j];
      }
      if (arriba[j] > max){
        max = arriba[j];
      }
      acc += arriba[j];
    }

    giro_max = max * (t_interrupcion);
    giro_min = min * (t_interrupcion);
    giro_med = acc / length(arriba) * t_interrupcion;
  }

  za[i+1] = za;
  yg[i+1] = yg;
  i++;

  // Cambiar lo siguiente por lo de bluetooth

  serial.println(tiempo_subida);
  serial.println(tiempo_permanencia);
  serial.println(giro_max);
  serial.println(giro_min);
  serial.println(giro_med);

}
