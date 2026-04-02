/**********************************************************************
* Filename    : 030_SDCard_read_write__spi
* Description : performing SDCard read write basic operations.
* Just make sure for now that the mount of the card was successful.
* Auther      : Alternatives Solutions. 
* Modification: 2026/04/02
**********************************************************************/

/*
Please on windows 11, format the card as FAT and select 16K
When using FAT32 as system file, you will not have the possibility to select 16k
and when testing this code you will get the following error, which confirms the 
FAT system file not FAT32
====================

Initializing SD_MMC...
E (1329) vfs_fat_sdmmc: mount_to_vfs failed (0xffffffff).
Card Mount Failed
=========================

Error message = E (1329) vfs_fat_sdmmc: mount_to_vfs failed (0xffffffff).
*/

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
}

void loop() {
}
