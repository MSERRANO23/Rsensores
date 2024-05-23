#include <Wire.h>
#include <Arduino_LSM9DS1.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;

  Wire.begin(8);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }
}

float X = 0.0, Y = 0.0, Z = 0.0;

void loop() {
  // put your main code here, to run repeatedly:
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(X, Y, Z);
    Serial.print(X);
    Serial.print('\t');
    Serial.print(Y);
    Serial.print('\t');
    Serial.println(Z);
  }
  Wire.beginTransmission(8);  // transmit to device #8
  Wire.write(int(X));         // sends the given value
  Wire.write(int(Y));
  Wire.write(int(Z));
  Wire.endTransmission();  // stop transmitting
  delay(500);
}
