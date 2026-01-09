#ifndef BLEMOD_H
#define BLEMOD_H

#include <NimBLEDevice.h>
#include "config.h"

extern TFT_eSPI tft;

class BLEModule {
public:
    void init() {
        NimBLEDevice::init("TechBot4");
    }

    void detectSkimmers() {
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(0, 0);
        tft.println("Scanning for Skimmers...");
        
        NimBLEScan* pScan = NimBLEDevice::getScan();
        pScan->setActiveScan(true);
        if(pScan->start(5, false)) {
            NimBLEScanResults results = pScan->getResults();
            tft.fillScreen(TFT_BLACK);
            tft.println("Potential Skimmers:");
            
            bool found = false;
            for(int i = 0; i < results.getCount(); i++) {
                const NimBLEAdvertisedDevice* device = results.getDevice(i);
                String name = device->getName().c_str();
                // Common skimmer module names
                if(name.indexOf("HC-05") >= 0 || name.indexOf("HC-06") >= 0 || name.indexOf("HCO5") >= 0) {
                     tft.setTextColor(TFT_RED, TFT_BLACK);
                     tft.print("SUSPECT: "); tft.println(name);
                     tft.print("RSSI: "); tft.println(device->getRSSI());
                     found = true;
                }
            }
            if(!found) tft.println("No common skimmers found.");
        }
        waitForExit();
    }

    void sniffAirtags() {
        tft.fillScreen(TFT_BLACK);
        tft.println("Sniffing Airtags...");
        
        NimBLEScan* pScan = NimBLEDevice::getScan();
        pScan->setActiveScan(true);
        // Continuous scan loop
        while(digitalRead(BTN_LEFT) == HIGH && digitalRead(BTN_SELECT) == HIGH) {
            if(pScan->start(2, false)) { // Short scans
                NimBLEScanResults results = pScan->getResults();
                for(int i = 0; i < results.getCount(); i++) {
                    const NimBLEAdvertisedDevice* device = results.getDevice(i);
                    std::string mfgData = device->getManufacturerData();
                    
                    // Apple company ID 0x004C (Little Endian: 4C 00)
                    if(mfgData.length() >= 3 && mfgData[0] == 0x4C && mfgData[1] == 0x00) {
                        // Check for Airtag type byte (simplified)
                         tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
                         tft.print("APPLE: ");
                         tft.println(device->getAddress().toString().c_str());
                         tft.print("RSSI: "); tft.println(device->getRSSI());
                    }
                }
                delay(10);
            }
        }
        tft.fillScreen(TFT_BLACK);
    }
    
    // Legacy scan
    void scanBLE() {
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(0, 0);
        tft.println("Scanning BLE...");
        
        NimBLEScan* pScan = NimBLEDevice::getScan();
        pScan->setActiveScan(true);
        if(pScan->start(5, false)) {
            NimBLEScanResults results = pScan->getResults();
            
            tft.fillScreen(TFT_BLACK);
            tft.println("BLE Devices:");
            for(int i = 0; i < results.getCount() && i < 8; i++) {
                const NimBLEAdvertisedDevice* device = results.getDevice(i);
                tft.print(i+1); tft.print(": ");
                tft.print(device->getName().c_str());
                tft.print(" ");
                tft.println(device->getRSSI());
            }
        } else {
             tft.println("Scan failed!");
        }
        
        waitForExit();
    }

    // Moved attacks to BLEAttacks.h but kept stub if needed, 
    // though menu calls BLEAttacks.h directly.

private:
    void waitForExit() {
        tft.println("\nPress LEFT/SEL to Return");
        while(digitalRead(BTN_SELECT) == HIGH && digitalRead(BTN_LEFT) == HIGH) delay(10);
        while(digitalRead(BTN_SELECT) == LOW || digitalRead(BTN_LEFT) == LOW) delay(10);
    }
};

extern BLEModule bleModule;

#endif
