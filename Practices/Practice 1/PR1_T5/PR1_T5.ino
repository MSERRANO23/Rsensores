#include <Wire.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Wire.begin(8);
}

void loop() {
  // put your main code here, to run repeatedly:

}
