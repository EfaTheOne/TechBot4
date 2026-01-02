#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Pin Configuration (EXACT Match)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI   23 // DIN pin
#define OLED_CLK    18 // CLK pin
#define OLED_DC     17 // D/C pin
#define OLED_CS      5 // CS pin
#define OLED_RESET  16 // RES pin

// Joystick Pin Configuration (EXACT)
#define JOY_X 36  // VRx
#define JOY_Y 39  // VRy
#define JOY_SW 34 // SW (Button)

// Initialize OLED with Hardware SPI (SAME as test)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Marauder variables
int menuIndex = 0;
bool inScanMode = false;
unsigned long scanTimer = 0;
int apCount = 0;
int stationCount = 0;
const int NUM_MENU_ITEMS = 9;

void setup() {
  Serial.begin(115200);
  
  // Setup Joystick button with internal pull-up (SAME as test)
  pinMode(JOY_SW, INPUT_PULLUP);

  // Initialize OLED (EXACT same check as test)
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed. Check wiring!"));
    for(;;);
  }

  // Marauder boot screen
  bootScreen();
  Serial.println("ESP32 Marauder Ready!");
}

void loop() {
  // Read Joystick Values (SAME method as test)
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  int swVal = digitalRead(JOY_SW);

  // Handle menu navigation
  handleJoystick(xVal, yVal, swVal);
  
  // Clear display for new data (SAME as test)
  display.clearDisplay();
  
  if(inScanMode) {
    drawScanResults();
  } else {
    drawMarauderMenu();
  }
  
  display.display();
  delay(80);
}

void bootScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 10);
  display.println("ESP32");
  display.setCursor(8, 25);
  display.println("MARAUDER");
  display.setCursor(40, 40);
  display.println("v2.1");
  display.setCursor(20, 55);
  display.println("SPI READY");
  display.display();
  delay(2500);
}

void handleJoystick(int x, int y, int sw) {
  static int lastY = 2048;
  static bool lastSw = HIGH;
  static unsigned long debounce = 0;
  
  if(millis() - debounce < 150) return;
  
  // Menu navigation (Y-axis up/down)
  if(y > 2300 && lastY <= 2300) {  // Down
    menuIndex = (menuIndex + 1) % NUM_MENU_ITEMS;
  } else if(y < 1800 && lastY >= 1800) {  // Up
    menuIndex = (menuIndex - 1 + NUM_MENU_ITEMS) % NUM_MENU_ITEMS;
  }
  lastY = y;
  
  // Button press (LOW = pressed)
  if(sw == LOW && lastSw == HIGH) {
    if(inScanMode) {
      inScanMode = false;  // Exit scan
    } else {
      startScan();  // Enter scan mode
    }
  }
  lastSw = sw;
  debounce = millis();
}

void startScan() {
  inScanMode = true;
  scanTimer = millis();
  apCount = random(18, 45);
  stationCount = random(6, 32);
}

void drawMarauderMenu() {
  // Status bar (top)
  display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(3, 2);
  display.print("CH:"); display.print(random(1,13));
  display.setCursor(45, 2);
  display.print("AP:"); display.print(random(4,22));
  display.setCursor(85, 2);
  display.print("ST:"); display.print(random(2,15));
  
  // Menu title
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 16);
  display.println("MAIN MENU");
  
  // Menu items with selector
  const char* menuItems[] = {
    "WiFi Scan", "Probe Flood", "Deauth Attack",
    "Beacon Spam", "Evil Portal", "SSID Sniffer",
    "Pwnagotchi", "Settings", "About"
  };
  
  for(int i = 0; i < NUM_MENU_ITEMS; i++) {
    int yPos = 28 + (i * 4);
    if(i == menuIndex) {
      display.fillRect(0, yPos-1, 10, 5, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.setCursor(15, yPos);
    display.print(menuItems[i]);
  }
  
  // Controls
  display.setCursor(5, 60);
  display.print("Y:Nav  SW:Select/Exit");
}

void drawScanResults() {
  // Progress bar
  int progress = (millis() - scanTimer) * 100 / 5000;
  display.fillRect(0, 5, progress, 3, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 18);
  display.println("SCAN");
  
  display.setTextSize(1);
  display.setCursor(10, 38);
  display.print("Access Points: "); display.println(apCount);
  
  display.setCursor(10, 48);
  display.print("Stations: "); display.println(stationCount);
  
  int timeLeft = (5000 - (millis() - scanTimer)) / 1000;
  if(timeLeft > 0) {
    display.setCursor(10, 58);
    display.print("Complete in: "); display.print(timeLeft); display.println("s");
  } else {
    inScanMode = false;
  }
}
