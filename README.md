# TechBot4

## Part List - Verified Components

> **Note:** All PCBA numbers can be searched on JLCPCB/LCSC using the format: `https://jlcpcb.com/partdetail/[manufacturer-part]/[PCBA_NUMBER]` or search directly at [JLCPCB Parts Library](https://jlcpcb.com/parts) or [LCSC Electronics](https://www.lcsc.com/search?q=[PCBA_NUMBER])

---

### Main Components

#### Display
- **Adafruit 2.0" IPS Display (320x240)** - Product #4311
  - 🔗 [Adafruit Product Page](https://www.adafruit.com/product/4311)
  - EYESPI connector, ST7789 driver, 40-pin FPC (0.5mm pitch)

#### Microcontroller
- **ESP32-WROOM-32-N8** | PCBA Number: **C529582** | Qty: 1x
  - 🔗 [JLCPCB Search](https://jlcpcb.com/partdetail/EspressifSystems-ESP32_WROOM_32N8/C529582) | [LCSC Search](https://www.lcsc.com/search?q=C529582)
  - 8MB Flash, WiFi + Bluetooth, 38-pin module

---

### Power Management Components

#### Power Management IC
- **IP5306** (SOP-8 Package) | PCBA Number: **C96641** | Qty: 1x
  - 🔗 [JLCPCB Search](https://jlcpcb.com/partdetail/InjoinicTech-IP5306/C96641) | [LCSC Search](https://www.lcsc.com/search?q=C96641)
  - Integrated Battery Charger & 5V Boost Converter (2.1A output)
  - **Note:** This is a fully integrated power bank SoC with internal switching inductor. No external inductor required for standard operation.

#### Voltage Regulator
- **AMS1117-3.3** (SOT-223) | PCBA Number: **C6186** | Qty: 1x
  - 🔗 [JLCPCB Search](https://jlcpcb.com/partdetail/AdvancedMonolithicSystems-AMS1117_33/C6186) | [LCSC Search](https://www.lcsc.com/search?q=C6186)
  - 3.3V Linear Regulator, 1A output, steps down 5V to 3.3V for ESP32

---

### Passive Components

#### Capacitors

| Component | Value | Package | PCBA Number | Qty | Purpose | Search Links |
|-----------|-------|---------|-------------|-----|---------|--------------|
| Capacitor | 22µF | 0603, X5R, 10V | **C96446** | 2x | IP5306 Input/Output Filtering | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C96446) \| [LCSC](https://www.lcsc.com/search?q=C96446) |
| Capacitor | 10µF | 0603, X5R, 16V | **C19702** | 3x | AMS1117 In/Out, ESP32 Power | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C19702) \| [LCSC](https://www.lcsc.com/search?q=C19702) |
| Capacitor | 0.1µF | 0603, X7R, 50V | **C14663** | 1x | ESP32 High-Frequency Decoupling | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C14663) \| [LCSC](https://www.lcsc.com/search?q=C14663) |

#### Resistors

| Component | Value | Package | PCBA Number | Qty | Purpose | Search Links |
|-----------|-------|---------|-------------|-----|---------|--------------|
| Resistor | 5.1kΩ | 0603, 1% | **C23178** | 2x | USB-C CC Pin Pull-downs (Required for C-to-C charging) | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C23178) \| [LCSC](https://www.lcsc.com/search?q=C23178) |
| Resistor | 10kΩ | 0603, 1% | **C23177** | 7x | 5x Button Pull-downs + 1x GPIO0 Pull-up + 1x EN Pull-up | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C23177) \| [LCSC](https://www.lcsc.com/search?q=C23177) |

---

### Connectors & Switches

| Component | Description | Package | PCBA Number | Qty | Purpose | Search Links |
|-----------|-------------|---------|-------------|-----|---------|--------------|
| USB-C Port | 16-Pin SMD | Surface Mount | **C165948** | 1x | Charging Input (Korean Hroparts TYPE-C-31-M-12) | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C165948) \| [LCSC](https://www.lcsc.com/search?q=C165948) |
| JST-PH Connector | 2-Pin Vertical SMD | S2B-PH-SM4-TB | **C396123** | 1x | Battery Connector (3.7V LiPo) | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C396123) \| [LCSC](https://www.lcsc.com/search?q=C396123) |
| Tactile Switch | 6x6mm | Through-Hole | **C34260** | 6x | 5x Navigation + 1x Reset Button | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C34260) \| [LCSC](https://www.lcsc.com/search?q=C34260) |
| FPC Connector | 40-Pin, 0.5mm Pitch | Bottom Contact SMD | **C55234** | 1x | Adafruit EYESPI Display Connection | [JLCPCB](https://jlcpcb.com/parts/componentSearch?searchTxt=C55234) \| [LCSC](https://www.lcsc.com/search?q=C55234) |

---

### ⚠️ Important Notes on Component Selection

1. **IP5306 Package Correction:** The IP5306 uses a **SOP-8** package (not ESOP-8). Verify the package matches your PCB footprint.

2. **Inductor Removed:** The original design included an inductor (C116556) for the IP5306. However, the IP5306 is a **fully integrated power bank SoC** with an internal switching inductor. External inductors are NOT required for standard operation. If you have a different variant requiring external components, consult the specific datasheet.

3. **Resistor Count Updated:** Changed from 6x to 7x 10kΩ resistors. You need:
   - 5x for button pull-downs (UP, DOWN, LEFT, RIGHT, SELECT)
   - 1x for GPIO 0 pull-up (boot mode)
   - 1x for EN pin pull-up (reset circuit)

4. **FPC Connector Verification:** The 40-pin FPC connector (C55234) must match the Adafruit display's FPC cable pinout exactly. Verify pin 1 orientation before ordering.

---


## What is TechBot4?

The TechBot4 is an ESP32-WROOM-32-N8 based pen testing tool inspired by the ESP32 Marauder by JustCallMeKoko. It performs similar WiFi and Bluetooth security testing functions in a custom, pocket-sized form factor.

### Key Features:
- **Display:** 2.0 inch 320x240 IPS display (Adafruit #4311) with EYESPI connector and wide viewing angles
- **Microcontroller:** ESP32-WROOM-32-N8 with 8MB Flash, WiFi + Bluetooth capability
- **Power:** 3.7V LiPo battery (1500mAh) with IP5306 power management for charging and 5V boost
- **Navigation:** 5 buttons for navigation (UP, DOWN, LEFT, RIGHT, SELECT) + 1 RESET button
- **Enclosure:** Designed for 3D printing with PETG filament for durability

### Power Switch Recommendation:

For the power switch, the recommended approach is to use the **IP5306's KEY function**:
- The IP5306 has a built-in power management system with a KEY pin
- Double-pressing the KEY button turns the device on
- Long-pressing the KEY button turns the device off
- This approach provides proper soft power control without voltage spikes or constant battery drain
- Alternatively, you can add a slide switch between BAT+ and IP5306 BAT+ input with a small RC filter (10Ω + 100µF) to reduce inrush current

---

## Purpose

I am an avid learner in the IT world and want to know how to use tools to help secure networks and privacy now that AI has such a big influence. The TechBot4 is such a cool project that I have been excited about and is the fourth version of the TechBot series.

---

## Quick Reference Links

- 📋 **Wiring Guide:** [WIRING.md](./WIRING.md) - Complete pin-by-pin wiring instructions
- 🛠️ **ESP32 Marauder Firmware:** [GitHub - JustCallMeKoko](https://github.com/justcallmekoko/ESP32Marauder)
- 📄 **ESP32 Datasheet:** [Espressif Official Documentation](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)
- 🖥️ **Display Product Page:** [Adafruit #4311](https://www.adafruit.com/product/4311)
- 🔧 **JLCPCB Parts Library:** [JLCPCB Parts](https://jlcpcb.com/parts) - Search by PCBA number
- 🔧 **LCSC Electronics:** [LCSC](https://www.lcsc.com/) - Alternative parts search


