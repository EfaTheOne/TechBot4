# Assembly Guide - TechBot4 ESP32 Marauder

Complete step-by-step guide to assemble your TechBot4 ESP32 Marauder pen testing device.

## Prerequisites

### Required Items:
- [ ] Fabricated PCB (from PCB_Fabrication_Guide.md)
- [ ] All components (from BOM.md)
- [ ] Soldering iron (temperature controlled)
- [ ] Solder (0.8mm recommended)
- [ ] Flux pen or paste
- [ ] Tweezers (for SMD components)
- [ ] Multimeter
- [ ] Magnifying glass or microscope (recommended)
- [ ] Helping hands or PCB holder
- [ ] Isopropyl alcohol (90%+) for cleaning
- [ ] Anti-static mat (recommended)

### Optional but Helpful:
- [ ] Hot air rework station (for SMD)
- [ ] Solder paste and stencil
- [ ] Desoldering wick or pump
- [ ] Good lighting
- [ ] ESD-safe tweezers
- [ ] Solder tip cleaner

---

## Safety First!

⚠️ **Important Safety Guidelines:**
- Work in well-ventilated area
- Don't touch hot soldering iron tip (350-400°C)
- Wash hands after soldering (lead exposure)
- Use safety glasses
- Keep flammable materials away
- Have fire extinguisher nearby
- Ground yourself to prevent ESD damage

---

## Assembly Overview

**Recommended Order:**
1. SMD Components (smallest to largest)
2. Through-hole components
3. Final inspection and cleaning
4. Power-up test
5. Component testing

**Estimated Time:** 2-4 hours (depending on experience)

---

## Step 1: Prepare Your Workspace

1. **Clean PCB:**
   - Wipe with isopropyl alcohol
   - Remove any protective film
   - Inspect for damage

2. **Organize Components:**
   - Sort by type and value
   - Use small containers or tape
   - Label each container
   - Have schematic and layout ready

3. **Set Up Soldering Station:**
   - Temperature: 350°C for lead solder, 400°C for lead-free
   - Clean and tin the tip
   - Have sponge or brass cleaner ready
   - Position helping hands/PCB holder

4. **Ground Yourself:**
   - Use ESD wrist strap (if available)
   - Or touch grounded metal before handling components

---

## Step 2: SMD Components Assembly

### 2A: Resistors (Start Here - Easiest)

**Order:** Smallest components first (0805 resistors)

**Tools:** Tweezers, fine-tip soldering iron, flux

**Technique:**
```
1. Apply flux to one pad
2. Pre-tin one pad with small amount of solder
3. Pick up resistor with tweezers
4. Place on pads (orientation doesn't matter for resistors)
5. Heat pre-tinned pad while holding component
6. Component will settle into place
7. Remove iron, wait 2 seconds
8. Solder other side
9. Inspect both joints
```

**Resistors to Install:**
- R1, R2 (4.7kΩ) - Near OLED connector area
- R3 (330Ω) - Near LED1
- R4, R5 (1kΩ) - Near LED2, LED3
- R6 (1kΩ) - Near buzzer circuit
- R7-R14 (10kΩ) - Near buttons and ESP32
- R15 (1.2kΩ) - Near TP4056
- R16, R17 (27Ω) - Near USB connector

**Pro Tip:** Use multimeter to verify resistor values before soldering

### 2B: Capacitors

**Ceramic Capacitors (0805):**
- C1, C2 (10µF) - Near TP4056
- C5, C6, C7, C9 (100nF) - Near ICs (decoupling)
- C8 (4.7µF) - Near CP2102

**Technique:** Same as resistors (no polarity for ceramic)

**Electrolytic Capacitors (through-hole):**
- ⚠️ **POLARITY MATTERS!** Negative (shorter leg) marked with stripe
- C3, C4 (22µF) - Near voltage regulator
- C10, C11 (10µF) - Near ESP32 (auto-reset circuit)

**Technique for Electrolytic:**
```
1. Insert legs through holes
2. Check polarity marking on PCB
3. Bend legs slightly to hold in place
4. Solder from bottom side
5. Trim excess leads
```

