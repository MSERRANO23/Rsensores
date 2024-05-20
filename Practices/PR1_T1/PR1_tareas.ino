//Practica 1
//Tarea 1
int analogPin=A0;
//SoftwareSerial Serial;

void setup() {
  // put your setup code here, to run once:
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
}
float valor=0.0;
float anterior, actual;
void loop() {
  // put your main code here, to run repeatedly:
  anterior = millis();
  valor = analogRead(analogPin);
  valor = valor*3.3/1023;
  Serial.print("P1, Valor:");
  Serial.println(valor);
  actual = millis()-anterior;
  delay(1000-actual);
}
