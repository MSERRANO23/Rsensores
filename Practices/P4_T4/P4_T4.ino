//Leer datos de acelerometro cada vez que se actualizan
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
BLEService IMUservice("1001");
BLECharacteristic accelData("2001", BLERead | BLENotify, 20);
BLECharacteristic activation("3001", BLEWrite | BLENotify, 20);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;
  //inicializar el BLE
  if (!BLE.begin()) {
    Serial.println("* Starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }
  //inicializar el acelerometro
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  BLE.setLocalName("MARCOS");
  // Añade el servicio al módulo BLE
  BLE.setAdvertisedService(IMUservice);
  // Añade la característica al servicio
  IMUservice.addCharacteristic(accelData);
  IMUservice.addCharacteristic(activation);
  // Añade el servicio al módulo BLE
  BLE.addService(IMUservice);
  // Establece el intervalo de conexión para la conexión BLE
  BLE.setConnectionInterval(8, 8);
  // Habilita el módulo BLE para ser conectable
  BLE.setConnectable(true);
  // Comienza a anunciar la conexión BLE
  BLE.advertise();
}
bool envio = false;
void loop() {
  float acX, acY, acZ;
  // Obtiene el dispositivo central BLE conectado
  BLEDevice central = BLE.central();
  if (central) {
    // Si hay un dispositivo central BLE conectado, entra en un bucle infinito
    while (central.connected()) {
      // Lee los datos del acelerómetro del dispositivo IMU
      if (activation.written()) {
        envio = true;
      }else{
        envio=false;
      }

      if (envio == true) {
        IMU.readAcceleration(acX, acY, acZ);
        // Crea una cadena con los datos del acelerómetro
        String accelString = String(acX) + " , " + String(acY) + " , " + String(acZ);
        // Escribe los datos del acelerómetro en la característica BLE
        accelData.writeValue(accelString.c_str());
        // Espera 7 milisegundos antes de enviar los siguientes datos
        delay(7);
      }
    }
  }
}