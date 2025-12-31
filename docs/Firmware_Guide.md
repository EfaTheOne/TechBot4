# Firmware Installation Guide - TechBot4 ESP32 Marauder

Complete guide to install and configure the firmware on your TechBot4 ESP32 Marauder device.

## Prerequisites

Before starting:
- [ ] Fully assembled TechBot4 device (see Assembly_Guide.md)
- [ ] USB-C cable (data-capable)
- [ ] Computer (Windows, Mac, or Linux)
- [ ] Internet connection for downloads

---

## Step 1: Install Arduino IDE

### Download and Install

**Windows:**
1. Go to: https://www.arduino.cc/en/software
2. Download "Windows Win 10 and newer" installer
3. Run installer (arduino-ide_xxx_Windows_64bit.exe)
4. Follow installation wizard
5. Launch Arduino IDE

**Mac:**
1. Download "macOS 10.14 or newer" DMG
2. Open DMG file
3. Drag Arduino IDE to Applications
4. Launch from Applications folder
5. Allow security permissions if prompted

**Linux:**
1. Download AppImage or use package manager
2. Make executable: `chmod +x arduino-ide_xxx_Linux_64bit.AppImage`
3. Run: `./arduino-ide_xxx_Linux_64bit.AppImage`

**Alternative:** Use Arduino IDE 1.8.x (legacy) if 2.x has issues

---

## Step 2: Install ESP32 Board Support

### Add ESP32 Board Manager URL

1. **Open Arduino IDE**
2. **Go to File → Preferences** (or Arduino IDE → Settings on Mac)
3. **Find "Additional Board Manager URLs"**
4. **Add this URL:**
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
5. **Click OK**

### Install ESP32 Boards

1. **Go to Tools → Board → Boards Manager**
2. **Search for "esp32"**
3. **Find "esp32 by Espressif Systems"**
4. **Click Install** (may take 5-10 minutes)
5. **Wait for completion**
6. **Close Boards Manager**

### Verify Installation

1. **Go to Tools → Board**
2. **Navigate to ESP32 Arduino**
3. **You should see many ESP32 boards listed**
4. **Select "ESP32 Dev Module"**

---

## Step 3: Install Required Libraries

### Using Library Manager

1. **Go to Sketch → Include Library → Manage Libraries** (or Tools → Manage Libraries)
2. **Install these libraries one by one:**

#### WiFi Library (Built-in)
- Already included with ESP32 board support
- No installation needed

#### ESP32 BLE Arduino
- Search: "ESP32 BLE Arduino"
- Author: Neil Kolban
- Click Install

### Verify Libraries Installed

**Check installed libraries:**
```
Sketch → Include Library → [should see WiFi, BLE, etc.]
```

**If library missing**, can install manually:
```
1. Download library ZIP
2. Sketch → Include Library → Add .ZIP Library
3. Select downloaded ZIP file
```

---

## Step 4: Install USB Drivers (Windows Only)

### CP2102 Driver Installation

**Check if driver needed:**
1. Connect device via USB
2. Open Device Manager (Windows key + X → Device Manager)
3. Look under "Ports (COM & LPT)"
4. If you see "CP2102 USB to UART Bridge" - drivers installed ✓
5. If you see "Unknown Device" or exclamation mark - need drivers

**Install CP210x Driver:**
1. Download from: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
2. Select your OS version
3. Download and run installer
4. Restart computer
5. Reconnect device
6. Verify COM port appears in Device Manager

**Mac/Linux:**
- Drivers usually built-in to OS
- If issues on Mac: Install from Silicon Labs website
- Linux: Should work automatically (uses ch341 driver)

---

## Step 5: Download Firmware

### Option A: From Repository

```bash
# Clone repository
git clone https://github.com/EfaTheOne/TechBot4.git

# Navigate to firmware folder
cd TechBot4/firmware/
```

### Option B: Download ZIP

1. Go to: https://github.com/EfaTheOne/TechBot4
2. Click green "Code" button
3. Select "Download ZIP"
4. Extract ZIP file
5. Navigate to firmware folder

### Firmware File Location

```
TechBot4/
└── firmware/
    └── TechBot4_Marauder.ino
```

---

## Step 6: Configure Arduino IDE for Upload

### Select Board

1. **Tools → Board → ESP32 Arduino → ESP32 Dev Module**

### Configure Board Settings

