# Bill of Materials (BOM) - TechBot4 ESP32 Marauder

## Overview
This BOM lists all components required to build one TechBot4 ESP32 Marauder device.

## Quick Summary
- **Total Components**: ~50 items
- **Estimated Cost**: $25-35 USD (excluding PCB)
- **PCB Cost**: $2-10 USD (depending on quantity and manufacturer)
- **Assembly Difficulty**: Intermediate (SMD soldering required)

---

## Main Components

| Ref | Qty | Value | Description | Package | Supplier | Part Number | Est. Price |
|-----|-----|-------|-------------|---------|----------|-------------|------------|
| U3 | 1 | ESP32-WROOM-32 | WiFi+BT MCU Module | SMD Module | AliExpress/Mouser | ESP32-WROOM-32D | $3.50 |
| U1 | 1 | TP4056 | LiPo Battery Charger IC | SOT23-6 | AliExpress/LCSC | TP4056 | $0.15 |
| U2 | 1 | AMS1117-3.3 | 3.3V LDO Regulator | SOT-223 | AliExpress/LCSC | AMS1117-3.3 | $0.20 |
| U4 | 1 | CP2102 | USB to UART Bridge | QFN-28 | AliExpress/LCSC | CP2102-GMR | $1.50 |
| D1 | 1 | SSD1306 OLED | 0.96" 128x64 Display | I2C Module | AliExpress/Amazon | SSD1306 | $3.00 |

**Main Components Subtotal**: ~$8.35

---

## Passive Components - Resistors (0805 SMD)

| Ref | Qty | Value | Description | Package | Tolerance | Power | Est. Price |
|-----|-----|-------|-------------|---------|-----------|-------|------------|
| R1, R2 | 2 | 4.7kΩ | I2C Pull-up | 0805 | 5% | 1/8W | $0.02 |
| R3 | 1 | 330Ω | LED Current Limit | 0805 | 5% | 1/8W | $0.01 |
| R4, R5 | 2 | 1kΩ | LED Current Limit | 0805 | 5% | 1/8W | $0.02 |
| R6 | 1 | 1kΩ | Transistor Base | 0805 | 5% | 1/8W | $0.01 |
| R7-R14 | 8 | 10kΩ | Pull-up Resistors | 0805 | 5% | 1/8W | $0.08 |
| R15 | 1 | 1.2kΩ | Charge Current | 0805 | 5% | 1/8W | $0.01 |
| R16, R17 | 2 | 27Ω | USB Series | 0805 | 5% | 1/8W | $0.02 |

**Resistors Subtotal**: ~$0.17 (or buy resistor kit for $5-10)

---

## Passive Components - Capacitors

| Ref | Qty | Value | Type | Voltage | Package | Est. Price |
|-----|-----|-------|------|---------|---------|------------|
| C1, C2 | 2 | 10µF | Ceramic | 16V | 0805 | $0.04 |
| C3, C4 | 2 | 22µF | Electrolytic | 16V | 6.3x5.4mm | $0.10 |
| C5-C7, C9 | 4 | 100nF (0.1µF) | Ceramic | 50V | 0805 | $0.04 |
| C8 | 1 | 4.7µF | Ceramic | 16V | 0805 | $0.02 |
| C10, C11 | 2 | 10µF | Electrolytic | 16V | 5x5mm | $0.10 |

**Capacitors Subtotal**: ~$0.30 (or buy capacitor kit for $5-10)

---

## Semiconductors

| Ref | Qty | Value | Description | Package | Est. Price |
|-----|-----|-------|-------------|---------|------------|
| LED1 | 1 | Red LED | Status Indicator | 0805 SMD | $0.02 |
| LED2 | 1 | Yellow LED | Standby Indicator | 0805 SMD | $0.02 |
| LED3 | 1 | Red LED | Charging Indicator | 0805 SMD | $0.02 |
| Q1 | 1 | 2N3904 | NPN Transistor | SOT-23 | $0.05 |
| D1 | 1 | 1N4148 | Switching Diode | SOD-123 | $0.02 |

**Semiconductors Subtotal**: ~$0.13

---

## Connectors and Mechanical

| Ref | Qty | Value | Description | Type | Est. Price |
|-----|-----|-------|-------------|------|------------|
| J1 | 1 | USB-C | USB Type-C Connector | SMD/THT | $0.50 |
| BAT1 | 1 | JST-PH-2 | Battery Connector | 2.0mm pitch | $0.15 |
| SW1 | 1 | RESET | Tactile Switch 6x6mm | THT | $0.10 |
| SW2-SW4, SW6 | 4 | Buttons | Tactile Switch 6x6mm | THT | $0.40 |
| SW5 | 1 | Power | Slide Switch SS12D00 | THT | $0.15 |
| BZ1 | 1 | Buzzer | Passive Buzzer 5V 12mm | THT | $0.30 |

**Connectors/Mechanical Subtotal**: ~$1.60

---

## Optional Components

| Ref | Qty | Value | Description | Purpose | Est. Price |
|-----|-----|-------|-------------|---------|------------|
| ANT1 | 1 | 2.4GHz | External WiFi Antenna | Better range | $2.00 |
| J2 | 1 | U.FL | Antenna Connector | For external antenna | $0.30 |
| Headers | 1 | Female | Display Socket Headers | Easy replacement | $0.20 |

