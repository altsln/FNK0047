/**********************************************************************
* Filename    : 030-01_SDCard_CRUD_operations
* Description : performing SDCard read write basic operations.
* Auther      : Alternatives Solutions.
* Modification: 2026/04/02
**********************************************************************/

#include "FS.h"
#include "SD_MMC.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Initializing SD_MMC...");

  // Using 'true' for 1-bit mode often helps with stability on WROVER boards
  // because it prevents conflicts with the camera pins.
  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.println("Success! Card Mounted via SDMMC.");
  
  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

  //CRUD Operations
  // 1. CREATE & WRITE
  File file = SD_MMC.open("/karl_test.txt", FILE_WRITE);
  if(file){
    file.println("SDMMC Write Successful!");
    file.close();
    Serial.println("File created and written.");
  }

  // 2. READ
  fileRead();

  // 3. UPDATE append
  fileUpdate_Append();
  fileRead();
  
  // 4. DELETE
  if(SD_MMC.remove("/karl_test.txt")){
    Serial.println("\nFile deleted successfully.");
  }

  fileRead();
}

void loop() {
}


void fileRead() {
  
  // 2. READ
  File file = SD_MMC.open("/karl_test.txt");
  if(file){
    Serial.print("Reading file content: ");
    while(file.available()){
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.print("File does not exist!");
  }
}

void fileUpdate_Seek() {
  File file = SD_MMC.open("/karl_test.txt", FILE_WRITE);
  if(file){
      file.seek(10); // Move the "cursor" to the 10th byte
      file.print("NEW_DATA"); 
      file.close();
  }
}

void fileUpdate_Append() {
  //3.Update
  // Use FILE_APPEND instead of FILE_WRITE
  File file = SD_MMC.open("/karl_test.txt", FILE_APPEND);
  if(file){
      file.println("This is an update! Added to the end.");
      file.close();
      Serial.println("File Appended.");
  }

}