**Important settings:**
```
Upload Speed: 115200
CPU Frequency: 240MHz
Flash Frequency: 80MHz
Flash Mode: QIO
Flash Size: 4MB (32Mb)
Partition Scheme: Default 4MB with spiffs
Core Debug Level: None
PSRAM: Disabled
```

**To access these:**
- Go to Tools menu
- Each setting appears as submenu

### Select COM Port

**Windows:**
1. Tools → Port
2. Select COM port (e.g., COM3, COM4)
3. If multiple ports, unplug device and see which disappears

**Mac:**
1. Tools → Port
2. Select /dev/cu.SLAB_USBtoUART or similar

**Linux:**
1. Tools → Port
2. Select /dev/ttyUSB0 or /dev/ttyACM0

**If no port appears:**
- Check USB cable (must be data cable, not charge-only)
- Verify drivers installed (Windows)
- Check Device Manager / lsusb
- Try different USB port
- Restart computer

---

## Step 7: Open and Compile Firmware

### Open Firmware File

1. **File → Open**
2. **Navigate to firmware folder**
3. **Select TechBot4_Marauder.ino**
4. **Click Open**

### Verify/Compile Code

1. **Click ✓ (Verify) button** or **Sketch → Verify/Compile**
2. **Wait for compilation** (30-60 seconds first time)
3. **Check for errors** in bottom panel

**Expected Output:**
```
Sketch uses XXXXX bytes (XX%) of program storage space.
Global variables use XXXXX bytes (XX%) of dynamic memory.
```

**If compilation errors:**
- Check all libraries installed
- Verify ESP32 board support installed
- Check Arduino IDE version compatible

---

## Step 8: Upload Firmware to Device

### Prepare Device

1. **Connect ESP32 via USB-C cable**
2. **Ensure power switch is ON**
3. **Status LED should light up**

### Upload

1. **Click → (Upload) button** or **Sketch → Upload**
2. **Wait for "Connecting..."** message
3. **Upload progress will show in console**

**Expected Upload Process:**
```
Connecting........_____.....
Chip is ESP32-D0WDQ6 (revision 1)
Writing at 0x00001000... (5 %)
...
Writing at 0x000e1000... (100 %)
Wrote XXXXXX bytes
Leaving...
Hard resetting via RTS pin...
```

### If Upload Fails

**"Failed to connect" error:**

**Manual Boot Mode:**
1. Hold BOOT button (GPIO0)
2. Press and release RESET button
3. Release BOOT button
4. Click Upload in Arduino IDE
5. ESP32 now in bootloader mode

**Still failing:**
- Try lower upload speed (Tools → Upload Speed → 115200)
- Check USB cable quality
- Try different USB port
- Verify COM port selected
- Check CP2102 soldering
- Restart Arduino IDE

---

## Step 9: Test Firmware

### Open Serial Monitor

1. **Tools → Serial Monitor** (or Ctrl+Shift+M)
2. **Set baud rate to 115200** (bottom-right dropdown)
3. **Set line ending to "Both NL & CR"**
4. **Press RESET button on device**

### Expected Output

You should see:
```
TechBot4 Marauder Starting...
ESP32 Pen Testing Device
================================
System Ready!

=== MAIN MENU ===
1. WiFi Scanner
2. WiFi Attacks
3. Bluetooth Scanner
4. Packet Monitor
5. Settings
```

### Test Basic Functions

**Via Serial Monitor:**
- Device should respond to input
- WiFi scan should detect networks
- Bluetooth scan should find devices
- Menu navigation should work

**Via Display (if connected):**
- Display should show menu
- Buttons should navigate
- Selections should change

---

## Step 10: Configure Display (Optional)

If using OLED display, you'll need to add display library:

### Install Display Library

1. **Library Manager**
2. **Search "Adafruit SSD1306"**
3. **Install "Adafruit SSD1306" by Adafruit**
4. **Also install "Adafruit GFX Library"** (dependency)

### Add Display Code

**Modify firmware to add display support:**

```cpp
// Add at top of file
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// In setup()
void setup() {
  // ... existing code ...
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("TechBot4 Marauder");
  display.display();
}
```

**Full display integration available in advanced firmware version.**

---

## Troubleshooting

### Problem: Upload Successful but No Serial Output

**Solutions:**
- Check baud rate (must be 115200)
- Press RESET button
- Try different USB cable
- Check TX/RX connections
- Verify CP2102 working

### Problem: WiFi Scan Shows No Networks