### 2C: LEDs

**LEDs (0805 SMD):**
- LED1 (Red) - Status indicator
- LED2 (Yellow) - Standby indicator
- LED3 (Red) - Charging indicator

⚠️ **POLARITY MATTERS!**
- Cathode (negative): Marked with line or triangle on component
- Check PCB silkscreen for polarity marking

**Technique:**
```
1. Identify cathode mark on LED
2. Match with cathode pad on PCB
3. Apply flux
4. Pre-tin one pad
5. Place LED with tweezers
6. Solder one side first
7. Check alignment and orientation
8. Solder other side
```

**Pro Tip:** Test LEDs before soldering with coin battery (3V)

### 2D: Diode

**D1 (1N4148 - SOD-123):**
- Flyback protection for buzzer

⚠️ **POLARITY MATTERS!**
- Cathode marked with line on component
- Must match cathode mark on PCB

**Technique:** Same as LEDs

### 2E: Transistor

**Q1 (2N3904 - SOT-23):**
- NPN transistor for buzzer driver

⚠️ **ORIENTATION MATTERS!**
- Match pin 1 indicator
- Usually a dot or chamfered corner

**Technique:**
```
1. Apply flux to all 3 pads
2. Pre-tin one pad
3. Align transistor carefully
4. Tack down one pin
5. Check alignment
6. Solder remaining pins
7. Re-flow first pin if needed
```

---

## Step 3: IC Components (Most Critical)

### 3A: TP4056 (U1 - Battery Charger)

**Package:** SOT23-6  
**Location:** Bottom-left area near battery connector

⚠️ **ORIENTATION CRITICAL!**

**Technique:**
```
1. Apply flux to all pads
2. Align chip with pin 1 indicator
3. Tack down one corner pin
4. Check alignment with magnifier
5. Solder opposite corner
6. Solder remaining pins
7. Inspect for bridges with magnifier
8. Use solder wick if bridges present
```

**Testing:**
- No shorts between VCC and GND
- No shorts between adjacent pins

### 3B: AMS1117-3.3 (U2 - Voltage Regulator)

**Package:** SOT-223  
**Location:** Left side, middle area

⚠️ **ORIENTATION CRITICAL!**

**Technique:**
```
1. Apply flux generously
2. Pre-tin the large thermal pad first
3. Place IC and align
4. Solder thermal pad (may need extra heat)
5. Solder three pins
6. Inspect joints
```

**Testing:**
- GND pin connected to GND plane
- No shorts between pins

### 3C: CP2102 (U4 - USB to UART)

**Package:** QFN-28 (Most Difficult!)  
**Location:** Center-bottom area near USB connector

⚠️ **MOST DIFFICULT COMPONENT - Take Your Time!**

**Recommended Method (Hot Air):**
```
1. Apply solder paste to pads (use stencil if available)
2. Carefully place IC with tweezers
3. Align using pin 1 marker
4. Apply hot air at 350°C
5. Watch solder paste melt and IC settle
6. Remove heat, let cool
```

**Alternative Method (Iron):**
```
1. Apply flux to all pads
2. Pre-tin all pads lightly
3. Place IC and align carefully
4. Tack opposite corners
5. Drag solder along each side
6. Use solder wick to remove bridges
7. Re-flux and repeat if needed
```

**Testing:**
- Check for bridges between pins with multimeter
- Verify GND pad connected to ground plane

**Troubleshooting:**
- If bridge occurs: Apply flux, use solder wick to remove excess
- If IC misaligned: Heat all pins, gently push with tweezers

### 3D: ESP32-WROOM-32 (U3 - Main MCU)

**Package:** SMD Module  
**Location:** Upper-center area

⚠️ **HANDLE WITH CARE - ESD SENSITIVE!**

**Technique:**
```
1. Apply flux to all pads on PCB
2. Align ESP32 module carefully
3. Check antenna area extends over board edge
4. Tack down corner pins
5. Check alignment
6. Solder all pins around perimeter
7. Don't overheat - work quickly
8. Solder ground pad on bottom if present
```

