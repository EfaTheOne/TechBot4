#ifndef MENU_FUNCS_H
#define MENU_FUNCS_H

#include "Menu.h"
#include "WiFiModule.h"
#include "WiFiAdvanced.h"
#include "BLEModule.h"
#include "BLETools.h"
#include "WebPortal.h"
#include "SDUpdater.h"

// Instantiate globals
Input input;
Menu menu;
WiFiModule wifiModule;
WiFiAdvanced wifiAdv;
BLEModule bleModule;
BLETools bleTools;
WebPortal webPortal;
SDUpdater sdUpdater;

// Implementations
void Menu::populateMenus() {
    currentItems.clear();
    switch (state) {
        case MAIN_MENU:
            currentItems.push_back({"WiFi Utils", [](){ menu.setMenu(WIFI_MENU); }});
            currentItems.push_back({"Bluetooth Utils", [](){ menu.setMenu(BT_MENU); }});
            currentItems.push_back({"Pentest Tools", [](){ menu.setMenu(ATTACK_MENU); }});
            currentItems.push_back({"Special Audits", [](){ menu.setMenu(SNIFF_MENU); }}); // Reusing SNIFF_MENU enum for Specials
            currentItems.push_back({"Captive Portal", [](){ webPortal.start("Free WiFi"); menu.drawMenu(); }});
            currentItems.push_back({"Update Firmware", [](){ sdUpdater.updateFromSD("/update.bin"); menu.drawMenu(); }});
            currentItems.push_back({"Reboot", [](){ ESP.restart(); }});
            break;

            
        case WIFI_MENU:
            currentItems.push_back({"Back", [](){ menu.setMenu(MAIN_MENU); }});
            currentItems.push_back({"Traffic Monitor", [](){ wifiModule.runPacketMonitor(); menu.drawMenu(); }});
            currentItems.push_back({"Scan APs", [](){ wifiModule.scanAPs(); menu.drawMenu(); }});
            currentItems.push_back({"Scan Stations", [](){ wifiModule.scanStations(); menu.drawMenu(); }});
            currentItems.push_back({"Sniff Beacons", [](){ wifiModule.sniffBeacons(); menu.drawMenu(); }});
            currentItems.push_back({"Sniff Probes", [](){ wifiModule.sniffProbes(); menu.drawMenu(); }});
            currentItems.push_back({"Sniff Deauths", [](){ wifiModule.sniffDeauths(); menu.drawMenu(); }});
            currentItems.push_back({"Sniff PMKID", [](){ wifiModule.sniffPMKID(); menu.drawMenu(); }});
            break;
            
        case ATTACK_MENU:
            currentItems.push_back({"Back", [](){ menu.setMenu(MAIN_MENU); }});
            currentItems.push_back({"Deauth Test", [](){ wifiAdv.deauthAttack(); menu.drawMenu(); }});
            currentItems.push_back({"Beacon Spam Test", [](){ wifiAdv.beaconSpamRickRoll(); menu.drawMenu(); }});
            currentItems.push_back({"Probe Req Test", [](){ wifiAdv.probeFlood(); menu.drawMenu(); }});
            currentItems.push_back({"AP Clone Test", [](){ wifiAdv.apCloneSpam(); menu.drawMenu(); }});
            break;

        case BT_MENU:
            currentItems.push_back({"Back", [](){ menu.setMenu(MAIN_MENU); }});
            currentItems.push_back({"Scan BLE", [](){ bleModule.scanBLE(); menu.drawMenu(); }});
            currentItems.push_back({"Detect Skimmers", [](){ bleModule.detectSkimmers(); menu.drawMenu(); }});
            currentItems.push_back({"Sniff Airtags", [](){ bleModule.sniffAirtags(); menu.drawMenu(); }});
            currentItems.push_back({"iOS Spam Test", [](){ bleTools.runAttack(SOUR_APPLE); menu.drawMenu(); }});
            currentItems.push_back({"Samsung Test", [](){ bleTools.runAttack(SAMSUNG_SPAM); menu.drawMenu(); }});
            currentItems.push_back({"SwiftPair Test", [](){ bleTools.runAttack(SWIFT_PAIR); menu.drawMenu(); }});
            currentItems.push_back({"Airtag Test", [](){ bleTools.runAttack(AIRTAG_SPOOF); menu.drawMenu(); }});
            break;
            
        case SNIFF_MENU: // Specials
            currentItems.push_back({"Back", [](){ menu.setMenu(MAIN_MENU); }});
            currentItems.push_back({"RSSI Tracker", [](){ wifiAdv.foxHunt("FF:FF:FF:FF:FF:FF"); menu.drawMenu(); }});
            currentItems.push_back({"Terminal Effect", [](){ wifiAdv.matrixEffect(); menu.drawMenu(); }});
            currentItems.push_back({"Defense Monitor", [](){ wifiAdv.defenseMode(); menu.drawMenu(); }});
            break;
    }
}


void Menu::executeItem() {
    if (selectedIndex >= 0 && selectedIndex < currentItems.size()) {
        currentItems[selectedIndex].action();
    }
}

#endif