**Solutions:**
- Check ESP32 antenna area clear
- Try in area with known WiFi networks
- Verify ESP32 not damaged
- Check WiFi enabled in code

### Problem: Bluetooth Scan Fails

**Solutions:**
- Ensure BLE library installed
- Check ESP32 Bluetooth not disabled
- Verify enough memory available
- Try disabling WiFi before BLE scan

### Problem: Device Keeps Rebooting

**Solutions:**
- Check power supply (USB should provide enough current)
- Verify 3.3V regulator working
- Check for shorts on power rails
- Reduce power consumption (disable features)

### Problem: Buttons Don't Respond

**Solutions:**
- Check button connections
- Verify GPIO pins correct in code
- Test buttons with multimeter
- Check pull-up resistors installed

---

## Advanced Configuration

### Customize Settings

Edit these values in firmware:

```cpp
// Pin Definitions
#define BUTTON_SELECT 34  // Change if using different pins
#define BUTTON_UP 35
#define BUTTON_DOWN 32
#define BUTTON_BACK 33

// Attack Parameters
uint8_t deauthPacket[26] = { ... };  // Customize packet
```

### Enable Debug Output

```cpp
// In Arduino IDE:
Tools → Core Debug Level → Debug
// Re-upload firmware
// Serial output will be more verbose
```

### Adjust WiFi Power

```cpp
// In setup()
WiFi.setTxPower(WIFI_POWER_19_5dBm);  // Maximum power
// Or
WiFi.setTxPower(WIFI_POWER_11dBm);    // Power saving
```

---

## Firmware Updates

### Check for Updates

1. Visit repository: https://github.com/EfaTheOne/TechBot4
2. Check for new firmware releases
3. Download updated .ino file
4. Upload using same process

### Backup Settings

Before updating:
```
1. Note any custom configurations
2. Save modified firmware to different folder
3. Can revert if needed
```

---

## OTA Updates (Advanced)

⚠️ **SECURITY WARNING**: OTA (Over-The-Air) updates allow wireless firmware installation, but **WITHOUT AUTHENTICATION, ANYONE ON YOUR NETWORK CAN TAKE CONTROL OF YOUR DEVICE**. An attacker on the same network could push malicious firmware, gaining complete control.

**NEVER enable unauthenticated OTA on production or unattended devices.**

For wireless firmware updates with proper security, add OTA library:

```cpp
#include <ArduinoOTA.h>

void setup() {
  // ... existing code ...
  
  ArduinoOTA.setHostname("TechBot4");
  
  // CRITICAL: Set a strong password to prevent unauthorized access
  ArduinoOTA.setPassword("YourStrongPasswordHere");  // REQUIRED for security
  
  // Optional: Add additional security callbacks
  ArduinoOTA.onStart([]() {
    Serial.println("OTA Update Starting...");
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
  });
  
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
  // ... existing code ...
}
```

**Security Best Practices:**
- Always use `ArduinoOTA.setPassword("strong_password")` 
- Use unique, complex passwords (12+ characters)
- Only enable OTA when actively updating
- Disable OTA in production code
- Use VPN or isolated network for OTA updates
- Monitor for unauthorized OTA attempts

Then update wirelessly via Arduino IDE:
```
Tools → Port → TechBot4 at 192.168.x.x
(You will be prompted for the password you set)
```

---

## Additional Resources

### Documentation
- ESP32 Arduino Core: https://docs.espressif.com/projects/arduino-esp32/
- Arduino Language Reference: https://www.arduino.cc/reference/en/

### Community Support
- ESP32 Forum: https://esp32.com/
- Arduino Forum: https://forum.arduino.cc/
- Project Issues: https://github.com/EfaTheOne/TechBot4/issues

### Video Tutorials
- ESP32 Getting Started: YouTube search "ESP32 Arduino tutorial"
- Firmware Upload: YouTube search "ESP32 upload firmware"

---

## Next Steps

After successful firmware installation:
1. ✓ Firmware uploaded and running
2. → Learn device usage (see Usage_Guide.md)
3. → Explore pen testing features
4. → Join community for tips and updates

---

## Legal Notice

⚠️ **Important:**
- Use only on networks you own or have permission to test
- Unauthorized access to networks is illegal
- This device is for educational purposes only
- Comply with local laws and regulations
- You are responsible for your use of this device

---

**Document Version**: 1.0  
**Last Updated**: 2025-01-01  
**Project**: TechBot4 ESP32 Marauder

**Happy hacking (ethically)! 🔒**
