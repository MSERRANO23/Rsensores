//Haz que el módulo lleve a cabo un proceso de advertising 
//en el que aparezca tu nombre dentro del campo UUID como identificativo.

#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  if (!BLE.begin()) {
    Serial.println("* Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("MARCOS"); 
  BLE.advertise();

  Serial.println("Arduino Nano 33 BLE Sense (Central Device)");
  Serial.println(" ");  
}

void loop() {
  // put your main code here, to run repeatedly:

}
