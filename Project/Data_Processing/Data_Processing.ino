#include <Arduino_LSM9DS1.h>
#include <BBTimer.hpp>

// Variables
int estado = 0;
int i = 0;
int a = 0;
int s = 0;

// Umbrales
float th1 = -0.1;
float th2 = 0.1;
float th3 = 0.25;

// Generacion del TIMER
BBTimer my_t0(BB_TIMER0);
int tiempo_interrupcion = 2;  //Frecuencia 500 Hz
bool falg = false;

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
    za = -y_acel;
    // Guardo el giro en Y
    yg = z_giro;
  }
  flag = false;

  // Maquina de estados
  // Cálculo de la derivada
  dAcel = (za - za[i]) / tiempo_interrupcion; // derivada subiendo o bajando < 1000
  dGiro = (yg - yg[i]) / tiempo_interrupcion; // derivada arriba o en reposo < 1000

  // Estado 1: Reposo (Cuando la derivada de la aceleracion es 0 y aceleracion no supera un umbral por arriba (th1) y por abajo (th2))
  if(dGiro < 1000 || estado == 1){

  }

  // Estado 2: Subida (Cuando la derivada de la aceleracion es mayor de 0 y aceleracion supera un umbral (th1) y no supera umbral (th3))
  if(dAcel < 1000 || estado == 2){
    subida[s] = za;
    s++;

    if(){
      estado = 3;
      subida[s]
    }
  }

  // Estado 3: Arriba (Cuando la derivada de la aceleracion es 0 y aceleracion supera un umbral por arriba (th4))
  if(dGiro < 1000 || estado == 3){
    s = 0;
    arriba[a] = yg;
    a++;
  }

  // Estado 4: Bajada (Cuando la derivada de la aceleracion es menor de 0 y aceleracion no supera un umbral por arriba y por abajo)
  if(dAcel < 1000 || estado == 4){
    a = 0;    
    // Calculo del giro maximo
    float max = 0;
    float min = 20;
    float acc = 0;
    int t_max = 0;

    for(int j = 0; j<length(arriba)-1;i++){
      if (arriba[j] < min){
        min = 
      }
      if (arriba[j] > max){
        max = arriba[j];
        t_max = j;
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
}