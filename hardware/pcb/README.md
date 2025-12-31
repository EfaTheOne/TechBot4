# TechBot4 ESP32 Marauder - PCB Design Files

This directory contains the PCB design files for the TechBot4 ESP32 Marauder pen testing device.

## Design Overview

The PCB is designed to be compact and phone-like in form factor, with:
- ESP32-WROOM-32 module as the main processor
- 128x64 OLED display (I2C)
- 4 tactile buttons for navigation
- USB-C connector for programming and power
- LiPo battery charging circuit
- Status LED and buzzer
- Antenna connector for improved WiFi/BT range

## PCB Specifications

- **Dimensions**: 80mm x 150mm (phone-like form factor)
- **Layers**: 2-layer PCB
- **Board Thickness**: 1.6mm
- **Copper Weight**: 1 oz
- **Surface Finish**: HASL or ENIG
- **Solder Mask**: Black (for aesthetic appeal)
- **Silkscreen**: White

## Main Components

1. **ESP32-WROOM-32** - Main microcontroller module
2. **TP4056** - LiPo battery charging IC
3. **AMS1117-3.3** - 3.3V voltage regulator
4. **SSD1306** - 128x64 OLED display controller
5. **CP2102** - USB to UART bridge
6. **Tactile Switches** - Navigation buttons
7. **3.7V LiPo Battery** - Power source (1000-2000mAh)

## Design Files

- `schematic.txt` - Component connections and circuit design
- `pcb_layout.txt` - Board layout specifications
- `gerber/` - Gerber files for manufacturing (when generated)

## Design Software

The design can be implemented in:
- **KiCad** (Recommended, free and open-source)
- **EasyEDA** (Browser-based, beginner-friendly)
- **Eagle/Fusion 360**
- **Altium Designer**

## Next Steps

See the `/docs` folder for:
- Complete Bill of Materials (BOM)
- PCB fabrication guide
- Assembly instructions
