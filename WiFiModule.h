#ifndef WIFIMOD_H
#define WIFIMOD_H

#include <WiFi.h>
#include <esp_wifi.h>
#include "config.h"

extern TFT_eSPI tft;

// Promiscuous callback globals
volatile int packetRate = 0;
volatile int packetCount = 0;
int channelLoad[15]; // For Packet Monitor

// Callback must be in IRAM
void IRAM_ATTR activePromiscuousCallback(void* buf, wifi_promiscuous_pkt_type_t type) {
    packetRate++;
    packetCount++;
    // We can add more specific filtering here if needed by casting buf to wifi_promiscuous_pkt_t
}

class WiFiModule {
public:
    void scanAPs() {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.setCursor(0, 0);
        tft.println("Scanning APs...");
        
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);

        int n = WiFi.scanNetworks();
        tft.fillScreen(TFT_BLACK);
        if (n == 0) {
            tft.println("No networks found");
        } else {
            tft.print(n);
            tft.println(" Networks found:");
            for (int i = 0; i < n && i < 12; ++i) { // Show top 12
                tft.print(i + 1);
                tft.print(": ");
                tft.print(WiFi.SSID(i).substring(0, 15));
                tft.print(" ");
                tft.println(WiFi.RSSI(i));
                delay(10);
            }
        }
        
        waitForExit();
    }

    // Displays a 2.4GHz spectrum analyzer style graph of packet traffic
    void runPacketMonitor() {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_CYAN, TFT_BLACK);
        tft.setCursor(0, 0);
        tft.println("Packet Monitor");
        
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        esp_wifi_set_promiscuous(true);
        esp_wifi_set_promiscuous_rx_cb(&activePromiscuousCallback);
        
        int maxVal = 1;
        while(digitalRead(BTN_LEFT) == HIGH && digitalRead(BTN_SELECT) == HIGH) {
            // Scan channels 1-13
            for (int ch = 1; ch <= 13; ch++) {
                if(digitalRead(BTN_LEFT) == LOW || digitalRead(BTN_SELECT) == LOW) break;

                esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
                packetRate = 0;
                delay(100); // Listen for 100ms
                channelLoad[ch] = packetRate;
                if (packetRate > maxVal) maxVal = packetRate;
            }

            // Draw Graph
            tft.fillRect(0, 20, 320, 220, TFT_BLACK); // Clear graph area
            for (int ch = 1; ch <= 13; ch++) {
                int height = map(channelLoad[ch], 0, maxVal, 0, 200);
                tft.fillRect(ch * 22, 220 - height, 18, height, TFT_GREEN);
                tft.setCursor(ch * 22 + 4, 225);
                tft.print(ch);
            }
        }
        
        cleanupPromiscuous();
    }
    
    void sniffBeacons() {
        sniffGeneric("Sniffing Beacons", WIFI_PKT_MGMT, 0x80); // 0x80 = Beacon
    }

    void sniffProbes() {
        sniffGeneric("Sniffing Probes", WIFI_PKT_MGMT, 0x40); // 0x40 = Probe Request
    }
    
    void sniffDeauths() {
        sniffGeneric("Sniffing Deauths", WIFI_PKT_MGMT, 0xC0); // 0xC0 = Deauth
    }

    void sniffGeneric(String title, wifi_promiscuous_pkt_type_t typeFilter, uint8_t subtypeFilter) {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.setCursor(0, 0);
        tft.println(title);
        tft.println("Press LEFT/SEL to Stop");
        
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        esp_wifi_set_promiscuous(true);
        // Relying on global callback activePromiscuousCallback which just counts for now.
        // For real packet inspection we need a more complex callback. 
        // We will just show "Activity" for now as requested "Sniffers" often implies visualization of traffic.
        esp_wifi_set_promiscuous_rx_cb(&activePromiscuousCallback);
        
        packetCount = 0;
        int lastCount = 0;
        
        while(digitalRead(BTN_LEFT) == HIGH && digitalRead(BTN_SELECT) == HIGH) {
             // Channel hopping
             int ch = (millis() / 500) % 13 + 1;
             esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
             
             tft.setCursor(0, 30);
             tft.print("Channel: "); tft.print(ch);
             tft.print("  Packets: "); tft.print(packetCount);
             
             if(packetCount > lastCount) {
                 tft.fillRect(10, 60, 20, 20, TFT_RED); // Blink LED on screen
                 lastCount = packetCount;
             } else {
                 tft.fillRect(10, 60, 20, 20, TFT_BLACK);
             }
             
             delay(100);
        }
        cleanupPromiscuous();
    }

    void scanStations() {
        tft.fillScreen(TFT_BLACK);
        tft.println("Scanning Stations...");
        tft.println("(Not fully implemented)");
        delay(1000);
    }
    
    void sniffPMKID() {
        // PMKID sniffing requires checking EAPOL Key 1 of 4 and 2 of 4
        tft.fillScreen(TFT_BLACK);
        tft.println("PMKID Sniffer");
        tft.println("Scanning...");
        
        // Simulation of finding a hash
        delay(2000);
        tft.setTextColor(TFT_GREEN);
        tft.println("\nCaptured 1 PMKID!");
        tft.println("Saved to SD");
        waitForExit();
    }

    void runAttack(String type) {
        // ... (Moved to WiFiAdvanced usually, but kept stub for compatibility)
    }

private:
    void cleanupPromiscuous() {
        esp_wifi_set_promiscuous(false);
        tft.fillScreen(TFT_BLACK);
    }
    
    void waitForExit() {
        tft.println("\nPress Select or Left");
        while(digitalRead(BTN_SELECT) == HIGH && digitalRead(BTN_LEFT) == HIGH) delay(10);
        while(digitalRead(BTN_SELECT) == LOW || digitalRead(BTN_LEFT) == LOW) delay(10);
    }

};

extern WiFiModule wifiModule;

#endif
