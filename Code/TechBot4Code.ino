
#include "config.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h> // Graphics and font library

#include "config.h"
#include "MenuFunctions.h" 
// MenuFunctions includes Menu.h, WiFiModule.h, BLEModule.h, Input.h and instantiates them

void setup() {
  Serial.begin(115200);
  
  // HAL Setup
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  input.begin();
  bleModule.init();
  bleTools.init(); // Initialize PenTest tools
  wifiAdv.init();
  
  // SD Setup
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if(!SD.begin(SD_CS)) {
      Serial.println("SD Failed");
  }

  // Draw Initial Menu
  menu.begin();
}

void loop() {
  menu.update();
  delay(10); // Small delay to prevent watchdog starvation if loop is tight
}

// Remove old stubs

