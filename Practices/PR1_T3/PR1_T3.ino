//Practica 1
//Tarea 3
//Genera una salida PWM a 5kHz proporcional a la lectura del ADC. 
#include "BBTimer.hpp"
#include <mbed.h>
BBTimer my_Timer(BB_TIMER0);
int period = 200; //activacion de la interrupcion
bool flag = false;
int pinLeido = A0;
//int salida = D2;
float duty = 0.0;
int val_read;

mbed::PwmOut pwmPin(digitalPinToPinName(D5));

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLeido,INPUT);
  pinMode(D5,OUTPUT);
  my_Timer.setupTimer(period, t0Callback);
	my_Timer.timerStart();
  pwmPin.period(0.0002);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag == true){
    val_read = analogRead(pinLeido);
    //Serial.println(val_read);
    duty = val_read/1023.0; //transformacion de lectura de ADC a tiempo
    Serial.println(duty);
    //secuencia de generación del duty
    //pwmPin.write(duty);
    pwmPin.write(duty);
    //Tiempo que debe estar en ON//Tiempo que debe de estar en OFF, valor maximo son 200us
    flag = false;
  }
}

void t0Callback(){
  flag = true;
}