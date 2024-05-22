
#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
BLEService ledService("180A");
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  if (!BLE.begin()) {
    Serial.println("* Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("MARCOS"); 
  BLE.setAdvertisedService(ledService);

  Serial.println("Arduino Nano 33 BLE Sense (Central Device)");
  Serial.println(" ");  

  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characteristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();


  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);            // turn on the LED to indicate the connection

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        switch (switchCharacteristic.value()) {   // any value other than 0
          case 01:
            Serial.println("Red LED ON");
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, LOW);            // will turn the LED on
            digitalWrite(LEDG, HIGH);         // will turn the LED off
            digitalWrite(LEDB, HIGH);         // will turn the LED off
            break;
          case 02:
            Serial.println("Green LED ON");
            digitalWrite(LEDR, HIGH);         // will turn the LED off
            digitalWrite(LEDG, LOW);        // will turn the LED on
            digitalWrite(LEDB, HIGH);        // will turn the LED off
            break;
          case 03:
            Serial.println("Blue LED ON");
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, HIGH);         // will turn the LED off
            digitalWrite(LEDG, HIGH);       // will turn the LED off
            digitalWrite(LEDB, LOW);         // will turn the LED on
            break;
          case 04:
            Serial.println("All LEDs ON");
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, LOW);         // will turn the LED ON
            digitalWrite(LEDG, LOW);       // will turn the LED ON
            digitalWrite(LEDB, LOW);         // will turn the LED ON
            break;
          case 05:
            Serial.println(" LEDs ON");
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, HIGH);         // will turn the LED OFF
            digitalWrite(LEDG, LOW);       // will turn the LED ON
            digitalWrite(LEDB, LOW);         // will turn the LED ON
            break;
          case 06:
            Serial.println(" LEDs ON");
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, LOW);        // will turn the LED ON
            digitalWrite(LEDG, HIGH);       // will turn the LED OFF
            digitalWrite(LEDB, LOW);        // will turn the LED ON
            break;
          case 07:
            Serial.println(" LEDs ON");
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, LOW);         // will turn the LED ON
            digitalWrite(LEDG, LOW);       // will turn the LED ON
            digitalWrite(LEDB, HIGH);         // will turn the LED ON
            break;
          default:
            Serial.println(F("All LEDs OFF"));
            digitalWrite(LED_BUILTIN, HIGH);
            digitalWrite(LEDR, HIGH);          // will turn the LED off
            digitalWrite(LEDG, HIGH);        // will turn the LED off
            digitalWrite(LEDB, HIGH);         // will turn the LED off
            break;
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, LOW);         // when the central disconnects, turn off the LED
    digitalWrite(LEDR, HIGH);          // will turn the LED off
    digitalWrite(LEDG, HIGH);        // will turn the LED off
    digitalWrite(LEDB, HIGH);         // will turn the LED off
  }
}