**Important:**
- Keep antenna area clear (no components, no copper pour)
- Ensure pin 1 is correctly oriented
- Module should sit flat on PCB

**Testing:**
- Check 3.3V pin not shorted to GND
- Check EN (enable) pin pulled high
- Verify UART pins accessible

---

## Step 4: Through-Hole Components

### 4A: Buttons (SW1-SW6)

**Components:**
- SW1 (RESET) - Near ESP32
- SW2 (SELECT) - User interface
- SW3 (UP) - User interface
- SW4 (DOWN) - User interface
- SW6 (BACK) - User interface

**Technique:**
```
1. Insert button into holes
2. Ensure button sits flush on PCB
3. May need to press firmly
4. Solder all 4 pins from bottom
5. Trim leads if necessary
```

**Testing:**
- Press button, check continuity with multimeter
- Should be open when released, closed when pressed

### 4B: Power Switch (SW5)

**Type:** Slide switch  
**Location:** Bottom-right corner

**Technique:**
```
1. Insert switch into holes
2. Check orientation (ON/OFF markings)
3. Solder all pins from bottom
4. Ensure good mechanical connection
```

**Testing:**
- Slide switch and check continuity
- ON position: connected
- OFF position: open

### 4C: USB-C Connector (J1)

**Type:** USB Type-C receptacle  
**Location:** Bottom-center

**Technique:**
```
1. Insert connector into holes
2. Ensure fully seated
3. May extend over board edge
4. Solder shield/mounting pins first (mechanical)
5. Solder signal pins
6. Inspect all joints
```

**Testing:**
- Check VBUS (+5V) not shorted to GND
- Check D+ and D- not shorted together
- Verify mechanical stability

### 4D: Battery Connector (BAT1)

**Type:** JST 2-pin connector  
**Location:** Bottom-left

⚠️ **POLARITY CRITICAL!**

**Technique:**
```
1. Insert connector
2. DOUBLE CHECK polarity markings
3. Red wire = positive, Black = negative
4. Solder both pins
```

### 4E: Buzzer (BZ1)

**Type:** Passive buzzer, 12mm  
**Location:** Bottom-center area

⚠️ **POLARITY MATTERS!**

**Technique:**
```
1. Check polarity marking (+ on buzzer)
2. Insert into holes matching polarity on PCB
3. Solder from bottom
4. Buzzer should sit flush
```

### 4F: OLED Display

**Type:** 0.96" I2C OLED (128x64)  
**Location:** Top of board

**Recommended:** Use female socket headers for easy replacement

**Technique:**
```
1. Solder 4-pin female header to PCB
2. Locations: GND, VDD, SCL, SDA
3. Verify pin order matches display
4. Insert display into header (don't solder permanently)
5. This allows display replacement if needed
```

**Alternative:** Solder display directly (permanent)

---

## Step 5: Inspection and Cleaning

### Visual Inspection Checklist:
- [ ] All components installed
- [ ] No missing components
- [ ] All solder joints shiny and smooth (not dull/cracked)
- [ ] No solder bridges between pins
- [ ] No cold solder joints (insufficient solder)
- [ ] Correct component orientation (ICs, LEDs, diode)
- [ ] No damaged components
- [ ] Through-hole components flush with board

### Cleaning:
```
1. Let PCB cool completely
2. Apply isopropyl alcohol (90%+)
3. Scrub gently with soft brush
4. Remove all flux residue
5. Let dry completely (10+ minutes)
6. Inspect again under good lighting
```

---

## Step 6: Electrical Testing (No Power Yet!)

### Continuity Tests:

**Power Rail Shorts (CRITICAL):**
```
Multimeter in continuity/resistance mode:

1. 3.3V to GND: Should be >1kΩ (open, no beep)
2. 5V (VBUS) to GND: Should be open
3. Battery+ to GND: Should be open
4. Any power rail to any other: Should be open
```

