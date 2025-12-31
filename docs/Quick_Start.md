# Quick Start Guide - TechBot4 ESP32 Marauder

**Get up and running in 30 minutes!**

## For Complete Beginners (Breadboard Build)

If you're new to this, start with a breadboard build before attempting the PCB version.

### What You Need (Minimum)

1. **ESP32 Development Board** (~$5-10)
   - Any ESP32 board works (DevKitC, NodeMCU-32S, etc.)
   - Search Amazon/AliExpress: "ESP32 development board"

2. **0.96" OLED Display** (~$3-5)
   - I2C interface (4 pins: VCC, GND, SCL, SDA)
   - 128x64 resolution
   - Search: "0.96 OLED I2C SSD1306"

3. **4x Push Buttons** (~$1)
   - Any momentary push buttons
   - Search: "tactile push button"

4. **Breadboard and Jumper Wires** (~$5)
   - Standard 830 point breadboard
   - Male-to-male jumper wires

5. **USB Cable** (often included with ESP32)
   - Micro-USB or USB-C depending on your ESP32 board

**Total Cost: ~$15-25**

---

## Step 1: Wiring (15 minutes)

### ESP32 to OLED Display

```
ESP32          OLED Display
Pin 21 (SDA) → SDA
Pin 22 (SCL) → SCL
3.3V         → VCC
GND          → GND
```

### ESP32 to Buttons

```
ESP32 Pin → Button → GND
GPIO 34   → SELECT → GND (with 10kΩ to 3.3V)
GPIO 35   → UP     → GND (with 10kΩ to 3.3V)
GPIO 32   → DOWN   → GND (with 10kΩ to 3.3V)
GPIO 33   → BACK   → GND (with 10kΩ to 3.3V)
```

**Simple Method (without resistors):**
The ESP32 has internal pull-ups, so you can enable them in code:
```cpp
pinMode(34, INPUT_PULLUP);
```

### Visual Diagram

```
                    ESP32 DevKit
                  ┌────────────┐
        USB ←─────┤  USB       │
                  │            │
    OLED SDA ←────┤ 21         │
    OLED SCL ←────┤ 22         │
                  │            │
 SELECT BTN ←─────┤ 34         │
     UP BTN ←─────┤ 35         │
   DOWN BTN ←─────┤ 32         │
   BACK BTN ←─────┤ 33         │
                  │            │
    OLED VCC ←────┤ 3.3V       │
    OLED GND ←────┤ GND        │
                  └────────────┘
```

---

## Step 2: Software Setup (10 minutes)

### Install Arduino IDE

1. Download from: https://www.arduino.cc/en/software
2. Install for your operating system
3. Open Arduino IDE

### Add ESP32 Support

1. File → Preferences
2. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Tools → Board → Boards Manager
4. Search "esp32"
5. Install "esp32 by Espressif Systems"

### Install Libraries

1. Tools → Manage Libraries
2. Search and install:
   - "Adafruit SSD1306" (for OLED display)
   - "Adafruit GFX Library" (dependency)

---

## Step 3: Upload Firmware (5 minutes)

### Get the Code

1. Download from: https://github.com/EfaTheOne/TechBot4
2. Open `firmware/TechBot4_Marauder.ino`

### Configure Arduino IDE

1. **Tools → Board → ESP32 Arduino → ESP32 Dev Module**
2. **Tools → Upload Speed → 115200**
3. **Tools → Port → [Select your ESP32 COM port]**

### Upload

1. Click the **Upload** button (→)
2. Wait for "Connecting..."
3. If it fails, press and hold BOOT button on ESP32, then click Upload
4. Wait for "Done uploading"

---

## Step 4: Test It! (2 minutes)

### Open Serial Monitor

1. **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. Press RESET button on ESP32

### You Should See:

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

### Test WiFi Scan

1. Send "1" in Serial Monitor (or press SELECT button if wired)
2. Wait a few seconds
3. You should see a list of WiFi networks!

**Congratulations! It's working! 🎉**

---

## Troubleshooting

### "No Port Available"

**Windows:**
- Install CP210x drivers from Silicon Labs
- Check Device Manager for COM port

**Mac:**
- Should work automatically
- If not, install drivers from Silicon Labs website

**Linux:**
- Add yourself to dialout group: `sudo usermod -a -G dialout $USER`
- Log out and back in

### "Failed to Connect"

1. Hold down BOOT button on ESP32
2. Click Upload in Arduino IDE
3. Keep holding until "Connecting..." appears
4. Release BOOT button

### "Compilation Error"

- Make sure ESP32 board support is installed
- Install all required libraries
- Check you opened the .ino file correctly

### Display Shows Nothing

- Check wiring (especially SDA and SCL)
- Verify display is powered (3.3V)
- Try example sketch from Adafruit SSD1306 library first

### WiFi Scan Finds Nothing

- Make sure you're near WiFi networks
- Try in a different location
- Check ESP32 antenna not covered

---

## Next Steps

### You're Ready to:

✓ **Scan WiFi networks** - Find networks around you  
✓ **Scan Bluetooth devices** - Discover BLE devices  
✓ **Learn about wireless security** - Understand protocols  

### Want to Go Further?

1. **Add more features** - Customize the firmware
2. **Build the PCB version** - Make it portable
3. **Create a case** - 3D print an enclosure
4. **Learn ethical hacking** - Take security courses

---

## Important Reminders

⚠️ **Legal Notice:**
- Only test YOUR OWN networks
- Get written permission for any other networks
- Unauthorized access is illegal
- Use for learning, not harm

🎓 **Learning Resources:**
- Read the full documentation in `/docs`
- Join ESP32 community forums
- Study WiFi security fundamentals
- Practice on your own lab network

---

## Upgrading to PCB Version

Once comfortable with the breadboard version:

1. **Review** - `/docs/PCB_Fabrication_Guide.md`
2. **Order PCB** - From JLCPCB (~$2 for 5 boards)
3. **Get components** - See `/docs/BOM.md`
4. **Assemble** - Follow `/docs/Assembly_Guide.md`
5. **Enjoy** - Phone-sized professional device!

---

## Need Help?

- **Full Documentation**: See `/docs` folder
- **Issues**: https://github.com/EfaTheOne/TechBot4/issues
- **Community**: ESP32 forums

---

## Success Checklist

- [ ] Arduino IDE installed
- [ ] ESP32 board support added
- [ ] Libraries installed
- [ ] Hardware connected
- [ ] Firmware uploaded successfully
- [ ] Serial monitor shows menu
- [ ] WiFi scan works
- [ ] Ready to learn!

---

**Now you're a wireless hacker! (The ethical kind 😊)**

**Happy building and learning!**
