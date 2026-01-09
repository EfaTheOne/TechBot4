#ifndef SD_UPDATER_H
#define SD_UPDATER_H

#include <Update.h>
#include "config.h"

extern TFT_eSPI tft;

class SDUpdater {
public:
    void updateFromSD(String filename) {
        File updateBin = SD.open(filename);
        if (updateBin) {
            if (updateBin.isDirectory()) {
                tft.println("Error: Directory");
                updateBin.close();
                return;
            }

            size_t updateSize = updateBin.size();

            if (updateSize > 0) {
                tft.fillScreen(TFT_BLACK);
                tft.setCursor(0, 0);
                tft.println("Starting Update...");
                tft.print("File: "); tft.println(filename);
                
                if (Update.begin(updateSize)) {
                    size_t written = Update.writeStream(updateBin);
                    if (written == updateSize) {
                        tft.println("Written: " + String(written) + " success");
                    } else {
                        tft.println("Written only : " + String(written) + "/" + String(updateSize));
                    }
                    if (Update.end()) {
                        tft.println("OTA Done!");
                        if (Update.isFinished()) {
                            tft.println("Rebooting...");
                            delay(1000);
                            ESP.restart();
                        } else {
                            tft.println("Update Failed");
                        }
                    } else {
                        tft.println("Error Occurred. Error #: " + String(Update.getError()));
                    }

                } else {
                    tft.println("Not enough space to begin OTA");
                }
            } else {
                tft.println("Error: Empty file");
            }
            updateBin.close();
        } else {
            tft.println("Could not load " + filename);
        }
        delay(5000); // Let user see result
    }
};

extern SDUpdater sdUpdater;

#endif
