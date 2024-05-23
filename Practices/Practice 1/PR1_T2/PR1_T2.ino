//Practica 1
//tarea 2
//Utilizando los timers hardware genera una interrupción cada 10 segundos que lea el ADC 
//y lo muestre por pantalla.
#include "BBTimer.hpp"
int analogPin=A0;
BBTimer my_Timer(BB_TIMER0);
float valor=0.0;
bool flag = false;
int period = 10000000;
void setup() {
  // put your setup code here, to run once:
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
  my_Timer.setupTimer(period, t0Callback);
	my_Timer.timerStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag==true){
    valor = analogRead(analogPin);
    valor = valor*3.3/1023;
    Serial.println(valor);
    flag = false;
  }
  //Serial.println(".....");
  delay(4000);
}

void t0Callback(){
  flag = true;
}


