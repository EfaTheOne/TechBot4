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
#define JOY_SW 34 // SW (Button) - Note: GPIO34 is input-only, no internal pullup

// Joystick calibration values
#define JOY_CENTER 2048
#define JOY_DEADZONE 300
#define JOY_THRESHOLD_UP    (JOY_CENTER - JOY_DEADZONE)
#define JOY_THRESHOLD_DOWN  (JOY_CENTER + JOY_DEADZONE)
#define JOY_THRESHOLD_LEFT  (JOY_CENTER - JOY_DEADZONE)
#define JOY_THRESHOLD_RIGHT (JOY_CENTER + JOY_DEADZONE)

// Button threshold for analog read (if using external pullup)
#define BTN_PRESSED_THRESHOLD 500

// Initialize OLED with Hardware SPI (SAME as test)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Marauder variables
int menuIndex = 0;
int menuScrollOffset = 0;
const int VISIBLE_MENU_ITEMS = 4;
bool inScanMode = false;
bool inJoystickTest = false;
unsigned long scanTimer = 0;
int apCount = 0;
int stationCount = 0;
const int NUM_MENU_ITEMS = 10;

// Animation variables
unsigned long lastAnimTime = 0;
int animFrame = 0;
int signalStrength = 0;

// Joystick state for visual feedback
int joyXMapped = 0;
int joyYMapped = 0;
bool btnPressed = false;

void setup() {
  Serial.begin(115200);
  
  // Setup Joystick button - GPIO34 is input-only, no internal pullup available
  // IMPORTANT: You need an EXTERNAL 10K pullup resistor from GPIO34 to 3.3V
  pinMode(JOY_SW, INPUT);

  // Initialize OLED (EXACT same check as test)
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed. Check wiring!"));
    for(;;);
  }

  // Marauder boot screen with animation
  bootScreen();
  Serial.println("ESP32 Marauder Ready!");
}

void loop() {
  // Read Joystick Values
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  
  // Read button - check analog value since GPIO34 has no internal pullup
  // With external pullup: HIGH when not pressed, LOW when pressed
  // Alternative: read analog and check threshold
  int swAnalog = analogRead(JOY_SW);
  bool swPressed = (swAnalog < BTN_PRESSED_THRESHOLD);
  
  // Map joystick values for visual feedback (-10 to 10 range)
  joyXMapped = map(xVal, 0, 4095, -10, 10);
  joyYMapped = map(yVal, 0, 4095, -10, 10);
  btnPressed = swPressed;

  // Handle menu navigation
  handleJoystick(xVal, yVal, swPressed);
  
  // Update animations
  if(millis() - lastAnimTime > 150) {
    animFrame = (animFrame + 1) % 4;
    signalStrength = random(1, 4);
    lastAnimTime = millis();
  }
  
  // Clear display for new data
  display.clearDisplay();
  
  if(inJoystickTest) {
    drawJoystickTest();
  } else if(inScanMode) {
    drawScanResults();
  } else {
    drawMarauderMenu();
  }
  
  display.display();
  delay(50);  // Faster refresh for smoother animations
}

void bootScreen() {
  // Frame 1: Logo fade in
  for(int i = 0; i < 3; i++) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(22, 8);
    display.println("ESP32");
    display.setTextSize(1);
    display.setCursor(25, 28);
    display.println("MARAUDER");
    
    // Draw animated border
    for(int j = 0; j < i * 40; j += 2) {
      display.drawPixel(j, 0, SSD1306_WHITE);
      display.drawPixel(128 - j, 63, SSD1306_WHITE);
    }
    display.display();
    delay(300);
  }
  
  // Frame 2: Full display
  display.clearDisplay();
  
  // Draw cool border
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.drawRect(2, 2, 124, 60, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(22, 8);
  display.println("ESP32");
  
  display.setTextSize(1);
  display.setCursor(25, 28);
  display.println("MARAUDER");
  
  // Version with box
  display.fillRoundRect(45, 38, 38, 12, 3, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(52, 40);
  display.println("v2.1");
  
  // Status line
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 54);
  display.println("SPI READY");
  
  display.display();
  delay(2000);
  
  // Loading animation
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 25);
  display.println("LOADING...");
  
  for(int i = 0; i < 100; i += 5) {
    display.fillRect(14, 38, i, 8, SSD1306_WHITE);
    display.drawRect(14, 38, 100, 8, SSD1306_WHITE);
    display.display();
    delay(50);
  }
  delay(500);
}