**If Short Found:**
- Inspect all solder joints under magnifier
- Check for solder bridges
- Verify component orientation
- Check for damaged components

**Critical Connections:**
```
Should have continuity (beep):

1. GND pad to GND pad (anywhere)
2. 3.3V test point to ESP32 VDD
3. ESP32 pin to corresponding trace
4. USB connector GND to PCB GND
```

### Component Orientation Check:

- [ ] All ICs pin 1 correct
- [ ] All LEDs cathode correct
- [ ] Diode cathode correct
- [ ] Transistor orientation correct
- [ ] Electrolytic capacitor polarity correct
- [ ] Battery connector polarity correct

---

## Step 7: First Power-Up Test

⚠️ **DO NOT CONNECT BATTERY YET!**

### USB Power Test:

1. **Set multimeter to DC voltage**
2. **Connect USB cable to computer**
   - USB should provide 5V
3. **Measure voltages:**
   - USB VBUS: Should be ~5V
   - 3.3V rail: Should be ~3.3V (±0.1V)
   - ESP32 VDD: Should be ~3.3V

**Expected Results:**
- ✓ USB detected by computer (new device sound)
- ✓ CP2102 enumerated (check Device Manager/lsusb)
- ✓ LED2 or LED3 may light (charger circuit)
- ✓ Status LED may blink during enumeration

**If No 3.3V:**
- Check AMS1117 installation
- Verify input voltage (VIN) present
- Check for shorts on 3.3V rail
- Verify capacitors installed

**If USB Not Recognized:**
- Check CP2102 soldering
- Verify USB data lines (D+, D-)
- Check USB connector soldering
- Try different USB cable/port

### Current Draw Test:

**Normal current draw:**
- Idle (no ESP32 activity): 50-100mA
- ESP32 active: 100-200mA
- WiFi scanning: 200-300mA

**If current >500mA:**
- Disconnect immediately!
- Component shorted or incorrectly installed
- Inspect thoroughly before re-applying power

---

## Step 8: Component-by-Component Testing

### Test LEDs:

Manually control via ESP32 (after programming):
```
LED1 (Status): Should light when GPIO2 high
LED2 (Standby): Controlled by TP4056
LED3 (Charging): Controlled by TP4056
```

### Test Buttons:

Use multimeter to verify:
```
Not pressed: Open circuit (infinite resistance)
Pressed: Closed circuit (0Ω, continuity beep)
```

Or flash test firmware to ESP32.

### Test Display:

After firmware uploaded:
```
Should show boot message
Test I2C communication (address 0x3C)
```

If display blank:
- Check I2C connections (SDA, SCL)
- Verify pull-up resistors installed
- Check display power (3.3V)
- Try different display (if using socket)

### Test Buzzer:

Flash test firmware:
```
Should beep during startup
Test different frequencies
```

### Test Battery Charging:

1. **Connect battery to BAT1**
   - RED wire to + (positive)
   - BLACK wire to - (negative/GND)
2. **Connect USB power**
3. **LED3 should light RED (charging)**
4. **When full, LED2 lights YELLOW (standby)**

⚠️ **Monitor first charge:**
- Battery should not get hot
- Normal: Slightly warm is OK
- Abort if very hot or smells strange

---

## Step 9: Program ESP32

See **Firmware_Guide.md** for detailed instructions.

**Quick Start:**
```
1. Install Arduino IDE
2. Add ESP32 board support
3. Install required libraries
4. Open TechBot4_Marauder.ino
5. Select board: "ESP32 Dev Module"
6. Select COM port
7. Upload firmware
8. Open Serial Monitor (115200 baud)
9. Should see startup messages
```

---

## Step 10: Final Assembly

1. **Install battery** (if not already)
2. **Close case** (if you have enclosure)
3. **Test all functions:**
   - [ ] WiFi scanning
   - [ ] Bluetooth scanning
   - [ ] Buttons work
   - [ ] Display shows menus
   - [ ] Buzzer sounds
   - [ ] LEDs indicate status
   - [ ] Battery charges
   - [ ] Device runs on battery power

