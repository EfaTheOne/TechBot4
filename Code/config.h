#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==============================
// Hardware Pinout Definitions
// ==============================

// Display (ST7789)
#define TFT_MISO    -1 // Not used for ST7789
#define TFT_MOSI    23
#define TFT_SCLK    18
#define TFT_CS      5
#define TFT_DC      2
#define TFT_RST     4
#define TFT_BL      15

// SD Card
#define SD_CS       16
#define SD_MOSI     23
#define SD_MISO     19
#define SD_SCK      18

// Buttons (Active LOW, Internal Pullups)
#define BTN_UP      12
#define BTN_DOWN    13
#define BTN_LEFT    14
#define BTN_RIGHT   27
#define BTN_SELECT  26

// ==============================
// Feature Configuration
// ==============================

// WiFi Features
#define HAS_WIFI_SCAN_AP        true
#define HAS_WIFI_SCAN_STATION   true
#define HAS_WIFI_ATTACK_DEAUTH  true // Educational use only
#define HAS_WIFI_ATTACK_BEACON  true // Educational use only
#define HAS_WIFI_ATTACK_PROBE   true // Educational use only
#define HAS_WIFI_SNIFF_PMKID    true
#define HAS_WIFI_SNIFF_PROBE    true
#define HAS_WIFI_SNIFF_PWN      true // Pwnagotchi detection
#define HAS_WIFI_SNIFF_ESP      true // ESP detection
#define HAS_WIFI_SNIFF_RAW      true

// Bluetooth Features
#define HAS_BT_SCAN_BLE         true
#define HAS_BT_SCAN_CLASSIC     true // May require dual mode
#define HAS_BT_ATTACK_SOURAPPLE true // iOS Sour Apple
#define HAS_BT_ATTACK_SWIFT     true // Swift Pair spam
#define HAS_BT_ATTACK_SAMSUNG   true
#define HAS_BT_SNIFF_SKIMMER    true

// Hardware Features
#define HAS_SCREEN              true
#define HAS_SD                  true
#define HAS_BUTTONS             true
#define HAS_GPS                 false // Not in provided pinout, set to true if added via UART
#define HAS_NEOPIXEL            false // Not in provided pinout

// System Settings
#define SCREEN_WIDTH            320
#define SCREEN_HEIGHT           240
#define SD_LIMIT_SIZE           false // Support 32GB

#endif
