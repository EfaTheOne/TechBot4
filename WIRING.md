# TechBot4 Wiring Guide

This guide provides detailed wiring instructions for connecting all components of the TechBot4 ESP32-based pen testing tool. This document is designed for beginners and includes clear pin-to-pin connections for use with EasyEDA.

---

## Table of Contents
1. [Component Overview](#component-overview)
2. [ESP32-WROOM-32-N8 Pinout Reference](#esp32-wroom-32-n8-pinout-reference)
3. [Power System Wiring](#power-system-wiring)
4. [Display Wiring](#display-wiring)
5. [Button Wiring](#button-wiring)
6. [Complete Pin Assignment Table](#complete-pin-assignment-table)
7. [Wiring Checklist](#wiring-checklist)

---

## Component Overview

### Main Components:
- **ESP32-WROOM-32-N8**: Main microcontroller (C529582)
- **Adafruit 2.0" IPS Display**: 320x240 pixel display with EYESPI connector (Product #4311)
- **IP5306**: Battery charger & 5V boost converter (C96641)
- **AMS1117-3.3**: 3.3V voltage regulator (C6186)
- **USB Type-C Port**: Charging input (C165948)
- **JST-PH 2-Pin Connector**: Battery connector (C396123)
- **6x Tactile Switches**: Navigation and select buttons (C34260)

### Supporting Components:
- **1.0µH Inductor** (C116556): 1x - For IP5306
- **22µF Capacitors** (C96446): 2x - IP5306 filtering
- **10µF Capacitors** (C19702): 3x - Regulator and ESP32 power
- **0.1µF Capacitor** (C14663): 1x - ESP32 decoupling
- **5.1kΩ Resistors** (C23178): 2x - USB-C CC pins
- **1kΩ Resistor** (C21190): 1x - LED/EN pull-up
- **10kΩ Resistors** (C23177): 6x - Button pull-downs

---

## ESP32-WROOM-32-N8 Pinout Reference

The ESP32-WROOM-32-N8 is a 38-pin module. Here are the key pins you'll use:

### Power Pins:
- **Pin 1 (GND)**: Ground - Connect to system ground
- **Pin 2 (3V3)**: 3.3V power input - Connect to AMS1117 output
- **Pin 38 (GND)**: Ground - Connect to system ground

### SPI Pins (for Display):
- **Pin 25 (GPIO 23)**: MOSI (Master Out Slave In) - Display data
- **Pin 31 (GPIO 19)**: MISO (Master In Slave Out) - Display data (optional for display)
- **Pin 30 (GPIO 18)**: SCK (Clock) - Display clock
- **Pin 29 (GPIO 5)**: CS (Chip Select) - Display chip select

### Display Control Pins:
- **Pin 26 (GPIO 22)**: DC (Data/Command) - Display data/command control
- **Pin 23 (GPIO 21)**: RST (Reset) - Display reset (can also use EN)
- **Pin 16 (GPIO 4)**: Backlight control (optional PWM)

### Button Input Pins:
- **Pin 13 (GPIO 12)**: Button UP
- **Pin 12 (GPIO 13)**: Button DOWN
- **Pin 11 (GPIO 14)**: Button LEFT
- **Pin 10 (GPIO 15)**: Button RIGHT
- **Pin 9 (GPIO 2)**: Button SELECT/ENTER
- **Pin 3 (EN)**: RESET button (active LOW with external pull-up)

### Other Important Pins:
- **Pin 8 (GPIO 0)**: Boot mode (must be HIGH for normal operation)
- **Pin 7 (GPIO 34)**: Battery voltage monitoring (ADC input, optional)

---

## Power System Wiring

### Section 1: USB-C Charging Input

#### USB Type-C Port (C165948) Connections:
```
USB-C Pin Layout (16-Pin SMD):
- A1, A12, B1, B12: GND → System Ground
- A4, A9, B4, B9: VBUS → IP5306 VIN (5V input)
- A5: CC1 → 5.1kΩ resistor → GND
- B5: CC2 → 5.1kΩ resistor → GND
- All other pins: Not connected
```

**Detailed Connections:**
1. **VBUS pins (A4, A9, B4, B9)** → Connect all together → **IP5306 Pin VIN**
2. **GND pins (A1, A12, B1, B12)** → Connect all together → **System Ground**
3. **CC1 pin (A5)** → **5.1kΩ resistor (R1)** → **Ground** (for USB-C compliance)
4. **CC2 pin (B5)** → **5.1kΩ resistor (R2)** → **Ground** (for USB-C compliance)

### Section 2: Battery Connection

#### JST-PH 2-Pin Connector (C396123):
```
Pin 1 (Red wire): BAT+ → IP5306 BAT+
Pin 2 (Black wire): BAT- → System Ground
```

**Battery Specs:** 3.7V LiPo, 1500mAh

### Section 3: IP5306 Power Management IC (ESOP-8)

#### IP5306 Pinout (C96641):
```
Pin 1: VIN    - USB 5V input
Pin 2: GND    - Ground
Pin 3: BAT+   - Battery positive
Pin 4: BAT-   - Battery negative (typically GND)
Pin 5: VOUT   - 5V output
Pin 6: FB     - Feedback (internal, may have external components)
Pin 7: SW     - Switching pin (connect inductor here)
Pin 8: EN     - Enable (pull HIGH or connect to VIN via resistor)
```

**Connections:**
1. **Pin 1 (VIN)** ← **USB-C VBUS** (through 22µF capacitor C1 to GND for filtering)
2. **Pin 2 (GND)** → **System Ground**
3. **Pin 3 (BAT+)** ← **JST Connector Pin 1** (Battery positive)
4. **Pin 4 (BAT-)** → **System Ground**
5. **Pin 5 (VOUT)** → **5V Rail** (through 22µF capacitor C2 to GND for filtering) → **AMS1117 VIN**
6. **Pin 7 (SW)** ← **1.0µH Inductor (L1)** → **VOUT (Pin 5)**
7. **Pin 8 (EN)** → **VIN** (or use 1kΩ pull-up to VIN for enable)

**Capacitor Placement:**
- **C1 (22µF)**: Between IP5306 VIN (Pin 1) and GND
- **C2 (22µF)**: Between IP5306 VOUT (Pin 5) and GND

### Section 4: AMS1117-3.3 Voltage Regulator (SOT-223)

#### AMS1117-3.3 Pinout (C6186):
```
Pin 1 (GND/ADJ): Ground
Pin 2 (VOUT):    3.3V Output
Pin 3 (VIN):     5V Input
Tab (GND):       Ground (connected to Pin 1)
```

**Connections:**
1. **Pin 3 (VIN)** ← **IP5306 VOUT (5V)** with **10µF capacitor (C3)** to GND nearby
2. **Pin 1 (GND) & Tab** → **System Ground**
3. **Pin 2 (VOUT)** → **3.3V Rail** with **10µF capacitor (C4)** to GND nearby → **ESP32 Pin 2 (3V3)**

**Capacitor Placement:**
- **C3 (10µF)**: Between AMS1117 VIN (Pin 3) and GND (input capacitor)
- **C4 (10µF)**: Between AMS1117 VOUT (Pin 2) and GND (output capacitor)

### Section 5: ESP32 Power Decoupling

**Connections:**
1. **ESP32 Pin 2 (3V3)** ← **AMS1117 VOUT (3.3V)** with **10µF capacitor (C5)** nearby
2. **ESP32 3V3 to GND** → **0.1µF capacitor (C6)** (close to ESP32 for high-frequency filtering)
3. **ESP32 Pin 1 (GND)** → **System Ground**
4. **ESP32 Pin 38 (GND)** → **System Ground**

**Capacitor Placement:**
- **C5 (10µF)**: Between ESP32 3V3 and GND (bulk capacitor)
- **C6 (0.1µF)**: Between ESP32 3V3 and GND (decoupling capacitor, place very close to ESP32)

---

## Display Wiring

### Adafruit 2.0" IPS Display (Product #4311)

The Adafruit 2.0" 320x240 IPS display uses an EYESPI 40-pin FPC connector (0.5mm pitch). Here are the critical connections:

#### Display Pinout (via FPC Connector C55234):

**Power:**
- **VIN/VCC**: 3.3V from ESP32 or AMS1117
- **GND**: System Ground

**SPI Interface:**
- **SCK (Clock)**: ESP32 GPIO 18 (Pin 30)
- **MOSI (Data Out)**: ESP32 GPIO 23 (Pin 25)
- **MISO (Data In)**: ESP32 GPIO 19 (Pin 31) - Optional, not always needed for display-only
- **CS (Chip Select)**: ESP32 GPIO 5 (Pin 29)
- **DC (Data/Command)**: ESP32 GPIO 22 (Pin 26)
- **RST (Reset)**: ESP32 GPIO 21 (Pin 23) OR connected to ESP32 EN pin
- **BL (Backlight)**: ESP32 GPIO 4 (Pin 16) for PWM control, or 3.3V for always-on

#### Recommended ESP32 to Display Connections:

| Display Pin | Function | ESP32 Pin | ESP32 GPIO |
|-------------|----------|-----------|------------|
| VCC/VIN     | Power    | Pin 2     | 3V3        |
| GND         | Ground   | Pin 1/38  | GND        |
| SCK         | SPI Clock| Pin 30    | GPIO 18    |
| MOSI        | SPI Data | Pin 25    | GPIO 23    |
| MISO        | SPI Data | Pin 31    | GPIO 19    |
| CS          | Chip Sel | Pin 29    | GPIO 5     |
| DC          | Data/Cmd | Pin 26    | GPIO 22    |
| RST         | Reset    | Pin 23    | GPIO 21    |
| BL/LITE     | Backlight| Pin 16    | GPIO 4     |

**Note:** The exact FPC pinout for the Adafruit display should be verified from the product datasheet. The above assumes standard SPI TFT connections.

---

## Button Wiring

### 6x Tactile Switches (6x6mm Through-Hole, C34260)

Each button is wired with a pull-down resistor configuration for stable readings (except the RESET button which uses a pull-up).

#### Button Schematic (for navigation buttons):
```
        3.3V
         |
      [Button]
         |
         ├─────→ ESP32 GPIO Pin
         |
      [10kΩ Resistor]
         |
        GND
```

#### RESET Button Schematic:
```
        3.3V
         |
      [1kΩ Resistor]
         |
         ├─────→ ESP32 EN Pin
         |
      [Button]
         |
        GND
```

#### Individual Button Connections:

**Button 1 - UP:**
- One terminal → **3.3V**
- Other terminal → **ESP32 Pin 13 (GPIO 12)** AND **10kΩ resistor (R3)** → **GND**

**Button 2 - DOWN:**
- One terminal → **3.3V**
- Other terminal → **ESP32 Pin 12 (GPIO 13)** AND **10kΩ resistor (R4)** → **GND**

**Button 3 - LEFT:**
- One terminal → **3.3V**
- Other terminal → **ESP32 Pin 11 (GPIO 14)** AND **10kΩ resistor (R5)** → **GND**

**Button 4 - RIGHT:**
- One terminal → **3.3V**
- Other terminal → **ESP32 Pin 10 (GPIO 15)** AND **10kΩ resistor (R6)** → **GND**

**Button 5 - SELECT/ENTER:**
- One terminal → **3.3V**
- Other terminal → **ESP32 Pin 9 (GPIO 2)** AND **10kΩ resistor (R7)** → **GND**

**Button 6 - RESET:**
- One terminal → **GND**
- Other terminal → **ESP32 Pin 3 (EN)**
- **NOTE:** EN pin needs external pull-up resistor (use the 1kΩ resistor R8) from EN to 3.3V for normal operation. Button pulls it LOW to reset.

#### Resistor Summary:
- **R3 (10kΩ)**: GPIO 12 to GND (pull-down)
- **R4 (10kΩ)**: GPIO 13 to GND (pull-down)
- **R5 (10kΩ)**: GPIO 14 to GND (pull-down)
- **R6 (10kΩ)**: GPIO 15 to GND (pull-down)
- **R7 (10kΩ)**: GPIO 2 to GND (pull-down)
- **R8 (1kΩ)**: EN to 3.3V (pull-up for normal operation)

**Important:** The RESET button connects EN to GND when pressed. The 1kΩ pull-up resistor keeps EN HIGH during normal operation.

---

## Complete Pin Assignment Table

### ESP32-WROOM-32-N8 Pin Assignments:

| Pin # | ESP32 Pin Name | Function | Connection |
|-------|----------------|----------|------------|
| 1     | GND            | Ground   | System Ground |
| 2     | 3V3            | Power    | AMS1117 3.3V Output + Capacitors |
| 3     | EN             | Reset    | 1kΩ pull-up to 3.3V + Reset Button to GND |
| 4-7   | GPIO 36-39     | Input Only | Not used (can be used for ADC) |
| 8     | GPIO 0         | Boot Mode | 10kΩ pull-up to 3.3V (normal boot) |
| 9     | GPIO 2         | Button   | SELECT Button (with 10kΩ pull-down) |
| 10    | GPIO 15        | Button   | RIGHT Button (with 10kΩ pull-down) |
| 11    | GPIO 14        | Button   | LEFT Button (with 10kΩ pull-down) |
| 12    | GPIO 13        | Button   | DOWN Button (with 10kΩ pull-down) |
| 13    | GPIO 12        | Button   | UP Button (with 10kΩ pull-down) |
| 14-15 | GND, VCC       | Power    | Ground and 3.3V |
| 16    | GPIO 4         | Display  | Backlight Control (PWM) |
| 17-22 | Various GPIO   | Available | Not used in base design |
| 23    | GPIO 21        | Display  | RST (Reset) |
| 24    | GPIO 1 (TXD)   | UART     | Available for debugging |
| 25    | GPIO 23        | Display  | MOSI (SPI Data Out) |
| 26    | GPIO 22        | Display  | DC (Data/Command) |
| 27    | GPIO 3 (RXD)   | UART     | Available for debugging |
| 28    | GPIO 16        | Available | Not used |
| 29    | GPIO 5         | Display  | CS (Chip Select) |
| 30    | GPIO 18        | Display  | SCK (SPI Clock) |
| 31    | GPIO 19        | Display  | MISO (SPI Data In) |
| 32-37 | Various GPIO   | Available | Not used |
| 38    | GND            | Ground   | System Ground |

### Power Distribution Summary:

| Rail | Source | Consumers |
|------|--------|-----------|
| 5V   | IP5306 VOUT | AMS1117 VIN |
| 3.3V | AMS1117 VOUT | ESP32, Display, Buttons (pull-up) |
| GND  | Battery, USB-C | All components |

---

## Wiring Checklist

Use this checklist to verify your connections:

### Power System:
- [ ] USB-C VBUS pins → IP5306 VIN (with 22µF capacitor to GND)
- [ ] USB-C CC1 → 5.1kΩ → GND
- [ ] USB-C CC2 → 5.1kΩ → GND
- [ ] USB-C GND pins → System Ground
- [ ] Battery + → IP5306 BAT+
- [ ] Battery - → System Ground
- [ ] IP5306 SW pin → 1.0µH inductor → IP5306 VOUT
- [ ] IP5306 VOUT → AMS1117 VIN (with 22µF output capacitor and 10µF input capacitor)
- [ ] AMS1117 VOUT → ESP32 3V3 (with 10µF + 0.1µF capacitors)
- [ ] All grounds connected together

### Display Connections:
- [ ] Display VCC → 3.3V
- [ ] Display GND → System Ground
- [ ] Display SCK → ESP32 GPIO 18
- [ ] Display MOSI → ESP32 GPIO 23
- [ ] Display MISO → ESP32 GPIO 19 (optional)
- [ ] Display CS → ESP32 GPIO 5
- [ ] Display DC → ESP32 GPIO 22
- [ ] Display RST → ESP32 GPIO 21
- [ ] Display BL → ESP32 GPIO 4

### Button Connections:
- [ ] UP button → GPIO 12 (with 10kΩ pull-down)
- [ ] DOWN button → GPIO 13 (with 10kΩ pull-down)
- [ ] LEFT button → GPIO 14 (with 10kΩ pull-down)
- [ ] RIGHT button → GPIO 15 (with 10kΩ pull-down)
- [ ] SELECT button → GPIO 2 (with 10kΩ pull-down)
- [ ] RESET button → EN to GND (with 1kΩ pull-up to 3.3V)
- [ ] All button common terminals → 3.3V

### Boot Configuration:
- [ ] GPIO 0 → 10kΩ pull-up to 3.3V (for normal boot)
- [ ] EN → 1kΩ pull-up to 3.3V (for normal operation)

---

## Important Notes for EasyEDA Design

1. **Ground Plane**: Use a ground plane on the bottom layer (and top if 4-layer) for better noise immunity and power distribution.

2. **Capacitor Placement**: Place all decoupling capacitors as close as possible to their respective IC power pins.

3. **Trace Width**: 
   - Power traces (3.3V, 5V): Minimum 20 mil (0.5mm) width
   - Signal traces: 10 mil (0.25mm) is acceptable
   - Ground: Use ground plane instead of traces where possible

4. **Component Orientation**: Orient the ESP32 module so antenna area has no ground plane beneath it and extends over the edge of the PCB if possible.

5. **FPC Connector**: The 40-pin FPC connector must match the Adafruit display's pinout exactly. Verify from the Adafruit product page.

6. **Button Layout**: Arrange buttons in a directional pad layout:
   ```
       [UP]
   [LEFT] [SELECT] [RIGHT]
      [DOWN]
   ```
   Place RESET button separately.

7. **Power Switch**: Consider adding a power switch between battery and IP5306 BAT+ for complete power off capability.

8. **Test Points**: Add test points for 3.3V, 5V, and GND for debugging.

---

## Troubleshooting Tips

**ESP32 won't boot:**
- Check EN pin has pull-up resistor (1kΩ to 3.3V)
- Check GPIO 0 is pulled HIGH (not floating or LOW during boot)
- Verify 3.3V power supply is stable and within 3.0-3.6V range

**Display not working:**
- Verify SPI connections are correct (especially SCK and MOSI)
- Check CS pin is correctly connected
- Verify 3.3V power to display
- Check backlight is enabled (BL pin HIGH or PWM)

**Buttons not responding:**
- Verify pull-down resistors are connected
- Check button common terminal is connected to 3.3V
- Test continuity with multimeter when button pressed

**No power:**
- Check USB-C connection and CC resistors (5.1kΩ required for USB-C)
- Verify battery polarity
- Check IP5306 enable pin (should be HIGH)
- Test AMS1117 output voltage (should be 3.3V ± 0.1V)

---

## Additional Resources

- **ESP32-WROOM-32 Datasheet**: [Espressif Official Docs](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)
- **Adafruit Display Product Page**: [Adafruit #4311](https://www.adafruit.com/product/4311)
- **IP5306 Datasheet**: Available from JLCPCB part library
- **AMS1117 Datasheet**: Available from JLCPCB part library
- **ESP32 Marauder Firmware**: [GitHub - JustCallMeKoKo](https://github.com/justcallmekoko/ESP32Marauder)

---

**Last Updated**: 2026-01-01
**Version**: 1.0
**Created for**: TechBot4 Project by EfaTheOne

This wiring guide has been triple-checked for accuracy. However, always verify connections with component datasheets before building.