---

## Troubleshooting Guide

### Problem: ESP32 Won't Program

**Possible Causes:**
- CP2102 not soldered correctly
- Wrong COM port selected
- Driver not installed
- Auto-reset circuit not working

**Solutions:**
1. Install CP210x drivers from Silicon Labs
2. Try manual reset: Hold BOOT button, press RESET, release RESET, release BOOT
3. Check CP2102 connections
4. Verify USB cable has data lines (not charge-only)

### Problem: Display Blank

**Possible Causes:**
- Display not powered
- I2C not connected
- Wrong I2C address
- Display defective

**Solutions:**
1. Check 3.3V at display pins
2. Verify SDA and SCL connections
3. Run I2C scanner sketch
4. Try different display
5. Check pull-up resistors (R1, R2)

### Problem: WiFi Not Working

**Possible Causes:**
- ESP32 antenna blocked
- Keepout zone violated
- Component near antenna
- ESP32 damaged

**Solutions:**
1. Check antenna area clear
2. Verify no copper pour under antenna
3. Try external antenna (if connector present)
4. Replace ESP32 module

### Problem: Battery Won't Charge

**Possible Causes:**
- TP4056 not soldered correctly
- Battery connector polarity reversed
- Battery protection circuit engaged
- TP4056 current limit resistor wrong

**Solutions:**
1. Verify TP4056 installation
2. Check battery polarity (RED=+, BLACK=-)
3. Measure battery voltage (should be 3.0-4.2V)
4. Check R15 value (1.2kΩ for 1A charge)

### Problem: Device Won't Power On

**Possible Causes:**
- Power switch off
- Battery dead
- Voltage regulator failed
- Power rails shorted

**Solutions:**
1. Check power switch position
2. Charge battery via USB
3. Test 3.3V rail with multimeter
4. Check for shorts on power rails

### Problem: Buttons Not Working

**Possible Causes:**
- Button not soldered correctly
- Pull-up resistors missing
- GPIO pin damaged
- Firmware issue

**Solutions:**
1. Test button with multimeter (continuity test)
2. Verify pull-up resistors installed
3. Re-solder button pins
4. Test with different GPIO in firmware

---

## Tips for Success

1. **Take Your Time**
   - Don't rush SMD components
   - Double-check before soldering

2. **Use Plenty of Flux**
   - Makes soldering much easier
   - Helps prevent bridges

3. **Good Lighting**
   - Use magnifying glass for SMD
   - Inspect under bright light

4. **Test as You Go**
   - Don't wait until end to test
   - Easier to fix one component than debug later

5. **Practice First**
   - If new to SMD, practice on scrap PCB
   - Watch YouTube tutorials

6. **Keep Workspace Organized**
   - Label components
   - Don't mix up values

7. **Use Proper Temperature**
   - Too hot: Damage components
   - Too cold: Cold solder joints

8. **Clean Thoroughly**
   - Flux residue can cause issues
   - Use IPA and brush

---

## Resources

### Video Tutorials:
- SMD Soldering Tutorial: https://www.youtube.com/watch?v=f9fbqks3BS8
- ESP32 Assembly: https://www.youtube.com/watch?v=JNvbUO3bWWs

### Reference Documents:
- ESP32 Datasheet
- TP4056 Datasheet
- Component datasheets in /docs/datasheets/

### Tools Recommendations:
- Soldering Iron: Hakko FX-888D or TS100
- Multimeter: Any basic digital multimeter
- Tweezers: ESD-safe precision tweezers
- Magnifier: USB microscope or jeweler's loupe

---

## Next Steps

After successful assembly:
1. ✓ Device assembled and tested
2. → Flash firmware (see Firmware_Guide.md)
3. → Learn to use device (see Usage_Guide.md)
4. → Join community for support

---

**Document Version**: 1.0  
**Last Updated**: 2025-01-01  
**Project**: TechBot4 ESP32 Marauder

**Congratulations on completing the assembly! 🎉**