**Optional Components Subtotal**: ~$2.50

---

## Battery

| Ref | Qty | Value | Description | Specs | Est. Price |
|-----|-----|-------|-------------|-------|------------|
| BAT1 | 1 | LiPo Battery | 3.7V Lithium Polymer | 1000-2000mAh, JST-PH connector | $5.00 |

**Recommended**: 3.7V 1500mAh LiPo with built-in protection circuit

---

## PCB

| Item | Qty | Description | Specifications | Est. Price |
|------|-----|-------------|----------------|------------|
| PCB | 1 | Custom PCB | 80x150mm, 2-layer, black solder mask | $2-10 |

**Note**: Price varies significantly with quantity
- 5 pieces: ~$10 total ($2 each)
- 10 pieces: ~$15 total ($1.50 each)

**Recommended Manufacturers**:
- JLCPCB (China) - Fast, cheap, good quality
- PCBWay (China) - Good quality, assembly service available
- OSH Park (USA) - Higher quality, slower, more expensive

---

## Tools and Supplies (Not Included)

| Item | Description | Est. Price |
|------|-------------|------------|
| Soldering Iron | Temperature controlled, 350-400°C | $15-50 |
| Solder | Lead-free or 60/40 tin-lead, 0.8mm | $5-10 |
| Flux Pen | For SMD soldering | $3-5 |
| Tweezers | Precision tweezers for SMD | $3-8 |
| Multimeter | For testing and debugging | $10-30 |
| USB Cable | USB-A to USB-C | $3-5 |

---

## Component Kits (Alternative to Individual Parts)

Instead of buying individual resistors and capacitors, consider these kits:

| Kit | Description | Supplier | Est. Price |
|-----|-------------|----------|------------|
| SMD Resistor Kit | 0805 package, common values | AliExpress/Amazon | $8-15 |
| SMD Capacitor Kit | 0805 ceramic, common values | AliExpress/Amazon | $8-15 |
| Electrolytic Cap Kit | Through-hole, various sizes | AliExpress/Amazon | $5-10 |
| Tactile Switch Kit | 6x6mm buttons, 100pcs | AliExpress/Amazon | $3-5 |

---

## Sourcing Guide

### Recommended Suppliers

**For Complete Kits (Easy):**
1. **AliExpress** - Cheapest, 2-4 week shipping
   - Search: "ESP32 development board kit"
   - Buy pre-assembled modules when possible

2. **Amazon** - Fast shipping (2 days), higher price
   - Good for batteries, displays, basic components

**For Individual Components (Advanced):**
1. **LCSC / JLCPCB** - Great prices, integrated with PCB orders
2. **Mouser / Digikey** - Reliable, fast, but more expensive
3. **Newark / Farnell** - Professional grade

**For PCB:**
1. **JLCPCB** - $2 for 5 PCBs (recommended for beginners)
2. **PCBWay** - Good quality, offers assembly service
3. **OSH Park** - USA-based, great for prototypes

---

## Assembly Order and Notes

### SMD Components (Solder First)
1. Start with smallest components (resistors, capacitors)
2. Then ICs (U1, U2, U4)
3. Then ESP32 module (U3)
4. Finally LEDs and diode

### Through-Hole Components (Solder Last)
1. USB connector
2. Battery connector
3. Tactile switches
4. Power switch
5. Buzzer
6. Display (use socket headers for easy replacement)

### Tips:
- Use solder paste and hot air for SMD components (easier than iron)
- Apply flux liberally when soldering SMD
- Test power rails before inserting ESP32
- Use a magnifying glass or microscope for inspection
- Double-check component polarity (LEDs, diode, ICs)

---

## Cost Breakdown Summary

| Category | Estimated Cost |
|----------|----------------|
| Main ICs | $8.35 |
| Passive Components | $0.47 |
| LEDs/Transistors | $0.13 |
| Connectors/Switches | $1.60 |
| Battery | $5.00 |
| PCB (5 pcs) | $2.00 |
| **Total per Unit** | **~$17.55** |
| Optional (antenna, etc.) | +$2.50 |
| Tools (if needed) | +$30-100 |

**Note**: Prices are estimates and vary by supplier, quantity, and location. Buying in bulk or kits can significantly reduce costs.

---

## Pre-Made Alternative

If you don't want to build the PCB, you can use:
- ESP32 DevKit + breadboard + components (~$10-15)
- Follow the firmware and wiring diagram
- Less compact but fully functional

---

## Purchasing Links (Examples)

**AliExpress Search Terms:**
- "ESP32-WROOM-32"
- "TP4056 module"
- "0.96 OLED SSD1306"
- "3.7V LiPo battery 1500mAh"
- "SMD resistor capacitor kit 0805"

**Amazon Search Terms:**
- "ESP32 development board"
- "LiPo battery charger module"
- "OLED display I2C"
- "Tactile switch kit"

---

## Next Steps

After gathering components:
1. Order PCB from manufacturer (see `/docs/PCB_Fabrication_Guide.md`)
2. Wait for PCB and components to arrive (2-4 weeks)
3. Follow assembly guide (see `/docs/Assembly_Guide.md`)
4. Flash firmware (see `/docs/Firmware_Guide.md`)
5. Test and enjoy!

---

**Document Version**: 1.0  
**Last Updated**: 2025-01-01  
**Project**: TechBot4 ESP32 Marauder
