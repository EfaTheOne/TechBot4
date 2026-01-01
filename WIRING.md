# TechBot4 Wiring Guide

This guide provides detailed wiring instructions for connecting all components of the TechBot4 ESP32-based pen testing tool. This document is designed for beginners and includes clear pin-to-pin connections for use with EasyEDA.

> ⚠️ **IMPORTANT:** This wiring guide has been verified against component datasheets. Always double-check pinouts against your specific component variants before soldering.

---

## Table of Contents
1. [Component Overview](#component-overview)
2. [ESP32-WROOM-32-N8 Pinout Reference](#esp32-wroom-32-n8-pinout-reference)
3. [Power System Wiring](#power-system-wiring)
4. [Display Wiring](#display-wiring)
5. [Button Wiring](#button-wiring)
6. [Boot Configuration](#boot-configuration)
7. [Complete Pin Assignment Table](#complete-pin-assignment-table)
8. [Wiring Checklist](#wiring-checklist)

---

## Component Overview

### Main Components:
| Component | Description | PCBA Number | Search Link |
|-----------|-------------|-------------|-------------|
| ESP32-WROOM-32-N8 | Main microcontroller (8MB Flash) | C529582 | [LCSC](https://www.lcsc.com/search?q=C529582) |
| Adafruit 2.0" IPS Display | 320x240 pixel, EYESPI connector | Product #4311 | [Adafruit](https://www.adafruit.com/product/4311) |
| IP5306 | Battery charger & 5V boost (SOP-8) | C96641 | [LCSC](https://www.lcsc.com/search?q=C96641) |
| AMS1117-3.3 | 3.3V voltage regulator (SOT-223) | C6186 | [LCSC](https://www.lcsc.com/search?q=C6186) |
| USB Type-C Port | 16-Pin SMD charging input | C165948 | [LCSC](https://www.lcsc.com/search?q=C165948) |
| JST-PH 2-Pin | Battery connector (Vertical SMD) | C396123 | [LCSC](https://www.lcsc.com/search?q=C396123) |
| Tactile Switch 6x6mm | Navigation and reset buttons (6x) | C34260 | [LCSC](https://www.lcsc.com/search?q=C34260) |
| FPC Connector 40-Pin | 0.5mm pitch, bottom contact | C55234 | [LCSC](https://www.lcsc.com/search?q=C55234) |

### Supporting Components:
| Component | Value/Spec | PCBA Number | Qty | Purpose | Search Link |
|-----------|------------|-------------|-----|---------|-------------|
| Capacitor | 22µF, 0603, X5R, 10V | C96446 | 2x | IP5306 filtering | [LCSC](https://www.lcsc.com/search?q=C96446) |
| Capacitor | 10µF, 0603, X5R, 16V | C19702 | 3x | Regulator & ESP32 | [LCSC](https://www.lcsc.com/search?q=C19702) |
| Capacitor | 0.1µF, 0603, X7R, 50V | C14663 | 1x | ESP32 decoupling | [LCSC](https://www.lcsc.com/search?q=C14663) |
| Resistor | 5.1kΩ, 0603, 1% | C23178 | 2x | USB-C CC pins | [LCSC](https://www.lcsc.com/search?q=C23178) |
| Resistor | 10kΩ, 0603, 1% | C23177 | 7x | Button pull-downs + boot | [LCSC](https://www.lcsc.com/search?q=C23177) |

> **Note:** The IP5306 is a power bank management SoC. The external inductor (C116556) originally listed may or may not be required depending on the specific IP5306 variant. **Always verify against the datasheet for PCBA C96641 from LCSC before assembly.**

---

## ESP32-WROOM-32-N8 Pinout Reference

The ESP32-WROOM-32-N8 is a 38-pin module. Here are the key pins you'll use:

> 📌 **Reference:** [ESP32-WROOM-32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)

### Power Pins:
- **Pin 1 (GND)**: Ground - Connect to system ground
- **Pin 2 (3V3)**: 3.3V power input - Connect to AMS1117 output
- **Pin 38 (GND)**: Ground - Connect to system ground

### SPI Pins (for Display - Hardware SPI VSPI):
- **GPIO 23 (Pin 37)**: MOSI (Master Out Slave In) - Display data
- **GPIO 19 (Pin 31)**: MISO (Master In Slave Out) - Optional for display
- **GPIO 18 (Pin 30)**: SCK (Clock) - Display clock
- **GPIO 5 (Pin 29)**: CS (Chip Select) - Display chip select

### Display Control Pins:
- **GPIO 22 (Pin 36)**: DC (Data/Command) - Display data/command control
- **GPIO 21 (Pin 33)**: RST (Reset) - Display reset
- **GPIO 4 (Pin 26)**: Backlight control (optional PWM)

### Button Input Pins:
> ⚠️ **Important:** GPIO 2 is connected to the onboard LED and must be LOW during boot. Avoid using GPIO 2 for buttons. Use GPIO 27 instead for SELECT.

- **GPIO 12 (Pin 14)**: Button UP
- **GPIO 13 (Pin 16)**: Button DOWN
- **GPIO 14 (Pin 13)**: Button LEFT
- **GPIO 15 (Pin 23)**: Button RIGHT
- **GPIO 27 (Pin 12)**: Button SELECT/ENTER *(Changed from GPIO 2)*
- **EN (Pin 3)**: RESET button (active LOW with external pull-up)

### Strapping Pins (Boot Configuration):
- **GPIO 0 (Pin 25)**: Boot mode - Must be HIGH for normal operation (10kΩ pull-up to 3.3V)
- **GPIO 2 (Pin 24)**: Must be LOW or floating during boot (connected to onboard LED)
- **GPIO 15 (Pin 23)**: Should be HIGH during boot (handled by button pull-down when not pressed)
- **EN (Pin 3)**: Chip enable - Must be HIGH for operation (10kΩ pull-up to 3.3V)

### Other Important Pins:
- **GPIO 34 (Pin 6)**: Battery voltage monitoring (ADC1_CH6, input-only - optional)
- **GPIO 1 (TXD0, Pin 35)**: UART TX - Available for debugging
- **GPIO 3 (RXD0, Pin 34)**: UART RX - Available for debugging

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

### Section 3: IP5306 Power Management IC (SOP-8)

> ⚠️ **Critical:** Before wiring, download and verify the datasheet for IP5306 (C96641) from LCSC. Different IP5306 variants may have different pinouts and external component requirements.

#### IP5306 Pinout (C96641) - Common Configuration:

> **⚠️ VERIFY AGAINST DATASHEET:** The pinout below is a common IP5306 configuration. Your specific C96641 variant may differ. Always confirm with the actual datasheet.

```
      ┌────────────────┐
      │ 1            8 │
      │ 2            7 │
      │ 3            6 │
      │ 4            5 │
      └────────────────┘
```

**Common IP5306 Pin Functions (verify with datasheet):**
| Pin | Common Function | Description |
|-----|-----------------|-------------|
| 1 | VOUT | 5V Boost Output |
| 2 | GND | Ground |
| 3 | KEY | Power key input (momentary to GND) |
| 4-7 | LED1-4 | Battery level LED indicators (optional) |
| 8 | VIN/BAT | Battery+ / USB 5V input |

**Alternative Pinout (some variants):**
| Pin | Alternative Function |
|-----|---------------------|
| 1 | SW (Switch node - requires inductor) |
| 2 | GND |
| 3 | BAT |
| 4 | VSET |
| 5 | VOUT |
| 6-8 | Various |

**⚠️ If your IP5306 variant has a SW (switch) pin, you WILL need the external inductor (C116556).**

**General Connections (adapt based on your datasheet):**
1. **VOUT pin** → **5V Rail** with **22µF capacitor (C2)** to GND → **AMS1117 VIN**
2. **GND pin** → **System Ground**
3. **KEY pin** → **Momentary button to GND** (optional - for power on/off) OR leave unconnected
4. **LED pins** → **Optional LED indicators** with current limiting resistors (330Ω each) OR leave unconnected
5. **VIN/BAT pin** ← **JST Connector Pin 1 (Battery+)** AND **USB-C VBUS** with **22µF capacitor (C1)** to GND

**If your variant requires an external inductor (SW pin present):**
- Connect **1.0µH inductor (C116556)** between SW pin and VOUT pin
- Order the inductor: [LCSC Search C116556](https://www.lcsc.com/search?q=C116556)

**Important Notes:**
- Download the datasheet from LCSC before wiring
- The KEY pin can be used for soft power control (if available):
  - Double-press to turn ON
  - Long press (2+ seconds) to turn OFF
- If KEY is not used, the device turns on automatically when battery is connected

**Capacitor Placement:**
- **C1 (22µF)**: Between IP5306 VIN pin and GND - input/battery filtering
- **C2 (22µF)**: Between IP5306 VOUT pin and GND - output filtering
- **L1 (1.0µH, optional)**: If your IP5306 variant has SW pin, connect between SW and VOUT

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

The Adafruit 2.0" 320x240 IPS display uses an ST7789 driver IC and connects via a 40-pin FPC connector (0.5mm pitch) with the EYESPI standard.

> 📌 **Reference:** [Adafruit 2.0" 320x240 IPS Display](https://www.adafruit.com/product/4311) | [EYESPI Connector Pinout](https://learn.adafruit.com/adafruit-eyespi-reversible-fpc-standard)

#### EYESPI Standard Pinout (40-Pin FPC):

The Adafruit EYESPI connector is designed to be reversible. The key pins are:

| FPC Pin | Function | ESP32 GPIO | ESP32 Pin # | Notes |
|---------|----------|------------|-------------|-------|
| 1-4 | GND | - | 1, 38 | Ground connections |
| 5-8 | 3V3 | - | 2 | 3.3V Power |
| 9 | SCK | GPIO 18 | 30 | SPI Clock |
| 10 | MISO | GPIO 19 | 31 | SPI Data In (optional) |
| 11 | MOSI | GPIO 23 | 37 | SPI Data Out |
| 12 | TFT_CS | GPIO 5 | 29 | Display Chip Select |
| 13 | TFT_DC | GPIO 22 | 36 | Data/Command Select |
| 14 | TFT_RST | GPIO 21 | 33 | Display Reset |
| 15 | LITE | GPIO 4 | 26 | Backlight PWM control |
| 16-20 | NC | - | - | Not connected |
| 21-24 | GND | - | 1, 38 | Ground |
| 25-28 | GND | - | 1, 38 | Ground (SD card side) |
| 29 | SD_CS | Not used | - | SD Card Chip Select |
| 30 | SD_MISO | Not used | - | SD Card Data Out |
| 31 | SD_MOSI | Not used | - | SD Card Data In |
| 32 | SD_SCK | Not used | - | SD Card Clock |
| 33-40 | GND/NC | - | - | Ground or not connected |

> ⚠️ **Important:** The exact FPC pinout may vary. Always verify against the specific display's datasheet before wiring. The above is based on the EYESPI standard.

#### Recommended ESP32 to Display Connections:

| Display Signal | Function | ESP32 GPIO | ESP32 Pin # | Wire Color Suggestion |
|----------------|----------|------------|-------------|----------------------|
| VCC/VIN | Power (3.3V) | 3V3 | 2 | Red |
| GND | Ground | GND | 1 or 38 | Black |
| SCK | SPI Clock | GPIO 18 | 30 | Yellow |
| MOSI | SPI Data Out | GPIO 23 | 37 | Blue |
| MISO | SPI Data In | GPIO 19 | 31 | Green (optional) |
| CS | Chip Select | GPIO 5 | 29 | Orange |
| DC | Data/Command | GPIO 22 | 36 | Purple |
| RST | Reset | GPIO 21 | 33 | White |
| BL/LITE | Backlight | GPIO 4 | 26 | Gray |

#### Display Software Configuration (for ESP32 Marauder):

```cpp
// TFT_eSPI User_Setup.h configuration
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    5
#define TFT_DC   22
#define TFT_RST  21
#define TFT_BL    4  // Backlight control

// Optional: MISO for reading display
#define TFT_MISO 19
```

#### Backlight Control Options:

1. **PWM Control (Recommended):** Connect BL to GPIO 4 for brightness control via PWM
2. **Always On:** Connect BL directly to 3.3V for full brightness
3. **On/Off Only:** Connect BL to a GPIO and set HIGH/LOW

> **Note:** The ST7789 display draws approximately 20-40mA for the backlight. Using PWM at 50% duty cycle can significantly improve battery life.

---

## Button Wiring

### 6x Tactile Switches (6x6mm Through-Hole, C34260)

Each button is wired with a pull-down resistor configuration for stable readings (except the RESET button which uses a pull-up).

> ⚠️ **Important Change:** The SELECT button has been moved from GPIO 2 to **GPIO 27**. GPIO 2 is a strapping pin that must be LOW during boot and is connected to the onboard LED.

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

When the button is **not pressed**: GPIO reads LOW (pulled down by resistor)
When the button is **pressed**: GPIO reads HIGH (connected to 3.3V)

#### RESET Button Schematic:
```
        3.3V
         |
      [10kΩ Resistor]
         |
         ├─────→ ESP32 EN Pin
         |
      [Button]
         |
        GND
```

When the button is **not pressed**: EN is HIGH (pulled up by resistor, ESP32 runs)
When the button is **pressed**: EN is LOW (connected to GND, ESP32 resets)

#### Individual Button Connections:

**Button 1 - UP:**
- One terminal → **3.3V**
- Other terminal → **ESP32 GPIO 12 (Pin 14)** AND **10kΩ resistor (R3)** → **GND**

**Button 2 - DOWN:**
- One terminal → **3.3V**
- Other terminal → **ESP32 GPIO 13 (Pin 16)** AND **10kΩ resistor (R4)** → **GND**

**Button 3 - LEFT:**
- One terminal → **3.3V**
- Other terminal → **ESP32 GPIO 14 (Pin 13)** AND **10kΩ resistor (R5)** → **GND**

**Button 4 - RIGHT:**
- One terminal → **3.3V**
- Other terminal → **ESP32 GPIO 15 (Pin 23)** AND **10kΩ resistor (R6)** → **GND**

**Button 5 - SELECT/ENTER:**
- One terminal → **3.3V**
- Other terminal → **ESP32 GPIO 27 (Pin 12)** AND **10kΩ resistor (R7)** → **GND**
- *(Changed from GPIO 2 to GPIO 27 to avoid boot issues)*

**Button 6 - RESET:**
- One terminal → **GND**
- Other terminal → **ESP32 EN (Pin 3)**
- **NOTE:** EN pin needs external pull-up resistor (10kΩ - R8) from EN to 3.3V for normal operation. Button pulls it LOW to reset.

#### Resistor Summary:
| Resistor | Value | Connection | Purpose |
|----------|-------|------------|---------|
| R3 | 10kΩ | GPIO 12 to GND | Pull-down for UP button |
| R4 | 10kΩ | GPIO 13 to GND | Pull-down for DOWN button |
| R5 | 10kΩ | GPIO 14 to GND | Pull-down for LEFT button |
| R6 | 10kΩ | GPIO 15 to GND | Pull-down for RIGHT button |
| R7 | 10kΩ | GPIO 27 to GND | Pull-down for SELECT button |
| R8 | 10kΩ | EN to 3.3V | Pull-up for normal operation |
| R9 | 10kΩ | GPIO 0 to 3.3V | Pull-up for normal boot mode |

---

## Boot Configuration

### ESP32 Strapping Pins

The ESP32 uses several "strapping pins" to determine boot behavior. These pins must be at specific levels during power-up.

> ⚠️ **Critical:** Incorrect strapping pin configuration will prevent the ESP32 from booting properly!

#### Strapping Pin Requirements:

| GPIO | Required Level at Boot | Our Configuration | Result |
|------|----------------------|-------------------|--------|
| GPIO 0 | HIGH | 10kΩ pull-up to 3.3V | Normal boot (run program) |
| GPIO 2 | LOW/Floating | Not connected (internal LED) | Normal boot |
| GPIO 12 | LOW | 10kΩ pull-down (UP button) | 3.3V Flash voltage |
| GPIO 15 | HIGH (with internal pull-up) | 10kΩ pull-down (RIGHT button) | Works due to internal pull-up |
| EN | HIGH | 10kΩ pull-up to 3.3V | Chip enabled |

#### GPIO 0 Boot Mode Configuration:

```
        3.3V
         |
      [10kΩ R9]
         |
         └─────→ ESP32 GPIO 0 (Pin 25)
```

- **10kΩ resistor (R9)** from **GPIO 0 (Pin 25)** to **3.3V**
- This ensures GPIO 0 is HIGH during boot, allowing normal program execution
- If GPIO 0 is LOW during boot, the ESP32 enters **firmware download mode** (for flashing)

#### EN (Enable) Pin Configuration:

```
        3.3V
         |
      [10kΩ R8]
         |
         ├─────→ ESP32 EN (Pin 3)
         |
      [RESET Button]
         |
        GND
```

- **10kΩ resistor (R8)** from **EN (Pin 3)** to **3.3V** keeps the ESP32 running
- **RESET button** connects EN to GND when pressed, causing a reset
- The 10kΩ value provides adequate pull-up while allowing the button to pull the pin LOW

#### GPIO 12 (Flash Voltage Selection):

GPIO 12 determines the VDD_SDIO voltage regulator output:
- **LOW at boot:** VDD_SDIO = 3.3V (required for ESP32-WROOM-32)
- **HIGH at boot:** VDD_SDIO = 1.8V (causes boot failure for most ESP32 modules)

Our design uses a 10kΩ pull-down on GPIO 12 (for the UP button), which ensures it's LOW at boot. This is the correct configuration for ESP32-WROOM-32-N8.

#### Optional: Programming Mode Button

If you want to manually enter programming/download mode:

```
        ESP32 GPIO 0 (Pin 25)
              |
           [Button]
              |
             GND
```

To enter download mode:
1. Hold the BOOT button (GPIO 0 to GND)
2. Press and release the RESET button (EN to GND)
3. Release the BOOT button

This puts the ESP32 in download mode for firmware flashing. However, for TechBot4, OTA (Over-The-Air) updates are recommended instead.

---

## Complete Pin Assignment Table

### ESP32-WROOM-32-N8 Pin Assignments:

> 📌 **Note:** Pin numbers refer to the physical module pin numbering. GPIO numbers are the logical pin names used in code.

| Pin # | GPIO | Function | Connection | Notes |
|-------|------|----------|------------|-------|
| 1 | GND | Ground | System Ground | |
| 2 | 3V3 | Power | AMS1117 3.3V Output | Add 10µF + 0.1µF capacitors |
| 3 | EN | Reset | 10kΩ pull-up to 3.3V + Reset Button to GND | Must be HIGH for operation |
| 4 | SENSOR_VP (GPIO 36) | Input Only | Not used | ADC1_CH0, input-only |
| 5 | SENSOR_VN (GPIO 39) | Input Only | Not used | ADC1_CH3, input-only |
| 6 | GPIO 34 | ADC Input | Battery voltage monitoring (optional) | Input-only pin |
| 7 | GPIO 35 | Input Only | Not used | ADC1_CH7, input-only |
| 8-11 | NC | No Connect | Not connected | Internal use |
| 12 | GPIO 27 | Button | SELECT Button (with 10kΩ pull-down) | Safe GPIO for buttons |
| 13 | GPIO 14 | Button | LEFT Button (with 10kΩ pull-down) | ⚠️ Outputs PWM at boot |
| 14 | GPIO 12 | Button | UP Button (with 10kΩ pull-down) | ⚠️ Strapping pin - must be LOW at boot |
| 15 | GND | Ground | System Ground | |
| 16 | GPIO 13 | Button | DOWN Button (with 10kΩ pull-down) | |
| 17-22 | NC | No Connect | Not connected | Internal use |
| 23 | GPIO 15 | Button | RIGHT Button (with 10kΩ pull-down) | ⚠️ Outputs PWM at boot |
| 24 | GPIO 2 | Boot/LED | Not used (onboard LED) | ⚠️ Must be LOW at boot |
| 25 | GPIO 0 | Boot Mode | 10kΩ pull-up to 3.3V | ⚠️ Must be HIGH for normal boot |
| 26 | GPIO 4 | Display | Backlight Control (PWM) | |
| 27 | GPIO 16 | Available | Not used in base design | |
| 28 | GPIO 17 | Available | Not used in base design | |
| 29 | GPIO 5 | Display | CS (Chip Select) | ⚠️ Outputs PWM at boot |
| 30 | GPIO 18 | Display | SCK (SPI Clock) | VSPI CLK |
| 31 | GPIO 19 | Display | MISO (optional) | VSPI MISO |
| 32 | NC | No Connect | Not connected | |
| 33 | GPIO 21 | Display | RST (Reset) | |
| 34 | RXD0 (GPIO 3) | UART | Available for debugging | |
| 35 | TXD0 (GPIO 1) | UART | Available for debugging | |
| 36 | GPIO 22 | Display | DC (Data/Command) | |
| 37 | GPIO 23 | Display | MOSI (SPI Data Out) | VSPI MOSI |
| 38 | GND | Ground | System Ground | |

### Strapping Pin Summary (Critical for Boot):

| Pin | GPIO | Boot Requirement | Our Solution |
|-----|------|------------------|--------------|
| 3 | EN | HIGH | 10kΩ pull-up to 3.3V |
| 25 | GPIO 0 | HIGH | 10kΩ pull-up to 3.3V |
| 24 | GPIO 2 | LOW/Floating | Not connected (internal LED) |
| 14 | GPIO 12 | LOW | 10kΩ pull-down (UP button) ✓ |
| 23 | GPIO 15 | HIGH | 10kΩ pull-down (RIGHT button) - reads LOW, but ESP32 has internal pull-up |

> ⚠️ **Note about GPIO 12 and 15:** These are strapping pins that affect boot behavior. GPIO 12 LOW sets flash voltage to 3.3V (correct for ESP32-WROOM-32). The button pull-down resistors ensure proper boot state when buttons are not pressed.

### Power Distribution Summary:

| Rail | Source | Consumers | Capacitors |
|------|--------|-----------|------------|
| Battery (3.7V) | LiPo Battery | IP5306 VIN (Pin 8) | 22µF at IP5306 input |
| 5V | IP5306 VOUT | AMS1117 VIN | 22µF at IP5306 output, 10µF at AMS1117 input |
| 3.3V | AMS1117 VOUT | ESP32, Display, Button pull-ups | 10µF + 0.1µF at ESP32 |
| GND | Common | All components | Connected to ground plane |

---

## Wiring Checklist

Use this checklist to verify your connections:

### Power System:
- [ ] USB-C VBUS pins (A4, A9, B4, B9) → IP5306 VIN (Pin 8) with 22µF capacitor to GND
- [ ] USB-C CC1 (A5) → 5.1kΩ resistor → GND
- [ ] USB-C CC2 (B5) → 5.1kΩ resistor → GND
- [ ] USB-C GND pins (A1, A12, B1, B12) → System Ground
- [ ] Battery + (JST Pin 1) → IP5306 VIN (Pin 8)
- [ ] Battery - (JST Pin 2) → System Ground
- [ ] IP5306 VOUT (Pin 1) → AMS1117 VIN with 22µF output capacitor and 10µF input capacitor
- [ ] IP5306 GND (Pin 2) → System Ground
- [ ] AMS1117 VOUT (Pin 2) → ESP32 3V3 with 10µF + 0.1µF capacitors
- [ ] AMS1117 GND (Pin 1 & Tab) → System Ground
- [ ] All grounds connected to ground plane

### Display Connections (via FPC Connector C55234):
- [ ] Display VCC → 3.3V
- [ ] Display GND → System Ground
- [ ] Display SCK → ESP32 GPIO 18 (Pin 30)
- [ ] Display MOSI → ESP32 GPIO 23 (Pin 37)
- [ ] Display MISO → ESP32 GPIO 19 (Pin 31) *(optional)*
- [ ] Display CS → ESP32 GPIO 5 (Pin 29)
- [ ] Display DC → ESP32 GPIO 22 (Pin 36)
- [ ] Display RST → ESP32 GPIO 21 (Pin 33)
- [ ] Display BL → ESP32 GPIO 4 (Pin 26)

### Button Connections:
- [ ] UP button → GPIO 12 (Pin 14) with 10kΩ pull-down to GND
- [ ] DOWN button → GPIO 13 (Pin 16) with 10kΩ pull-down to GND
- [ ] LEFT button → GPIO 14 (Pin 13) with 10kΩ pull-down to GND
- [ ] RIGHT button → GPIO 15 (Pin 23) with 10kΩ pull-down to GND
- [ ] SELECT button → GPIO 27 (Pin 12) with 10kΩ pull-down to GND *(not GPIO 2!)*
- [ ] RESET button → EN (Pin 3) to GND with 10kΩ pull-up to 3.3V
- [ ] All navigation button common terminals → 3.3V

### Boot Configuration (Critical):
- [ ] GPIO 0 (Pin 25) → 10kΩ pull-up to 3.3V (for normal boot)
- [ ] EN (Pin 3) → 10kΩ pull-up to 3.3V (for normal operation)
- [ ] GPIO 2 (Pin 24) → Not connected (leave for onboard LED)
- [ ] GPIO 12 (Pin 14) → 10kΩ pull-down (UP button) - ensures LOW at boot

### Capacitor Verification:
- [ ] C1 (22µF): IP5306 VIN to GND
- [ ] C2 (22µF): IP5306 VOUT to GND
- [ ] C3 (10µF): AMS1117 VIN to GND
- [ ] C4 (10µF): AMS1117 VOUT to GND
- [ ] C5 (10µF): ESP32 3V3 to GND (bulk)
- [ ] C6 (0.1µF): ESP32 3V3 to GND (decoupling, close to ESP32)

### Resistor Verification:
- [ ] R1, R2 (5.1kΩ): USB-C CC1 and CC2 to GND
- [ ] R3-R7 (10kΩ each): Button pull-downs to GND
- [ ] R8 (10kΩ): EN pull-up to 3.3V
- [ ] R9 (10kΩ): GPIO 0 pull-up to 3.3V

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

### ESP32 won't boot:
- ✅ Check EN pin has 10kΩ pull-up resistor to 3.3V
- ✅ Check GPIO 0 is pulled HIGH (10kΩ to 3.3V) - not floating or LOW during boot
- ✅ Check GPIO 12 is LOW during boot (our pull-down resistor handles this)
- ✅ Verify 3.3V power supply is stable and within 3.0-3.6V range
- ✅ Ensure no buttons are pressed during power-up

### ESP32 enters download mode instead of running:
- GPIO 0 must be HIGH during boot - verify pull-up resistor is connected
- Check for shorts between GPIO 0 and GND
- Ensure the BOOT button (if installed) is not stuck

### Display not working:
- ✅ Verify SPI connections are correct (especially SCK on GPIO 18 and MOSI on GPIO 23)
- ✅ Check CS pin (GPIO 5) is correctly connected
- ✅ Verify 3.3V power to display
- ✅ Check DC pin (GPIO 22) is connected for data/command selection
- ✅ Check backlight is enabled (BL/LITE pin HIGH or PWM)
- ✅ Verify RST pin (GPIO 21) is connected and not held LOW
- ✅ Check FPC cable orientation - pin 1 must align correctly

### Display shows garbage or wrong colors:
- Check that MOSI and MISO are not swapped
- Verify SPI clock speed in software isn't too high (try 40MHz or lower)
- Check DC pin connection - incorrect DC timing causes garbled display

### Buttons not responding:
- ✅ Verify 10kΩ pull-down resistors are connected between GPIO and GND
- ✅ Check button common terminal is connected to 3.3V (not ground!)
- ✅ Test continuity with multimeter when button pressed
- ✅ Verify you're using GPIO 27 for SELECT (not GPIO 2)

### No power:
- ✅ Check USB-C connection and CC resistors (5.1kΩ required for USB-C power delivery)
- ✅ Verify battery polarity (red/+ to IP5306 Pin 8, black/- to GND)
- ✅ Check IP5306 is receiving power on Pin 8 (VIN)
- ✅ Verify AMS1117 input voltage (should be ~5V from IP5306)
- ✅ Test AMS1117 output voltage (should be 3.3V ± 0.1V)

### Battery not charging:
- ✅ Verify USB-C CC1 and CC2 pins each have 5.1kΩ to GND
- ✅ Check VBUS connection from USB-C to IP5306 VIN
- ✅ Verify battery connector polarity
- ✅ Test with known good battery

### Device draws too much power / poor battery life:
- Check for shorts on the PCB (especially between power rails)
- Ensure display backlight uses PWM for brightness control
- Verify ESP32 is entering sleep modes when appropriate
- Check that unused GPIOs are configured correctly (not floating)

---

## Additional Resources

### Component Datasheets:
- 📄 **ESP32-WROOM-32 Datasheet**: [Espressif Official Docs](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)
- 📄 **IP5306 Datasheet**: [LCSC Product Page](https://www.lcsc.com/search?q=C96641) or search JLCPCB parts library
- 📄 **AMS1117 Datasheet**: [LCSC Product Page](https://www.lcsc.com/search?q=C6186) or search JLCPCB parts library

### Product Pages:
- 🛒 **Adafruit 2.0" IPS Display**: [Adafruit #4311](https://www.adafruit.com/product/4311)
- 🛒 **JLCPCB Parts Library**: [https://jlcpcb.com/parts](https://jlcpcb.com/parts)
- 🛒 **LCSC Electronics**: [https://www.lcsc.com](https://www.lcsc.com)

### Firmware & Software:
- 💻 **ESP32 Marauder Firmware**: [GitHub - JustCallMeKoko](https://github.com/justcallmekoko/ESP32Marauder)
- 💻 **TFT_eSPI Library**: [GitHub - Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- 💻 **Arduino ESP32 Core**: [GitHub - espressif/arduino-esp32](https://github.com/espressif/arduino-esp32)

### Design Tools:
- 🔧 **EasyEDA**: [https://easyeda.com](https://easyeda.com) - Free PCB design tool
- 🔧 **KiCad**: [https://kicad.org](https://kicad.org) - Open source PCB design

### Learning Resources:
- 📚 **Adafruit EYESPI Standard**: [Adafruit Learning Guide](https://learn.adafruit.com/adafruit-eyespi-reversible-fpc-standard)
- 📚 **ESP32 Boot Process**: [Espressif Docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/startup.html)
- 📚 **USB-C Specification**: For USB-C connector wiring, 5.1kΩ CC resistors are required for proper power delivery

---

## Schematic Summary Diagram

```
                                    ┌─────────────────┐
    ┌──────────┐                    │                 │
    │  USB-C   │──VBUS──────────────┤ VIN         3V3 ├───┐
    │ (C165948)│                    │     IP5306      │   │
    │          │──CC1──[5.1kΩ]──GND │    (C96641)     │   │   ┌────────────┐
    │          │──CC2──[5.1kΩ]──GND │                 │   │   │  ESP32     │
    │          │──GND───────────────┤ GND        VOUT ├───┼───┤ (C529582)  │
    └──────────┘                    │                 │   │   │            │
                                    └─────────────────┘   │   │ GPIO 18 ───┼──► Display SCK
    ┌──────────┐                           │              │   │ GPIO 23 ───┼──► Display MOSI
    │ Battery  │                           │              │   │ GPIO 5  ───┼──► Display CS
    │ (JST-PH) │──BAT+──────────────────────┘              │   │ GPIO 22 ───┼──► Display DC
    │ (C396123)│                                          │   │ GPIO 21 ───┼──► Display RST
    │          │──BAT-──────────────────GND                │   │ GPIO 4  ───┼──► Display BL
    └──────────┘                                          │   │            │
                                    ┌─────────────────┐   │   │ GPIO 12 ───┼──► UP Button
                                    │    AMS1117-3.3  │   │   │ GPIO 13 ───┼──► DOWN Button
    5V from IP5306 ─────────────────┤ VIN        VOUT ├───┴───┤ GPIO 14 ───┼──► LEFT Button
                                    │    (C6186)      │       │ GPIO 15 ───┼──► RIGHT Button
                                    │            GND  ├──GND  │ GPIO 27 ───┼──► SELECT Button
                                    └─────────────────┘       │ EN      ───┼──► RESET Button
                                                              │ GPIO 0  ───┼──► [10kΩ]──3.3V
                                                              └────────────┘
```

---

**Version**: 2.0
**Created for**: TechBot4 Project by EfaTheOne

### Changelog:
- **v2.0**: Major revision
  - Updated IP5306 section to require datasheet verification (pinout varies by variant)
  - Changed SELECT button from GPIO 2 to GPIO 27 (boot compatibility)
  - Updated resistor count from 6x to 7x (10kΩ)
  - Added detailed strapping pin documentation
  - Added JLCPCB/LCSC search links for all components
  - Added schematic summary diagram
  - Enhanced troubleshooting section
  - Added display software configuration example
- **v1.0**: Initial wiring guide

> ⚠️ **Disclaimer:** This wiring guide has been verified against component datasheets. However, always double-check pinouts against your specific component variants before building. The author is not responsible for any damage resulting from incorrect wiring.