void handleJoystick(int x, int y, bool sw) {
  static unsigned long lastMoveTime = 0;
  static bool lastSw = false;
  static unsigned long btnDebounce = 0;
  
  // Debounce timing
  unsigned long debounceDelay = 180;
  
  // Menu navigation (Y-axis up/down) with proper deadzone
  if(millis() - lastMoveTime > debounceDelay) {
    if(y > JOY_THRESHOLD_DOWN) {  // Down - joystick pushed down = higher analog value
      menuIndex = (menuIndex + 1) % NUM_MENU_ITEMS;
      // Update scroll offset
      if(menuIndex >= menuScrollOffset + VISIBLE_MENU_ITEMS) {
        menuScrollOffset = menuIndex - VISIBLE_MENU_ITEMS + 1;
      }
      if(menuIndex < menuScrollOffset) {
        menuScrollOffset = menuIndex;
      }
      lastMoveTime = millis();
    } else if(y < JOY_THRESHOLD_UP) {  // Up - joystick pushed up = lower analog value
      menuIndex = (menuIndex - 1 + NUM_MENU_ITEMS) % NUM_MENU_ITEMS;
      // Update scroll offset
      if(menuIndex < menuScrollOffset) {
        menuScrollOffset = menuIndex;
      }
      if(menuIndex >= menuScrollOffset + VISIBLE_MENU_ITEMS) {
        menuScrollOffset = menuIndex - VISIBLE_MENU_ITEMS + 1;
      }
      lastMoveTime = millis();
    }
  }
  
  // Button press with proper debounce
  if(millis() - btnDebounce > 250) {
    if(sw && !lastSw) {  // Button just pressed
      if(inJoystickTest) {
        inJoystickTest = false;  // Exit joystick test
      } else if(inScanMode) {
        inScanMode = false;  // Exit scan
      } else {
        // Handle menu selection
        if(menuIndex == NUM_MENU_ITEMS - 1) {  // Joystick Test option
          inJoystickTest = true;
        } else {
          startScan();  // Enter scan mode for other options
        }
      }
      btnDebounce = millis();
    }
  }
  lastSw = sw;
}

void startScan() {
  inScanMode = true;
  scanTimer = millis();
  apCount = random(18, 45);
  stationCount = random(6, 32);
}

void drawSignalIcon(int x, int y, int strength) {
  // Draw animated signal bars
  for(int i = 0; i < 3; i++) {
    if(i < strength) {
      display.fillRect(x + i*3, y + (2-i)*2, 2, 4 + i*2, SSD1306_WHITE);
    } else {
      display.drawRect(x + i*3, y + (2-i)*2, 2, 4 + i*2, SSD1306_WHITE);
    }
  }
}

