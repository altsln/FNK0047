/**********************************************************************
* Filename    : 027-02_Bluetooth_BLE_setup
* Description : Setup Bluetooth BLE between ESP32 and
* the mobile phone.
* Auther      : Alternatives Solutions
* Modification: 2026/03/30
**********************************************************************/

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Standard Nordic UART UUIDs (Industry standard for Serial-over-BLE)
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


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
      // if(rxValue[0] == '1') digitalWrite(2, HIGH);
    }
  }
};

BLEServer* pServer = NULL;
BLECharacteristic* pTxCharacteristic = NULL;

void setup() {
  Serial.begin(115200);
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



/* later on revisit this to understand where is the problem

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Unique IDs (You can generate these, but these are standard test ones)
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  setupBLE();
  Serial.println("System Ready!");
}

void loop() {
  // BLE handles most things in the background via interrupts/callbacks!
  delay(2000);
}


void setupBLE() {
  //log info
  Serial.println("Setting up BLE in progress...");

  // 1. Create the BLE Device
  BLEDevice::init("Karl_ESP32_BLE");
  //2. Create the BLE Server
  BLEServer* pServer = BLEDevice::createServer();
  //3. Create the BLE service
  BLEService* pService = pServer->createService(SERVICE_UUID);
  //4. Create a BLE Characteristic (Read and Write permissions)
  BLECharacteristic* pCharacteristic = 
    pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );
  //5. Set a default value
  pCharacteristic->setValue("Alt says Hello");
  //6. Start the service 
  pService->start();
  //start advertising so the phone can find it
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising-> addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  Serial.println("Characteristic defined! Now you can read it on your phone!");
}
*/