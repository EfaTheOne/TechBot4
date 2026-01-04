# EasyEDA Guide for TechBot4

This guide explains how to use EasyEDA tools to check the wiring and start the PCB creation for the TechBot4 project.

---

## Table of Contents
1. [Getting Started with EasyEDA](#getting-started-with-easyeda)
2. [Creating a New Project](#creating-a-new-project)
3. [Setting Up the Schematic](#setting-up-the-schematic)
4. [Finding and Adding Components](#finding-and-adding-components)
5. [Wiring the Schematic](#wiring-the-schematic)
6. [Checking the Wiring with ERC](#checking-the-wiring-with-erc)
7. [Converting Schematic to PCB](#converting-schematic-to-pcb)
8. [EasyEDA Pro PCB Editor Deep Dive](#easyeda-pro-pcb-editor-deep-dive)
9. [PCB Layout Best Practices](#pcb-layout-best-practices)
10. [Advanced PCB Techniques for TechBot4](#advanced-pcb-techniques-for-techbot4)
11. [Design Rule Check (DRC)](#design-rule-check-drc)
12. [Generating Manufacturing Files](#generating-manufacturing-files)

---

## Getting Started with EasyEDA

EasyEDA is a free, web-based EDA (Electronic Design Automation) tool for schematic capture, circuit simulation, and PCB design. It integrates well with JLCPCB and LCSC for PCB manufacturing and component sourcing.

### Access EasyEDA

1. Go to [https://easyeda.com/](https://easyeda.com/)
2. Create an account or log in
3. Choose between:
   - **EasyEDA Standard** - Web-based, beginner-friendly
   - **EasyEDA Pro** - Downloadable desktop app with advanced features

For TechBot4, either version works, but EasyEDA Standard is recommended for beginners.

---

## Creating a New Project

1. Click **File** → **New** → **Project**
2. Enter a project name: `TechBot4`
3. Add a description (optional)
4. Click **Create**

Your project will contain:
- Schematic files (.sch)
- PCB files (.pcb)
- Library files (custom components if needed)

---

## Setting Up the Schematic

1. In your project, click **File** → **New** → **Schematic**
2. Name it `TechBot4_Schematic`
3. The schematic editor will open with a blank canvas

### Schematic Editor Overview

- **Left Panel**: Component library, search, and design manager
- **Top Toolbar**: Drawing tools, wires, net labels, power symbols
- **Right Panel**: Component properties and attributes
- **Bottom**: Status bar and console

---

## Finding and Adding Components

EasyEDA has built-in access to LCSC/JLCPCB component libraries. Use the part numbers from the TechBot4 README.md file.

### How to Add Components

1. Click on the **Libraries** icon in the left panel (or press `Shift+F`)
2. Search for the component using:
   - Part name (e.g., `ESP32-WROOM-32U`)
   - LCSC/JLCPCB part number (e.g., `C529579`)
3. Click on the component to preview its schematic symbol and footprint
4. Click **Place** to add it to the schematic

### TechBot4 Component List

| Component | Part Number | LCSC/JLCPCB Part # |
|-----------|-------------|-------------------|
| ESP32-WROOM-32U-N8 | ESP32-WROOM-32U-N8 | C529579 |
| IP5306-I2C | IP5306-I2C | C488349 |
| XC6220B331MR-G | XC6220B331MR-G | C86534 |
| CH340C | CH340C | C84681 |
| USB-C 16PIN | HX TYPE-C 16PIN | C5178539 |
| EYESPI Connector | KH-CL0.5-H2.0-18PIN | C2797195 |
| JST Connector | S2B-PH-K-S(LF)(SN) | C173752 |
| Buttons | YIZHI YZA-056-5.0 | C49108648 |
| Power Switch | C&K PCM12SMTR | C221841 |
| NPN Transistor | S8050 | C266592 |
| 10kΩ Resistor | 0603WAJ0103T5E | C15401 |
| 1kΩ Resistor | 0603WAF1001T5E | C21190 |
| 5.1kΩ Resistor | 0603WAF5101T5E | C23186 |
| 10μF Capacitor | CL21A106KOQNNNE | C1713 |
| 100nF Capacitor | CL10B104KA8NNNC | C1590 |

### Adding Power Symbols

1. Press `P` or click **Wiring Tools** → **Power Flag**
2. Search for:
   - `VCC` or `3.3V` for power connections
   - `GND` for ground connections
3. Place them near component power pins

---

## Wiring the Schematic

### Drawing Wires

1. Press `W` or click **Wire** in the toolbar
2. Click on a component pin to start the wire
3. Click to create corners/bends
4. Click on another pin to complete the connection
5. Press `Escape` to cancel

### Using Net Labels

Net labels connect pins without drawing visible wires (useful for complex schematics).

1. Press `N` or click **Net Label**
2. Enter a name (e.g., `SPI_CLK`, `GPIO18`, `3V3`)
3. Place the label on a wire or pin
4. Any pins with the same net label are electrically connected

### Recommended Net Names for TechBot4

| Net Name | Connected Pins |
|----------|---------------|
| 3V3 | ESP32 3V3, XC6220 VOUT, CH340C VCC, Display VCC |
| GND | All ground pins |
| VBAT | Battery +, IP5306 BAT |
| VBUS | USB-C VBUS, IP5306 VIN |
| 5V_BOOST | IP5306 VOUT, Switch input |
| SPI_CLK | ESP32 GPIO18, Display SCK, SD CLK |
| SPI_MOSI | ESP32 GPIO23, Display MOSI, SD DI |
| SPI_MISO | ESP32 GPIO19, SD DO |
| TFT_CS | ESP32 GPIO5, Display CS |
| TFT_DC | ESP32 GPIO2, Display DC |
| TFT_RST | ESP32 GPIO4, Display RST |
| SD_CS | ESP32 GPIO16, SD CS |
| UART_TX | ESP32 GPIO1, CH340C RXD |
| UART_RX | ESP32 GPIO3, CH340C TXD |

---

## Checking the Wiring with ERC

The Electrical Rule Check (ERC) finds common wiring errors before you create the PCB.

### Running ERC

1. Click **Design** → **Check ERC** (or press `Ctrl+E`)
2. EasyEDA will analyze your schematic for:
   - Unconnected pins
   - Multiple power outputs connected together
   - Input pins not driven
   - Short circuits
3. A report window will show errors and warnings

### Common ERC Errors and Fixes

| Error | Cause | Solution |
|-------|-------|----------|
| **Pin not connected** | A required pin has no connection | Add wire or net label, or mark pin as "No Connect" |
| **Power pin not driven** | VCC/GND symbol not connected properly | Ensure power symbols are on the power net |
| **Output pins connected together** | Two outputs driving the same net | Review schematic, separate nets if needed |
| **Floating input pin** | Input has no source | Add pull-up/pull-down resistor or connect to a driver |

### Marking Pins as No Connect

Some IC pins are unused (NC). To avoid ERC warnings:
1. Right-click the pin
2. Select **No Connect Flag**
3. A small "X" will appear indicating intentional no-connect

---

## Converting Schematic to PCB

Once your schematic is complete and ERC-clean:

1. Click **Design** → **Convert to PCB** (or press `Alt+P`)
2. EasyEDA will create a new PCB document
3. All components will be placed outside the board outline
4. Connections will be shown as "ratsnest" lines (air wires)

### Setting Board Size

1. Click on the board outline layer (**BoardOutLine**)
2. Draw a rectangle or custom shape for your PCB
3. For TechBot4, a compact size like **70mm x 50mm** is recommended (see README.md for pocket-sized design goal)

---

## EasyEDA Pro PCB Editor Deep Dive

EasyEDA Pro offers advanced PCB design features that help you create a professional-quality board. This section covers Pro-specific tools and workflows.

### EasyEDA Pro Interface Overview

When you open the PCB editor in EasyEDA Pro:

| Panel | Location | Purpose |
|-------|----------|---------|
| **Layer Manager** | Left side | Toggle layer visibility, set active layer |
| **Design Manager** | Left side | View nets, components, DRC errors |
| **Properties Panel** | Right side | Edit selected object properties |
| **Toolbar** | Top | Drawing tools, routing, copper pour |
| **Canvas** | Center | PCB design area |
| **Bottom Bar** | Bottom | Grid settings, units, zoom |

### Layer Stack Configuration

For a 2-layer TechBot4 PCB:

1. Click **Setup** → **Layer Stack Manager**
2. Configure the layer stack:

| Layer | Name | Thickness | Purpose |
|-------|------|-----------|---------|
| Top | Top Copper | 35μm (1oz) | Signal traces, component pads |
| Bottom | Bottom Copper | 35μm (1oz) | Ground plane, additional routing |

**Note**: The FR4 substrate (1.6mm standard) is between the copper layers but is not configured as a separate layer in EasyEDA.

3. Click **Apply** to save settings

### Grid and Snap Settings

Proper grid settings are essential for precise component placement:

1. Click **Setup** → **Grid Settings** (or press `G`)
2. Recommended settings for TechBot4:

| Setting | Value | Purpose |
|---------|-------|---------|
| **Grid Size** | 0.1mm (100mil) | General placement |
| **Fine Grid** | 0.025mm (25mil) | Precise alignment |
| **Snap to Grid** | Enabled | Clean component placement |
| **Snap to Pad** | Enabled | Accurate trace routing |

3. Toggle between grids with `G` key during design

### Component Placement in EasyEDA Pro

#### Step 1: Import Components
After converting from schematic, all components appear in a cluster. To organize:

1. Press `M` to enter **Move** mode
2. Select components and drag to approximate positions
3. Press `R` to rotate selected component (90° increments)
4. Press `Shift+R` for custom rotation angles

#### Step 2: Alignment Tools (Pro Feature)

EasyEDA Pro has powerful alignment tools:

1. Select multiple components (Ctrl+Click)
2. Right-click → **Align**:
   - **Align Left/Right/Top/Bottom**: Align edges
   - **Distribute Horizontally/Vertically**: Equal spacing
   - **Align Centers**: Center alignment

#### Step 3: TechBot4 Component Layout Strategy

Place components in this order for optimal routing:

```
┌──────────────────────────────────────────────────┐
│  [USB-C]  [CH340C]  [BOOT] [RST]                 │
│                                                   │
│  [IP5306]  [Switch]  [XC6220 LDO]                │
│                                                   │
│  ┌─────────────────────────────┐                 │
│  │       ESP32-WROOM-32U       │    [Buttons]    │
│  │                             │    [UP]         │
│  │                             │ [LT][SEL][RT]   │
│  │         (Keep antenna       │    [DN]         │
│  │          area clear)        │                 │
│  └─────────────────────────────┘                 │
│                                                   │
│  [JST Battery]        [EYESPI Display Connector] │
└──────────────────────────────────────────────────┘
```

### Routing in EasyEDA Pro

#### Interactive Router Settings

1. Click **Route** → **Interactive Route** (or press `W`)
2. Configure routing options in the Properties panel:

| Setting | Recommended Value | Notes |
|---------|-------------------|-------|
| **Track Width** | 0.25mm default | Can change per-trace |
| **Via Size** | 0.6mm outer / 0.3mm drill | JLCPCB compatible |
| **Clearance** | 0.2mm | Space between traces |
| **Corner Style** | 45° (mitered) | Better signal integrity |

#### Track Width Classes

Set up different track widths for different signal types:

1. Click **Setup** → **Design Rules** → **Net Classes**
2. Create these net classes:

| Net Class | Track Width | Via Size | Nets |
|-----------|-------------|----------|------|
| **Power** | 0.5mm | 0.8mm/0.4mm | 3V3, VBAT, 5V_BOOST, GND |
| **Signal** | 0.25mm | 0.6mm/0.3mm | GPIO signals, SPI, I2C |
| **USB** | 0.3mm | 0.6mm/0.3mm | D+, D- (matched pair) |

3. Assign nets to classes in the Design Manager

#### Routing Shortcuts in Pro

| Shortcut | Action |
|----------|--------|
| `W` | Start routing |
| `V` | Place via while routing |
| `Shift+W` | Toggle routing layer |
| `Backspace` | Delete last segment |
| `Esc` | Cancel routing |
| `1` / `2` | Switch to Top/Bottom layer |
| `+` / `-` | Increase/decrease track width |

### Copper Pour (Ground Plane) in Pro

#### Creating a Solid Ground Plane

1. Select the **Bottom Layer** (`2` key)
2. Click **Place** → **Copper Area** (or press `Shift+P`)
3. Configure in Properties:
   - **Net**: GND
   - **Clearance**: 0.3mm
   - **Thermal Relief**: Spoke width 0.25mm, 4 spokes
4. Draw a rectangle covering the entire board
5. Press `Shift+B` to rebuild copper pours

#### Ground Plane Best Practices

- **Thermal Relief**: Enables easier soldering of through-hole GND connections
- **Spoke Count**: 4 spokes is standard; use 2 for better thermal dissipation
- **Anti-Pad Size**: Set to 0.3-0.5mm larger than via/pad diameter

### Via Stitching for Ground Plane

Connect top and bottom ground areas with vias:

1. Click **Place** → **Via Array** (Pro feature)
2. Configure:
   - **Via Size**: 0.6mm outer / 0.3mm drill
   - **Spacing**: 3-5mm apart
   - **Net**: GND
3. Place via arrays around:
   - Board edges
   - Near high-current components (IP5306, LDO)
   - Around the ESP32 module

### ESP32 Antenna Keepout Zone

The ESP32-WROOM-32U has an onboard antenna that requires a clearance zone:

1. Select **Top Layer**
2. Click **Place** → **Keepout Area**
3. Draw a rectangle extending **15mm beyond the ESP32 antenna end**
4. In Properties:
   - Enable: **No Copper**, **No Via**, **No Track**
5. Repeat on **Bottom Layer**

**Critical**: No copper (traces, ground plane, or pours) should be under or near the antenna area.

### Teardrops (Pro Feature)

Teardrops strengthen pad-to-trace connections:

1. Click **Tools** → **Add Teardrops**
2. Configure:
   - **Pad Teardrops**: Enabled
   - **Via Teardrops**: Enabled
   - **Size**: 100% (default)
3. Click **Apply All**

### Length Matching (USB Differential Pair)

For the USB D+/D- signals:

1. Route D+ and D- traces parallel, with **0.15mm** spacing
2. Click **Route** → **Differential Pair Router**
3. Select the D+/D- net pair
4. Route together to maintain matching length
5. After routing, check length in **Design Manager** → **Nets**
6. Target: Both traces within **±0.1mm** of each other for proper USB signal integrity

---

## Advanced PCB Techniques for TechBot4

### Power Integrity

#### Decoupling Capacitor Placement

| Component | Capacitor | Placement |
|-----------|-----------|-----------|
| ESP32 3V3 Pin | 100nF | Within 2mm of pin |
| XC6220 VOUT | 10μF + 100nF | Within 3mm of output pin |
| XC6220 VIN | 10μF | Within 3mm of input pin |
| IP5306 VOUT | 10μF | Within 3mm of pin 8 |
| IP5306 BAT | 10μF | Within 3mm of pin 6 |
| CH340C VCC | 100nF | Within 2mm of pin 13 |

#### Power Trace Star Topology

Route power from the LDO output in a star pattern:

```
                    ┌─── ESP32 3V3
                    │
XC6220 VOUT ────────┼─── CH340C VCC
                    │
                    ├─── Display VCC
                    │
                    └─── Decoupling Caps
```

This prevents voltage drops from affecting sensitive components.

### Signal Integrity

#### SPI Bus Routing

1. Keep SPI traces **short** (< 50mm total length)
2. Route SPI_CLK, SPI_MOSI, SPI_MISO as a group
3. Add **100nF capacitors** near display/SD card SPI connections
4. Avoid running SPI traces near power traces or switching nodes

#### USB Signal Routing

1. Route D+ and D- as **differential pair** (parallel, matched length)
2. Target **90Ω differential impedance** - use EasyEDA Pro's built-in impedance calculator (**Setup** → **Impedance Calculator**) to determine exact trace width and gap for your stackup
3. Keep USB traces away from high-frequency signals
4. Add ESD protection if desired (TVS diodes on D+/D-)

### Silkscreen and Assembly Markings

#### Component Labels

1. Select **Top Silkscreen Layer**
2. Ensure all component designators (R1, C1, U1) are visible
3. Move labels outside component footprints for readability
4. Minimum text height: **0.8mm** for JLCPCB

#### Add These Markings

| Marking | Location | Purpose |
|---------|----------|---------|
| **TechBot4** | Center/Corner | Project name |
| **V1.0** | Near project name | Version number |
| **+ / -** | Near JST connector | Battery polarity |
| **5V / 3V3 / GND** | Near test points | Power rail labels |
| **Pin 1 dot** | Near IC corner | Orientation marker |

### Mounting Holes

If adding mounting holes for the 3D printed case:

1. Click **Place** → **Pad** → **Mounting Hole**
2. Configure:
   - **Hole Size**: 3.2mm (for M3 screws)
   - **Pad Size**: 6mm (optional copper ring)
   - **Net**: Connect to GND for shielding or leave unconnected
3. Place in corners, at least **3mm from board edge**

---

## PCB Layout Best Practices

### Component Placement

1. **Place power components first**: Battery connector, IP5306, XC6220 LDO
2. **Place main IC next**: ESP32-WROOM-32U
3. **Place peripheral components**: USB-C, CH340C, buttons, display connector
4. **Keep related components close**: SPI bus components together, power components together

### Routing Guidelines

| Signal Type | Trace Width | Notes |
|-------------|-------------|-------|
| Power (VCC, GND) | 0.5mm - 1.0mm | Wider traces for lower resistance |
| High-speed signals (SPI, USB) | 0.2mm - 0.3mm | Keep traces short and parallel |
| GPIO signals | 0.2mm - 0.25mm | Standard width for low-current signals |
| Antenna keepout | N/A | No traces or copper near ESP32 antenna |

### Ground Plane

1. Add a ground plane on the bottom layer:
   - Click **Tools** → **Copper Area**
   - Select **GND** net
   - Draw a rectangle covering the entire board
2. Ground planes provide:
   - Low-impedance return path
   - EMI shielding
   - Heat dissipation

### Power Trace Routing

1. Route power traces on the top layer
2. Use wider traces (0.5mm+) for:
   - Battery to IP5306
   - IP5306 output to switch
   - Switch to LDO
   - LDO output to ESP32 and peripherals

### Decoupling Capacitor Placement

Place decoupling capacitors **as close as possible** to their associated IC power pins:
- 100nF capacitors: Within 3mm of VCC pins
- 10μF capacitors: Within 5mm of power input/output pins

---

## Design Rule Check (DRC)

Before ordering your PCB, run a Design Rule Check.

### Running DRC

1. Click **Design** → **Check DRC** (or press `Ctrl+D`)
2. EasyEDA checks for:
   - Trace-to-trace clearance violations
   - Trace-to-pad clearance violations
   - Minimum trace width violations
   - Drill hole size issues
   - Unconnected nets

### JLCPCB Manufacturing Rules

Set these DRC rules for JLCPCB manufacturing:

| Rule | Minimum Value |
|------|---------------|
| Trace Width | 0.127mm (5 mil) |
| Trace Spacing | 0.127mm (5 mil) |
| Via Diameter | 0.45mm |
| Via Drill | 0.25mm |
| Pad-to-Pad Spacing | 0.127mm |
| Board Edge Clearance | 0.2mm |

To set DRC rules:
1. Click **Design** → **Design Rule**
2. Enter the values above
3. Click **OK**
4. Run DRC again to verify

---

## Generating Manufacturing Files

### Gerber Files

Gerber files are the industry-standard format for PCB fabrication.

1. Click **Fabrication** → **PCB Fabrication File (Gerber)**
2. Review the layers included:
   - Top Copper (GTL)
   - Bottom Copper (GBL)
   - Top Silkscreen (GTO)
   - Bottom Silkscreen (GBO)
   - Top Soldermask (GTS)
   - Bottom Soldermask (GBS)
   - Drill File (DRL/XLN)
   - Board Outline (GKO)
3. Click **Generate Gerber**
4. Download the ZIP file

### BOM and Pick-and-Place Files (for PCBA)

If you want JLCPCB to assemble your board:

1. Click **Fabrication** → **BOM**
   - Review all components and LCSC part numbers
   - Export as CSV
2. Click **Fabrication** → **Pick and Place File**
   - Export component positions for assembly
3. Upload both files to JLCPCB during ordering

### Ordering from JLCPCB

1. Go to [https://jlcpcb.com/](https://jlcpcb.com/)
2. Click **Order Now** → **Add Gerber File**
3. Upload your Gerber ZIP file
4. Configure options:
   - PCB Qty: 5 (minimum)
   - Layers: 2
   - PCB Color: Your choice (green is cheapest)
   - Surface Finish: HASL or LeadFree HASL
5. For PCBA (assembly):
   - Enable **SMT Assembly**
   - Upload BOM and Pick-and-Place files
   - Review component placement
6. Complete checkout and wait for your boards!

---

## Troubleshooting Common Issues

### Component Not Found

If a component isn't in the library:
1. Search by manufacturer part number
2. Search by LCSC number without the "C" prefix
3. Create a custom component:
   - **File** → **New** → **Symbol/Footprint**

### Schematic and PCB Out of Sync

If you modify the schematic after creating the PCB:
1. Go to the PCB editor
2. Click **Design** → **Update PCB from Schematic**
3. Review changes and click **Apply**

### Ratsnest Lines Remaining

Ratsnest (airwire) lines show unrouted connections:
1. Press `Shift+X` to highlight unrouted nets
2. Route remaining traces manually
3. Use the **Auto Router** sparingly (manual routing is usually better)

---

## Additional Resources

- [EasyEDA Official Tutorial](https://docs.easyeda.com/en/Introduction/Introduction-to-EasyEDA/index.html)
- [JLCPCB Design Guidelines](https://jlcpcb.com/capabilities/Capabilities)
- [LCSC Component Database](https://lcsc.com/)
- [ESP32-WROOM-32U Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32u_datasheet_en.pdf)

---

*This guide is part of the TechBot4 documentation. Refer to WIRING.md for complete connection details.*