void drawMarauderMenu() {
  // Status bar (top) with rounded corners
  display.fillRoundRect(0, 0, 128, 14, 2, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  
  // Channel indicator
  display.setCursor(3, 3);
  display.print("CH:");
  display.print((animFrame + 1) % 13 + 1);
  
  // AP count with icon
  display.setCursor(40, 3);
  display.print("AP:");
  display.print(apCount > 0 ? apCount : random(4, 22));
  
  // Station count
  display.setCursor(80, 3);
  display.print("ST:");
  display.print(stationCount > 0 ? stationCount : random(2, 15));
  
  // Draw signal icon in status bar
  display.setTextColor(SSD1306_WHITE);
  drawSignalIcon(115, 2, signalStrength);
  
  // Menu title with underline
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(35, 17);
  display.println("MAIN MENU");
  display.drawLine(35, 26, 93, 26, SSD1306_WHITE);
  
  // Menu items (scrollable view)
  const char* menuItems[] = {
    "> WiFi Scan",
    "> Probe Flood",
    "> Deauth Attack",
    "> Beacon Spam",
    "> Evil Portal",
    "> SSID Sniffer",
    "> Pwnagotchi",
    "> Settings",
    "> About",
    "> Joystick Test"
  };
  
  // Draw visible menu items
  for(int i = 0; i < VISIBLE_MENU_ITEMS && (menuScrollOffset + i) < NUM_MENU_ITEMS; i++) {
    int itemIndex = menuScrollOffset + i;
    int yPos = 29 + (i * 9);
    
    if(itemIndex == menuIndex) {
      // Selected item - inverted with rounded rect
      display.fillRoundRect(2, yPos - 1, 124, 10, 2, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.setCursor(6, yPos);
    display.print(menuItems[itemIndex]);
  }
  
  // Scroll indicators
  display.setTextColor(SSD1306_WHITE);
  if(menuScrollOffset > 0) {
    display.setCursor(120, 28);
    display.print("^");
  }
  if(menuScrollOffset + VISIBLE_MENU_ITEMS < NUM_MENU_ITEMS) {
    display.setCursor(120, 55);
    display.print("v");
  }
}

void drawScanResults() {
  // Header
  display.fillRoundRect(0, 0, 128, 12, 2, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(35, 2);
  display.print("SCANNING");
  
  // Animated dots
  for(int i = 0; i < (animFrame % 3) + 1; i++) {
    display.print(".");
  }
  
  // Progress bar with frame
  int elapsed = millis() - scanTimer;
  int progress = min((elapsed * 100) / 5000, 100);
  display.setTextColor(SSD1306_WHITE);
  display.drawRoundRect(10, 16, 108, 10, 2, SSD1306_WHITE);
  display.fillRoundRect(12, 18, (progress * 104) / 100, 6, 1, SSD1306_WHITE);
  
  // Percentage
  display.setCursor(54, 28);
  display.print(progress);
  display.print("%");
  
  // Results in boxes
  display.drawRoundRect(5, 36, 58, 20, 3, SSD1306_WHITE);
  display.setCursor(10, 39);
  display.print("APs");
  display.setTextSize(1);
  display.setCursor(18, 48);
  display.print(apCount);
  
  display.drawRoundRect(65, 36, 58, 20, 3, SSD1306_WHITE);
  display.setCursor(70, 39);
  display.print("Stations");
  display.setCursor(82, 48);
  display.print(stationCount);
  
  // Time remaining or complete
  int timeLeft = (5000 - elapsed) / 1000;
  display.setCursor(5, 58);
  if(timeLeft > 0) {
    display.print("Time left: ");
    display.print(timeLeft);
    display.print("s  [CLICK=EXIT]");
  } else {
    display.print("COMPLETE! [CLICK=MENU]");
    if(elapsed > 6000) {  // Auto-exit after 1 second past completion
      inScanMode = false;
    }
  }
}

void drawJoystickTest() {
  // Header
  display.fillRoundRect(0, 0, 128, 12, 2, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(25, 2);
  display.print("JOYSTICK TEST");
  
  display.setTextColor(SSD1306_WHITE);
  
  // Raw values
  int xRaw = analogRead(JOY_X);
  int yRaw = analogRead(JOY_Y);
  int swRaw = analogRead(JOY_SW);
  
  display.setCursor(5, 15);
  display.print("X:");
  display.print(xRaw);
  display.print(" Y:");
  display.print(yRaw);
  
  display.setCursor(5, 25);
  display.print("SW:");
  display.print(swRaw);
  display.print(" ");
  
  // Button state indicator
  if(btnPressed) {
    display.fillRoundRect(55, 23, 45, 10, 2, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(58, 25);
    display.print("PRESSED");
    display.setTextColor(SSD1306_WHITE);
  } else {
    display.drawRoundRect(55, 23, 45, 10, 2, SSD1306_WHITE);
    display.setCursor(61, 25);
    display.print("OPEN");
  }
  
  // Visual joystick representation
  int centerX = 64;
  int centerY = 48;
  int radius = 14;
  
  // Outer circle
  display.drawCircle(centerX, centerY, radius, SSD1306_WHITE);
  display.drawCircle(centerX, centerY, radius - 1, SSD1306_WHITE);
  
  // Crosshairs
  display.drawLine(centerX - radius - 3, centerY, centerX - radius + 2, centerY, SSD1306_WHITE);
  display.drawLine(centerX + radius - 2, centerY, centerX + radius + 3, centerY, SSD1306_WHITE);
  display.drawLine(centerX, centerY - radius - 3, centerX, centerY - radius + 2, SSD1306_WHITE);
  display.drawLine(centerX, centerY + radius - 2, centerX, centerY + radius + 3, SSD1306_WHITE);
  
  // Joystick position indicator
  int posX = centerX + (joyXMapped * radius / 12);
  int posY = centerY + (joyYMapped * radius / 12);
  display.fillCircle(posX, posY, 3, SSD1306_WHITE);
  
  // Direction indicators
  display.setCursor(5, 48);
  if(joyXMapped < -3) display.print("<");
  else display.print(" ");
  
  display.setCursor(120, 48);
  if(joyXMapped > 3) display.print(">");
  else display.print(" ");
  
  display.setCursor(64, 35);
  if(joyYMapped < -3) display.print("^");
  
  display.setCursor(64, 60);
  if(joyYMapped > 3) display.print("v");
  
  // Instructions
  display.setCursor(5, 58);
  display.print("[CLICK=EXIT]");
}
