/**********************************************************************
  Filename    : 031-02_SDCard_music_player__different_lib
  Description : Play music from the sd card.
  Auther      : Alternatives Solutions.
  Modification: 2026/04/05
**********************************************************************/
//please include this lib  https://github.com/schreibfaul1/ESP32-audioI2S
//or install lib from Arduino "ESP32-audioI2S" (by Schreibfaul1)

#include "Arduino.h"
#include "Audio.h"
#include "SD_MMC.h"

#define SD_MMC_CMD 15
#define SD_MMC_CLK 14
#define SD_MMC_D0  2

// Hardware Pins for your S3 Wrover
#define I2S_DOUT      22
#define I2S_BCLK      26
#define I2S_LRCK      25 // Also known as WS

Audio audio;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Initializing SD_MMC...");
  if (!isSDInitialized()) {
    return;
  }
  Serial.println("Success! Card Mounted via SDMMC.");
  printCardSize();

  // 2. Configure I2S Pins
  audio.setPinout(I2S_BCLK, I2S_LRCK, I2S_DOUT);
  // 3. Set Volume (0 to 21)
  audio.setVolume(12); 
  // 4. Start Playback
  // This library handles ID3 tags and sample rates (44.1 vs 48) automatically
  audio.connecttoFS(SD_MMC, "/SD/Massacre.mp3");
  Serial.println("--- ESP32-audioI2S Started ---");
}

void loop() {
    // This is the "Engine" - it must run as fast as possible
    audio.loop(); 
}

bool isSDInitialized() {
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {
    Serial.println("Card Mount Failed");
    return false;
  }
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
      Serial.println("No SD_MMC card attached");
      return false;
  }
  printCardType(cardType);
  return true;
}

void printCardType(uint8_t& cType) {
  Serial.print("SD_MMC Card Type: ");
  if(cType == CARD_MMC){
      Serial.println("MMC");
  } else if(cType == CARD_SD){
      Serial.println("SDSC");
  } else if(cType == CARD_SDHC){
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }
}

void printCardSize() {
  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);
}



// Optional: Useful diagnostics to see what's happening
void audio_info(const char *info){
    Serial.print("audio_info: "); Serial.println(info);
}

void audio_bitrate(const char *info){
    Serial.print("bitrate:    "); Serial.println(info);
}

void audio_id3data(const char *info){  // identifies metadata
    Serial.print("id3data:    "); Serial.println(info);
}

void audio_eof_mp3(const char *info){  // end of file
    Serial.print("eof_mp3:    "); Serial.println(info);
}