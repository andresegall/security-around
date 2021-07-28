#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define RELAY_ON   HIGH
#define RELAY_OFF  LOW     

// Relay pin number
//pino do RELAY
#define RELAY   2


int scanTime = 5000; //Em Segundos
int nivelRSSI = -30; //Ajustar conforme o ambiente
String dispositivosAutorizados = "58:d9:c3:43:e8:ab"; //MAC do seu dispositov BLE
bool dispositivoPresente = false;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT); //  Initialize the relay pin as an output.
  BLEDevice::init("");
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      String dispositivosEncontrados = advertisedDevice.getAddress().toString().c_str();
      if (dispositivosEncontrados == dispositivosAutorizados  
                    && advertisedDevice.getRSSI() > nivelRSSI) {
        dispositivoPresente = true;
        
      } else {
        dispositivoPresente = false;
        
      }
      if (advertisedDevice.getRSSI() > nivelRSSI && advertisedDevice.getRSSI() != 0) 
  {
    digitalWrite(RELAY, RELAY_OFF); //liga o relé
    Serial.println("ON");
    Serial.println(advertisedDevice.getRSSI());
    Serial.println(advertisedDevice.getAddress().toString().c_str());
  }
  else 
  {
    digitalWrite(RELAY, RELAY_ON); //desliga o relé
    Serial.println("OFF");
    Serial.println(advertisedDevice.getRSSI());
     Serial.println(advertisedDevice.getAddress().toString().c_str());
  }
    }
};

void scanBLE() {
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
}



void loop() {
 
  scanBLE();
  delay(1000);
 
}
