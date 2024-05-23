//Practica 1
//Tarea 4
#include <string.h>
#include "BBTimer.hpp"
#include <mbed.h>

bool flag = false;
BBTimer my_Timer(BB_TIMER0);
int period = 10000000;
int pinLeido = A0;
int val_read;
mbed::PwmOut pwmPin(digitalPinToPinName(D5));
int valor = 0;

void setup() {
  Serial.begin(9600);
  my_Timer.setupTimer(period, t0Callback);
	my_Timer.timerStart();
  pinMode(pinLeido,INPUT);
}

char leido[15];
char adc[] = "ADC";
char adc_x[] = "(";
char pwm[] = "PWM(";

void loop() {
  
  if(Serial.available()>0){
    Serial.readBytesUntil('\n', leido, sizeof(leido));
    
    //readSerial(leido);
    //ver posición de la cadena para comparar
    char *posicion_1 = strstr(leido, adc);
    char *posicion_2 = strstr(leido,adc_x);
    char *posicion_3 = strstr(leido,pwm);

    if(posicion_1 != NULL){
      int indice = posicion_1 - leido;  // Calcular el índice de la letra encontrada
      Serial.print("La cadena a buscar es: ");
      Serial.print(adc);
      Serial.print("' se encontró en el índice ");
      Serial.println(indice);
      Serial.println("1");
      val_read = analogRead(pinLeido);
    }else{
      if(posicion_2 != NULL){
        char subcadena[5];
        int indice = posicion_2 - leido;  // Calcular el índice de la letra encontrada
        Serial.print("La cadena a buscar es: ");
        Serial.print(adc_x);
        strncpy(subcadena, &leido[5],5);
        //my_Timer.updatePeriod(subcadena);
        Serial.println(subcadena);
        Serial.print("' se encontró en el índice ");
        //valor = leido.substring(leido[3], leido[15]);
        Serial.println(indice);
        Serial.println("2");
      }
      if(posicion_3 != NULL){
        char subcadena[2];
        int indice = posicion_3 - leido;  // Calcular el índice de la letra encontrada
        Serial.print("La cadena a buscar es: ");
        Serial.print(pwm);
        strncpy(subcadena, &leido[4],1);
        Serial.println("3");
        Serial.print("' se encontró en el índice ");
        Serial.println(indice);
        val_read = analogRead(pinLeido);
      }
    }
  }
  
//usar substring para elegir los caracteres que se quieren comparar
//en primer lugar ver la longitud para comparar con los 3 casos, ADC, ADC(x), PWM(x)
//PAra ver si es PWM solo hay que mirar la posición de la P
//en el resto de casos hay que ver si hay parentesis y el numero que hay entre ellos
}

int readSerial(char result[]){
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}

void t0Callback(){
  flag = true;
}