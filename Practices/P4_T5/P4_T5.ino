//chat usando bluetooth entre ESP32 con perfil SSP con una APP en movil

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
String device = "MARCOS-BT";

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device);
  while(!SerialBT.connected()){
    SerialBT.connect(); // si no se puede conectar seguir intentandolo
  }
}

void loop(){
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }
  if(SerialBT.available()){
    Serial.write(SerialBT.read());
  }
  delay(100);
}