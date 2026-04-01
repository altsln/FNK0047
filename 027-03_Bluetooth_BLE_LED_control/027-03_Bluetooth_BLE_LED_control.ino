/**********************************************************************
* Filename    : 027-03_Bluetooth_BLE_LED_control
* Description : Controlling an LED over Bluetooth LE between ESP32
* and a connected mobile phone.
* Auther      : Alternatives Solutions
* Modification: 2026/03/31
**********************************************************************/

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Standard Nordic UART UUIDs (Industry standard for Serial-over-BLE)
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

const int BUILTIN_LED = 2;
bool deviceConnected = false;

//1. Connection Callback: Handles what happens when phone joins/leaves
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println(">>> Phone Connected!");
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println(">>> Phone Disconnected!");
    // CRITICAL: Restart advertising so you can reconnect without hitting reset
    pServer->getAdvertising()->start();
    Serial.println(">>>>> Advertising restarted...");
  }
};

//2. Data Callback: Handles incoming text from the phone 
class MyCharacteristicCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    String rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {
      Serial.print("BLE Received: ");
      for (int i = 0; i < rxValue.length(); i++) {
        Serial.print(rxValue[i]);
      }
      Serial.println();
            
      // --- ADD YOUR LED LOGIC HERE LATER ---
      // Check the first character of the message
      if ('1' == rxValue[0]) {
        digitalWrite(BUILTIN_LED, LOW); // ON (assuming Active Low like your previous test)
        Serial.println("Action: LED ON");
      } 
      else if ('0' == rxValue[0]) {
        digitalWrite(BUILTIN_LED, HIGH); // OFF
        Serial.println("Action: LED OFF");
      }
    }
  }
};

BLEServer* pServer = NULL;
BLECharacteristic* pTxCharacteristic = NULL;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);  //to force the LED OFF
  setupBLE();
  Serial.println("System Ready! Waiting for a phone to connect...");
}


void loop() {
  // We can put the ESP32 to sleep or do other tasks here.
  // The Callbacks handle the Bluetooth communication!
  delay(1000);
}


void setupBLE() {
  //log info
  Serial.println("Setting up BLE in progress...");

  //a. Create the BLE Device
  BLEDevice::init("Karl_UART_BLE");
  //b. Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  //c. Create the BLE service
  BLEService* pService = pServer->createService(SERVICE_UUID);
  //d. Create TX Characteristic (For ESP32 to send to Phone)
  pTxCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_TX,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
  pTxCharacteristic->addDescriptor(new BLE2902());
  //e. Create RX Characteristic (For Phone to send to ESP32)
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID_RX,
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
  pRxCharacteristic->setCallbacks(new MyCharacteristicCallbacks());
  //f. Start the service 
  pService->start();

  //g. Start advertising
  pServer->getAdvertising()->start();
}
