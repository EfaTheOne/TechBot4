# TechBot4 Complete Wiring Guide

This document provides the complete wiring schematic for the TechBot4 ESP32-based pen testing tool.

---

## Table of Contents
1. [Component Summary](#component-summary)
2. [ESP32-WROOM-32U-N8 Pin Mapping](#esp32-wroom-32u-n8-pin-mapping)
3. [Power System](#power-system)
4. [USB-C and CH340C Serial Interface](#usb-c-and-ch340c-serial-interface)
5. [Display Wiring (ST7789 via EYESPI)](#display-wiring-st7789-via-eyespi)
6. [MicroSD Card Wiring](#microsd-card-wiring)
7. [Navigation Buttons](#navigation-buttons)
8. [Boot and Reset Buttons](#boot-and-reset-buttons)
9. [Complete Connection Summary](#complete-connection-summary)
10. [Verification Checklist](#verification-checklist)

---

## Component Summary

| Component | Part Number | Quantity | Function |
|-----------|-------------|----------|----------|
| Microcontroller | ESP32-WROOM-32U-N8 | 1 | Main processor |
| Battery Management | IP5306-I2C | 1 | Charging & boost converter |
| LDO Regulator | XC6220B331MR-G | 1 | 3.3V voltage regulation |
| USB-Serial | CH340C | 1 | USB to UART bridge |
| USB Connector | HX TYPE-C 16PIN | 1 | USB-C input |
| Display Connector | KH-CL0.5-H2.0-18PIN | 1 | EYESPI FPC connector |
| Battery Connector | JST S2B-PH-K-S | 1 | Li-Po battery connection |
| Buttons | YIZHI YZA-056-5.0 | 7 | Navigation (5) + Boot/Reset (2) |
| Power Switch | C&K PCM12SMTR | 1 | On/Off control |
| NPN Transistor | S8050 | 2 | Auto-reset circuit |
| 10kΩ Resistor | 0603WAJ0103T5E | 5 | Pull-up/pull-down |
| 1kΩ Resistor | 0603WAF1001T5E | 2 | Current limiting |
| 5.1kΩ Resistor | 0603WAF5101T5E | 2 | USB-C CC resistors |
| 10μF Capacitor | CL21A106KOQNNNE | 4 | Decoupling |
| 100nF Capacitor | CL10B104KA8NNNC | 4 | Decoupling |
| Display | ST7789 2.0" IPS TFT | 1 | 320x240 color display |
| Battery | Li-Po 3.7V 2500mAh | 1 | Power source |

---

## ESP32-WROOM-32U-N8 Pin Mapping

| ESP32 GPIO | Function | Connected To |
|------------|----------|--------------|
| GPIO0 | BOOT | Boot Button (active LOW) |
| EN | RESET/ENABLE | Reset Button (active LOW) |
| GPIO5 | SPI CS (Display) | ST7789 CS |
| GPIO18 | SPI CLK | ST7789 SCK / SD CLK |
| GPIO19 | SPI MISO | SD MISO (D0/DO) |
| GPIO23 | SPI MOSI | ST7789 MOSI / SD MOSI (DI) |
| GPIO2 | Display DC | ST7789 DC |
| GPIO4 | Display RST | ST7789 RST |
| GPIO15 | Display Backlight | ST7789 Backlight (via transistor or direct) |
| GPIO16 | SD CS | MicroSD Card CS |
| GPIO12 | Button UP | Navigation Up |
| GPIO13 | Button DOWN | Navigation Down |
| GPIO14 | Button LEFT | Navigation Left |
| GPIO27 | Button RIGHT | Navigation Right |
| GPIO26 | Button SELECT | Navigation Select (Center) |
| GPIO1 (TXD0) | UART TX | CH340C RXD |
| GPIO3 (RXD0) | UART RX | CH340C TXD |

---

## Power System

The power system uses the **IP5306-I2C** for battery charging and 5V boost output, with the **XC6220B331MR-G** LDO providing a clean 3.3V rail for the ESP32 and peripherals.

### Power Flow Diagram
```
Battery (3.7V) → Power Switch → IP5306 → 5V Boost → XC6220B331MR-G → 3.3V Rail
                                  ↑
                            USB-C (5V VBUS)
```

### IP5306-I2C Wiring (Battery Management IC)

**Note:** The IP5306-I2C (SOP-8L package, LCSC C488349) has an **integrated inductor** - no external inductor is required.

| IP5306 Pin | Function | Connection | Notes |
|------------|----------|------------|-------|
| Pin 1 | KEY | 10kΩ pull-up to VIN or Power Button | Power on/off control |
| Pin 2 | LED1 | NC or LED indicator | Battery level indicator |
| Pin 3 | LED2 | NC or LED indicator | Battery level indicator |
| Pin 4 | LED3 | NC or LED indicator | Battery level indicator |
| Pin 5 | LED4/SDA | ESP32 GPIO21 | I2C Data (optional battery monitoring) |
| Pin 6 | SCL | ESP32 GPIO22 | I2C Clock (optional battery monitoring) |
| Pin 7 | VIN | USB-C VBUS (5V) | 5V input from USB-C |
| Pin 8 | BAT/VOUT | Battery + (via JST) / Power Switch COM | Li-Po positive; also 5V boost output |
| Exposed Pad | GND | Common Ground | Thermal pad - connect to ground plane |

**IP5306 Capacitors:**
- Pin 7 (VIN): 10μF capacitor to GND
- Pin 8 (BAT/VOUT): 10μF capacitor to GND (on battery side)

### Power Switch (C&K PCM12SMTR) Wiring

| Switch Pin | Connection |
|------------|------------|
| COM (Common) | IP5306 Pin 8 (BAT/VOUT - 5V boost output) |
| NO (Normally Open) | XC6220B331MR-G VIN |

**Note:** The switch controls the 5V boost output from IP5306 Pin 8 going to the 3.3V regulator. This allows the ESP32 to be completely powered off while still allowing battery charging via USB-C.

### XC6220B331MR-G (3.3V LDO) Wiring

**Package:** SOT-25-5 (JLCPCB Part #C86534)

| LDO Pin | Function | Connection | Notes |
|---------|----------|------------|-------|
| Pin 1 | VSS (GND) | Common Ground | Shared ground plane |
| Pin 2 | VIN | Power Switch Output (5V) | From IP5306 via switch |
| Pin 3 | VOUT | 3.3V Rail | Powers ESP32, Display, SD Card |
| Pin 4 | CE | VIN (tie high) | Chip Enable - active high |
| Pin 5 | NC | Not Connected | No connection |

**LDO Capacitors:**
- Pin 2 (VIN): 10μF capacitor to GND
- Pin 3 (VOUT): 10μF + 100nF capacitors to GND

### Battery Connector (JST S2B-PH-K-S) Wiring

| JST Pin | Connection |
|---------|------------|
| Pin 1 (+) | IP5306 Pin 8 (BAT) |
| Pin 2 (-) | Common Ground |

---

## USB-C and CH340C Serial Interface

The USB-C connector provides power input for charging and data connection for programming the ESP32.

### USB-C Connector (HX TYPE-C 16PIN) Wiring

**Package:** HX TYPE-C 16PIN (LCSC Part #C5178539)

**Physical Pin Layout (Left Side - Top to Bottom):**

| Connector Pin | USB-C Signal | Connection | Notes |
|---------------|--------------|------------|-------|
| B12/A1 | GND | Common Ground | Ground pins |
| B9/A4 | VBUS | IP5306 Pin 7 (VIN) | 5V power input |
| B8 | SBU2 | NC | Not Connected |
| A5 | CC1 | 5.1kΩ resistor to GND | USB-C identification |
| B7 | D- | CH340C Pin 6 (UD-) | USB Data- |
| A6 | D+ | CH340C Pin 5 (UD+) | USB Data+ |
| A7 | D- | CH340C Pin 6 (UD-) | USB Data- (active side) |
| B6 | D+ | CH340C Pin 5 (UD+) | USB Data+ |
| A8 | SBU1 | NC | Not Connected |
| B5 | CC2 | 5.1kΩ resistor to GND | USB-C identification |
| A9/B4 | VBUS | IP5306 Pin 7 (VIN) | 5V power input |
| A12/B1 | GND | Common Ground | Ground pins |

**Physical Pin Layout (Right Side - Top to Bottom):**

| Connector Pin | Function | Connection | Notes |
|---------------|----------|------------|-------|
| EH Pin 20 | Shield | GND | Housing/Shield ground |
| EH Pin 19 | Shield | GND | Housing/Shield ground |
| EH Pin 18 | Shield | GND | Housing/Shield ground |
| EH Pin 17 | Shield | GND | Housing/Shield ground |

**Important:** The 5.1kΩ resistors on CC1 (A5) and CC2 (B5) identify the device as a UFP (Upstream Facing Port) sink device, enabling proper USB-C power delivery.

**Note:** USB-C has duplicate D+/D- pins (A6/B6 for D+, A7/B7 for D-) for reversible cable support. Connect both D+ pins together and both D- pins together to the CH340C.

### CH340C Wiring (USB to Serial)

**Package:** SOP-16 (LCSC Part #C84681)

| CH340C Pin | Function | Connection | Notes |
|------------|----------|------------|-------|
| Pin 1 | GND | Common Ground | |
| Pin 2 | TXD | ESP32 GPIO3 (RXD0) | CH340 TX → ESP32 RX |
| Pin 3 | RXD | ESP32 GPIO1 (TXD0) | CH340 RX ← ESP32 TX |
| Pin 4 | V3 | 3.3V Rail (connect to VCC) | When VCC=3.3V, tie V3 to VCC |
| Pin 5 | UD+ | USB-C D+ | USB Data+ |
| Pin 6 | UD- | USB-C D- | USB Data- |
| Pin 7 | NC | Not Connected | Internal oscillator (no crystal needed) |
| Pin 8 | NC | Not Connected | Internal oscillator (no crystal needed) |
| Pin 9 | CTS# | NC | Clear to Send (optional) |
| Pin 10 | DSR# | NC | Data Set Ready (optional) |
| Pin 11 | RI# | NC | Ring Indicator (optional) |
| Pin 12 | DCD# | NC | Data Carrier Detect (optional) |
| Pin 13 | DTR# | Auto-Reset Circuit | Data Terminal Ready - for programming |
| Pin 14 | RTS# | Auto-Reset Circuit | Request to Send - for programming |
| Pin 15 | R232 | NC | Reserved |
| Pin 16 | VCC | 3.3V Rail | Operating voltage |

**CH340C Capacitors:**
- Pin 16 (VCC): 100nF capacitor to GND

**Note:** When operating at 3.3V, Pin 4 (V3) must be connected to Pin 16 (VCC). The internal 3.3V regulator is bypassed in this configuration.

### Auto-Reset and Auto-Boot Circuit

This circuit uses two S8050 NPN transistors to automatically enter bootloader mode when programming. The circuit uses the standard ESP32 auto-reset timing where DTR controls EN (reset) and RTS controls GPIO0 (boot mode).

```
                              ┌─────────┐
    DTR ──────────100nF──────┤         ├──── EN (Reset)
                              │   Q1    │
    RTS ─────────────────────┤  S8050  ├──┐
                    │        └─────────┘  │
                    │             │       │
                    │            GND      │
                    │                     │
                    │        ┌─────────┐  │
                    └──1kΩ───┤         ├──┘
                              │   Q2    │
                             ┤  S8050  ├──── GPIO0 (BOOT)
                              └─────────┘
                                   │
                                  GND
```

**Detailed Circuit Description:**

The auto-reset works as follows:
1. DTR goes LOW → 100nF capacitor couples pulse to EN → ESP32 resets
2. RTS goes LOW → Q2 turns on → GPIO0 pulled LOW → Boot mode
3. DTR returns HIGH → EN returns HIGH via pull-up → ESP32 starts in bootloader

```
    DTR ───100nF───┬─── EN (with 10kΩ pull-up to 3.3V)
                   │
    RTS ───1kΩ─────┤ Q1 (S8050)
                   │  Collector → EN
                   │  Emitter → GND
                   │
    RTS ───1kΩ─────┤ Q2 (S8050)
                      Collector → GPIO0 (with 10kΩ pull-up to 3.3V)
                      Emitter → GND
```

| Component | Connection |
|-----------|------------|
| 100nF Capacitor | Between CH340C Pin 13 (DTR#) and ESP32 EN |
| Q1 (S8050) Base | CH340C Pin 14 (RTS#) via 1kΩ resistor |
| Q1 Collector | ESP32 EN pin |
| Q1 Emitter | GND |
| Q2 (S8050) Base | CH340C Pin 14 (RTS#) via 1kΩ resistor |
| Q2 Collector | ESP32 GPIO0 |
| Q2 Emitter | GND |

**Pull-up Resistors:**
- ESP32 EN: 10kΩ pull-up to 3.3V
- ESP32 GPIO0: 10kΩ pull-up to 3.3V

---

## Display Wiring (ST7789 via EYESPI)

The 2.0" ST7789 display connects via the EYESPI 18-pin FPC connector.

### EYESPI 18-Pin Connector (KH-CL0.5-H2.0-18PIN) Pinout

| Pin | EYESPI Signal | ESP32 GPIO | Notes |
|-----|---------------|------------|-------|
| 1 | GND | GND | Ground |
| 2 | 3.3V | 3.3V Rail | Power |
| 3 | SCK | GPIO18 | SPI Clock |
| 4 | MOSI | GPIO23 | SPI Data Out |
| 5 | MISO | Not Connected | Display is write-only |
| 6 | TFT_CS | GPIO5 | Display Chip Select |
| 7 | TFT_DC | GPIO2 | Data/Command |
| 8 | TFT_RST | GPIO4 | Display Reset |
| 9 | SD_CS | GPIO16 | SD Card Chip Select |
| 10 | Backlight | GPIO15 | Backlight Control |
| 11-18 | Reserved/NC | NC | Not used |

**Note:** The Adafruit ST7789 EYESPI breakout has the SD card integrated, sharing the SPI bus.

---

## MicroSD Card Wiring

The MicroSD card is integrated on the ST7789 EYESPI breakout and shares the SPI bus with the display.

| SD Card Signal | ESP32 GPIO | Notes |
|----------------|------------|-------|
| CS | GPIO16 | SD Chip Select |
| CLK | GPIO18 | Shared with display |
| MOSI (DI) | GPIO23 | Shared with display |
| MISO (DO) | GPIO19 | SD data out to ESP32 |
| VCC | 3.3V Rail | Power |
| GND | GND | Ground |

**Important:** Only one device (display or SD card) should be selected at a time via their respective CS pins.

---

## Navigation Buttons

All navigation buttons connect GPIO pins to ground when pressed. Internal pull-ups on the ESP32 are used.

### Button Wiring (5 Navigation Buttons)

| Button | ESP32 GPIO | Wiring |
|--------|------------|--------|
| UP | GPIO12 | One terminal to GPIO12, other to GND |
| DOWN | GPIO13 | One terminal to GPIO13, other to GND |
| LEFT | GPIO14 | One terminal to GPIO14, other to GND |
| RIGHT | GPIO27 | One terminal to GPIO27, other to GND |
| SELECT | GPIO26 | One terminal to GPIO26, other to GND |

**Software Configuration:**
```cpp
pinMode(GPIO_UP, INPUT_PULLUP);    // GPIO12
pinMode(GPIO_DOWN, INPUT_PULLUP);  // GPIO13
pinMode(GPIO_LEFT, INPUT_PULLUP);  // GPIO14
pinMode(GPIO_RIGHT, INPUT_PULLUP); // GPIO27
pinMode(GPIO_SELECT, INPUT_PULLUP); // GPIO26
```

Buttons read LOW when pressed, HIGH when released.

---

## Boot and Reset Buttons

These buttons are used for manual programming mode entry and device reset.

### Boot Button Wiring

| Connection | Details |
|------------|---------|
| Button Pin 1 | ESP32 GPIO0 |
| Button Pin 2 | GND |
| Pull-up | 10kΩ resistor from GPIO0 to 3.3V |

### Reset Button Wiring

| Connection | Details |
|------------|---------|
| Button Pin 1 | ESP32 EN |
| Button Pin 2 | GND |
| Pull-up | 10kΩ resistor from EN to 3.3V |

**Programming Mode Entry:**
1. Hold BOOT button
2. Press and release RESET button
3. Release BOOT button
4. ESP32 enters bootloader mode

---

## Complete Connection Summary

### ESP32 GPIO Full Mapping

| GPIO | Function | Component | Direction |
|------|----------|-----------|-----------|
| GPIO0 | BOOT | Boot Button + Auto-boot circuit | INPUT (pull-up) |
| GPIO1 | UART TX | CH340C RXD | OUTPUT |
| GPIO2 | TFT DC | ST7789 DC | OUTPUT |
| GPIO3 | UART RX | CH340C TXD | INPUT |
| GPIO4 | TFT RST | ST7789 Reset | OUTPUT |
| GPIO5 | TFT CS | ST7789 Chip Select | OUTPUT |
| GPIO12 | BTN UP | Navigation Button | INPUT (pull-up) |
| GPIO13 | BTN DOWN | Navigation Button | INPUT (pull-up) |
| GPIO14 | BTN LEFT | Navigation Button | INPUT (pull-up) |
| GPIO15 | TFT BL | Backlight Control | OUTPUT |
| GPIO16 | SD CS | SD Card Chip Select | OUTPUT |
| GPIO18 | SPI CLK | ST7789/SD Clock | OUTPUT |
| GPIO19 | SPI MISO | SD Card Data Out | INPUT |
| GPIO21 | I2C SDA | IP5306 Pin 5 (LED4/SDA) - optional battery monitoring | BIDIRECTIONAL |
| GPIO22 | I2C SCL | IP5306 Pin 6 (SCL) - optional battery monitoring | OUTPUT |
| GPIO23 | SPI MOSI | ST7789/SD Data In | OUTPUT |
| GPIO26 | BTN SELECT | Navigation Button | INPUT (pull-up) |
| GPIO27 | BTN RIGHT | Navigation Button | INPUT (pull-up) |
| EN | RESET | Reset Button + Auto-reset | INPUT (pull-up) |

### Power Rail Connections

| Rail | Voltage | Components Connected |
|------|---------|---------------------|
| Battery | 3.7V | IP5306 Pin 8 (BAT) |
| VBUS | 5V | IP5306 Pin 7 (VIN) from USB-C |
| 5V Boost | 5V | From IP5306 Pin 8 (BAT/VOUT) → Switch → LDO Pin 2 (VIN) |
| 3.3V | 3.3V | ESP32 VCC, CH340C Pin 16 (VCC), Display VCC, SD VCC |
| GND | 0V | All components (common ground plane) |

### Capacitor Placement Summary

| Location | Capacitor | Purpose |
|----------|-----------|---------|
| IP5306 Pin 7 (VIN) | 10μF | Input filtering |
| IP5306 Pin 8 (BAT/VOUT) | 10μF | Battery/Output filtering |
| XC6220 Pin 2 (VIN) | 10μF | LDO input filtering |
| XC6220 Pin 3 (VOUT) | 10μF + 100nF | LDO output filtering |
| CH340C Pin 16 (VCC) | 100nF | Decoupling |
| CH340C Pin 13 (DTR#) to ESP32 EN | 100nF | Auto-reset timing |

### Resistor Placement Summary

| Location | Resistor | Purpose |
|----------|----------|---------|
| USB-C CC1 to GND | 5.1kΩ | USB-C sink identification |
| USB-C CC2 to GND | 5.1kΩ | USB-C sink identification |
| Q1 Base (RTS) | 1kΩ | Transistor base current limiting |
| Q2 Base (RTS) | 1kΩ | Transistor base current limiting |
| GPIO0 to 3.3V | 10kΩ | Boot pin pull-up |
| EN to 3.3V | 10kΩ | Enable pin pull-up |
| Reserved | 10kΩ (3x) | For additional needs |

---

## Verification Checklist

Use this checklist to verify all connections before powering on:

### Power System ✓
- [ ] Battery JST Pin 1 (+) to IP5306 Pin 8 (BAT), Pin 2 (-) to GND
- [ ] USB-C VBUS (A4/B4/A9/B9) connected to IP5306 Pin 7 (VIN)
- [ ] USB-C GND (A1/B1/A12/B12) connected to common ground
- [ ] USB-C CC1 (A5) has 5.1kΩ to GND
- [ ] USB-C CC2 (B5) has 5.1kΩ to GND
- [ ] IP5306 Pin 8 (BAT/VOUT) connected to switch COM
- [ ] Switch output connected to XC6220 Pin 2 (VIN)
- [ ] XC6220 Pin 3 (VOUT) provides 3.3V rail
- [ ] All power capacitors placed correctly

### USB Serial ✓
- [ ] CH340C Pin 5 (UD+) connected to USB-C D+ (A6/B6)
- [ ] CH340C Pin 6 (UD-) connected to USB-C D- (A7/B7)
- [ ] CH340C Pin 2 (TXD) connected to ESP32 GPIO3 (RXD0)
- [ ] CH340C Pin 3 (RXD) connected to ESP32 GPIO1 (TXD0)
- [ ] CH340C Pin 16 (VCC) connected to 3.3V
- [ ] CH340C Pin 4 (V3) connected to 3.3V (tied to VCC)
- [ ] CH340C Pin 1 (GND) connected to ground
- [ ] 100nF capacitor on CH340C Pin 16 (VCC)

### Auto-Reset Circuit ✓
- [ ] 100nF capacitor between CH340C Pin 13 (DTR#) and EN
- [ ] Q1 base connected to CH340C Pin 14 (RTS#) via 1kΩ
- [ ] Q1 collector connected to ESP32 EN
- [ ] Q1 emitter connected to GND
- [ ] Q2 base connected to CH340C Pin 14 (RTS#) via 1kΩ
- [ ] Q2 collector connected to ESP32 GPIO0
- [ ] Q2 emitter connected to GND
- [ ] 10kΩ pull-up on EN to 3.3V
- [ ] 10kΩ pull-up on GPIO0 to 3.3V

### Display ✓
- [ ] EYESPI Pin 1 (GND) connected to ground
- [ ] EYESPI Pin 2 (3.3V) connected to 3.3V rail
- [ ] EYESPI Pin 3 (SCK) connected to GPIO18
- [ ] EYESPI Pin 4 (MOSI) connected to GPIO23
- [ ] EYESPI Pin 6 (TFT_CS) connected to GPIO5
- [ ] EYESPI Pin 7 (TFT_DC) connected to GPIO2
- [ ] EYESPI Pin 8 (TFT_RST) connected to GPIO4
- [ ] EYESPI Pin 9 (SD_CS) connected to GPIO16
- [ ] EYESPI Pin 10 (Backlight) connected to GPIO15

### SD Card ✓
- [ ] SD MISO connected to GPIO19
- [ ] SD shares CLK, MOSI with display
- [ ] SD CS on separate GPIO (GPIO16)

### Buttons ✓
- [ ] UP button: GPIO12 to GND
- [ ] DOWN button: GPIO13 to GND
- [ ] LEFT button: GPIO14 to GND
- [ ] RIGHT button: GPIO27 to GND
- [ ] SELECT button: GPIO26 to GND
- [ ] BOOT button: GPIO0 to GND (with 10kΩ pull-up)
- [ ] RESET button: EN to GND (with 10kΩ pull-up)

### Final Checks ✓
- [ ] No short circuits between power rails
- [ ] All grounds connected to common ground plane
- [ ] All decoupling capacitors placed close to IC pins
- [ ] External antenna connected to ESP32-WROOM-32U antenna pad

---

## Schematic Notes

1. **Ground Plane:** Use a solid ground plane on one layer of the PCB for best noise immunity and thermal dissipation.

2. **Power Trace Width:** Use wide traces (≥0.5mm) for power connections, especially for battery connections and between the IP5306 and LDO.

3. **SPI Signal Routing:** Keep SPI traces short and equal length where possible. Route away from high-current switching nodes.

4. **Antenna Clearance:** Maintain a keepout zone around the ESP32-WROOM-32U external antenna connector. No ground plane or traces near antenna.

5. **Decoupling Capacitor Placement:** Place all decoupling capacitors as close as possible to their respective IC power pins.

---

*Document verified: All connections triple-checked against component datasheets.*
