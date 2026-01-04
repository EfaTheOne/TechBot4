# TechBot4 PCB Design Guide for EasyEDA Pro

This guide focuses exclusively on PCB layout and design in EasyEDA Pro for the TechBot4 ESP32 pen testing tool. It covers 4-layer PCB design with dedicated ground and power planes.

---

## Table of Contents
1. [PCB Layer Stack Setup](#pcb-layer-stack-setup)
2. [Board Setup and Design Rules](#board-setup-and-design-rules)
3. [Component Placement Strategy](#component-placement-strategy)
4. [Ground Plane Configuration](#ground-plane-configuration)
5. [3V3 Power Plane Configuration](#3v3-power-plane-configuration)
6. [Signal Routing](#signal-routing)
7. [Via Strategy](#via-strategy)
8. [Design Rule Check and Manufacturing](#design-rule-check-and-manufacturing)

---

## PCB Layer Stack Setup

### Why 4-Layer for TechBot4

A 4-layer PCB provides significant advantages for the TechBot4:
- **Dedicated ground plane**: Solid return path for all signals
- **Dedicated power plane**: Clean 3.3V distribution to ESP32 and peripherals
- **Reduced EMI**: Ground plane shields digital noise
- **Shorter traces**: Components connect directly to power/ground through vias

### Configuring the 4-Layer Stack in EasyEDA Pro

1. Open your PCB in EasyEDA Pro
2. Click **Setup** → **Layer Stack Manager**
3. Click **Add Layer** to create a 4-layer stackup
4. Configure layers as follows:

| Layer | Name | Type | Thickness | Purpose |
|-------|------|------|-----------|---------|
| L1 | Top | Signal | 35μm (1oz) | Component side, signal routing |
| L2 | Inner1 | Plane | 35μm (1oz) | **GND Plane** |
| L3 | Inner2 | Plane | 35μm (1oz) | **3V3 Power Plane** |
| L4 | Bottom | Signal | 35μm (1oz) | Additional routing, connectors |

**Dielectric (Core/Prepreg) Settings:**
| Layer | Material | Thickness |
|-------|----------|-----------|
| Core (between L2-L3) | FR4 | 1.2mm |
| Prepreg (L1-L2, L3-L4) | FR4 | 0.2mm |

5. Total board thickness: **~1.6mm** (standard)
6. Click **Apply** to save

### Alternative 3-Layer Configuration

If you prefer 3 layers (note: 3-layer PCBs are less common and may have longer lead times):

| Layer | Name | Purpose |
|-------|------|---------|
| L1 | Top | Signal + components |
| L2 | Inner | **GND Plane** |
| L3 | Bottom | Signal + 3V3 power traces |

---

## Board Setup and Design Rules

### Board Outline

1. Select the **BoardOutLine** layer
2. Draw a rectangle: **70mm x 50mm** (pocket-sized per project requirements)
3. Add corner fillets: **3mm radius** for a professional look

### Grid Settings

Click **Setup** → **Grid Settings**:

| Setting | Value | Use |
|---------|-------|-----|
| Default Grid | 0.5mm | Component placement |
| Fine Grid | 0.1mm | Precise adjustments |
| Routing Grid | 0.1mm | Trace alignment |

### Design Rules for JLCPCB 4-Layer

Click **Setup** → **Design Rules**:

| Rule | Value | Notes |
|------|-------|-------|
| Min Track Width | 0.15mm | Signals |
| Min Track Spacing | 0.15mm | Track-to-track |
| Min Via Diameter | 0.45mm | Outer diameter |
| Min Via Drill | 0.25mm | Hole size |
| Min Plane Clearance | 0.25mm | Around vias/pads on planes |
| Board Edge Clearance | 0.3mm | Components and copper |

### Net Classes

Click **Setup** → **Design Rules** → **Net Classes**:

| Net Class | Track Width | Via Size | Clearance | Nets |
|-----------|-------------|----------|-----------|------|
| **GND** | 0.3mm | 0.6/0.3mm | 0.2mm | GND |
| **Power** | 0.4mm | 0.6/0.3mm | 0.25mm | 3V3, VBAT, 5V_BOOST |
| **Signal** | 0.2mm | 0.5/0.25mm | 0.15mm | GPIO, SPI, I2C |
| **USB** | 0.25mm | 0.5/0.25mm | 0.15mm | D+, D- |

---

## Component Placement Strategy

### Placement Order for TechBot4

Place components in this sequence for optimal routing:

**Step 1: Power Components** (Top-left area)
- USB-C connector (edge of board)
- IP5306 battery management
- Power switch
- XC6220 LDO regulator
- Power-related capacitors (10μF)

**Step 2: ESP32 Module** (Center)
- ESP32-WROOM-32U-N8
- Position with antenna extending toward board edge
- Ensure antenna extends past board edge or has clearance

**Step 3: USB-Serial** (Near USB-C)
- CH340C
- Auto-reset transistors (S8050)
- Related resistors and capacitors

**Step 4: User Interface** (Right side)
- Navigation buttons (5x)
- Boot and Reset buttons
- Display connector (EYESPI)

**Step 5: Connectors** (Board edges)
- JST battery connector
- EYESPI display connector
- Antenna connection

### TechBot4 Layout Reference

```
┌─────────────────────────────────────────────────────────────────┐
│ [USB-C]                                                    70mm │
│    │                                                            │
│ [IP5306]──[Switch]──[XC6220]            [BOOT] [RST]           │
│                                                                 │
│ [CH340C] [S8050x2]                                             │
│     │                                                           │
│     └───────────────┐                                          │
│                     │                                          │
│  ┌──────────────────────────────────┐        [UP]              │
│  │                                  │                     50mm │
│  │      ESP32-WROOM-32U-N8          │    [LT] [SEL] [RT]       │
│  │                                  │                          │
│  │      (Keep antenna area          │        [DN]              │
│  │       completely clear)          │                          │
│  │                                  │────────────────► Antenna │
│  └──────────────────────────────────┘                          │
│                                                                 │
│ [JST Battery]                  [EYESPI 18-Pin Connector]       │
└─────────────────────────────────────────────────────────────────┘
```

### Component Placement Rules

| Component | Placement Rule |
|-----------|---------------|
| ESP32 | Antenna must extend past board edge or have 15mm clearance zone |
| IP5306 | Keep near USB-C and battery connector for short power traces |
| XC6220 LDO | Place close to ESP32 for clean 3.3V delivery |
| Decoupling Caps | Within 3mm of their associated IC power pins |
| CH340C | Near USB-C for short D+/D- traces |
| Buttons | Edge of board for easy access |

---

## Ground Plane Configuration

The ground plane is the most critical layer for TechBot4's performance.

### Creating the GND Plane on Layer 2

1. Select **Layer 2 (Inner1)** in the Layer Manager
2. Click **Place** → **Copper Area** (or `Shift+P`)
3. Configure in the Properties panel:

| Property | Value |
|----------|-------|
| **Net** | GND |
| **Layer** | Inner1 (L2) |
| **Clearance** | 0.25mm |
| **Pour Type** | Solid |
| **Thermal Relief** | Enabled |
| **Spoke Width** | 0.3mm |
| **Spoke Count** | 4 |
| **Thermal Gap** | 0.25mm |

4. Draw a polygon covering the entire board area
5. Press **Shift+B** to rebuild the copper pour

### GND Plane Design Rules

| Rule | Requirement |
|------|-------------|
| **Coverage** | Full board coverage on L2 (no splits) |
| **Antenna Zone** | Cut out area under ESP32 antenna (see below) |
| **Via Connections** | Use thermal relief for easy soldering |
| **Clearance** | 0.25mm around all through-holes and vias |

### ESP32 Antenna Keepout on GND Plane

The ESP32 antenna requires NO copper underneath:

1. On Layer 2 (GND plane), click **Place** → **Keepout Area**
2. Draw a rectangle covering:
   - 15mm beyond the ESP32 antenna edge
   - Full width of antenna area (~8mm)
3. Set properties:
   - **No Copper**: Enabled
   - **No Via**: Enabled
   - **No Track**: Enabled

```
ESP32 Module:
┌────────────────────────────────────┬─────────────┐
│                                    │  ANTENNA    │
│       ESP32-WROOM-32U              │  KEEPOUT    │
│                                    │  (No GND    │
│                                    │   plane)    │
└────────────────────────────────────┴─────────────┘
                                     ◄────15mm────►
```

---

## 3V3 Power Plane Configuration

A dedicated 3.3V plane provides clean power to all digital components.

### Creating the 3V3 Plane on Layer 3

1. Select **Layer 3 (Inner2)** in the Layer Manager
2. Click **Place** → **Copper Area**
3. Configure:

| Property | Value |
|----------|-------|
| **Net** | 3V3 |
| **Layer** | Inner2 (L3) |
| **Clearance** | 0.3mm |
| **Pour Type** | Solid |
| **Thermal Relief** | Enabled |
| **Spoke Width** | 0.3mm |

4. Draw a polygon covering the area needed for 3.3V distribution
5. Rebuild copper with **Shift+B**

### 3V3 Plane Coverage Strategy

The 3V3 plane doesn't need to cover the entire board. Focus on:

```
3V3 Plane Coverage Area:
┌─────────────────────────────────────────────────────────────────┐
│ ████████████████████████████████████████████████               │
│ ████████████████████████████████████████████████               │
│ ████████████████████████████████████████████████               │
│ ████████                                    ████               │
│ ████████    [ESP32 area - full 3V3]        ████               │
│ ████████                                    ████               │
│ ████████████████████████████████████████████████               │
│ ████████████████████████████████████████████████               │
│          │                                                      │
│          └─ Extend 3V3 plane under power section,               │
│             ESP32, CH340C, and display connector                │
└─────────────────────────────────────────────────────────────────┘
```

### Areas to Exclude from 3V3 Plane

| Area | Reason |
|------|--------|
| ESP32 Antenna | RF interference |
| Battery power section (VBAT, 5V_BOOST) | Different voltage domains |
| USB D+/D- routing area | Signal integrity |

### Connecting Components to 3V3 Plane

Components connect to the 3V3 plane via vias:

1. On the Top Layer (L1), route a short trace from IC 3V3 pin
2. Place a via: **0.5mm outer / 0.25mm drill**
3. The via connects directly to Layer 3 (3V3 plane)

| Component | 3V3 Connection |
|-----------|----------------|
| ESP32 3V3 pin | Via to L3 (within 2mm of pin) |
| CH340C VCC (pin 13) | Via to L3 |
| Display VCC (EYESPI pin 2) | Via to L3 |
| Decoupling capacitors | Via to L3 |

---

## Signal Routing

With dedicated planes, signal routing becomes straightforward.

### Top Layer (L1) Routing

Primary routing layer for horizontal traces:

| Signal Type | Track Width | Notes |
|-------------|-------------|-------|
| GPIO signals | 0.2mm | Standard signals |
| SPI bus (CLK, MOSI, MISO) | 0.2mm | Keep traces parallel, short |
| Power (from LDO to via) | 0.4mm | Wide for low impedance |
| USB D+/D- | 0.25mm | Differential pair |

### Bottom Layer (L4) Routing

Secondary routing layer for vertical traces:

| Usage | Notes |
|-------|-------|
| Cross-traffic routing | When L1 traces can't cross |
| Button connections | Route from buttons to vias |
| Connector signals | EYESPI, JST connections |

### Routing Rules

| Rule | Requirement |
|------|-------------|
| Via placement | Use vias to transition between L1 and L4 |
| Keep short | Minimize trace length, especially for SPI |
| Avoid antenna area | No traces on any layer near antenna |
| Power first | Route power connections before signals |

### USB Differential Pair Routing

For proper USB signal integrity:

1. Click **Route** → **Differential Pair Router** in EasyEDA Pro
2. Select D+ and D- nets
3. Configure:
   - Track width: 0.25mm
   - Gap: 0.15mm
   - Length matching: ±0.1mm
4. Route directly from USB-C to CH340C (keep under 25mm)
5. Use **Route** → **Length Tuning** if needed for matching

### SPI Bus Routing Priority

Route in this order:
1. **SPI_CLK** (GPIO18) - Most critical, keep shortest
2. **SPI_MOSI** (GPIO23) - Data to display/SD
3. **TFT_CS** (GPIO5) - Display chip select
4. **SD_CS** (GPIO16) - SD card chip select
5. **SPI_MISO** (GPIO19) - Data from SD card

---

## Via Strategy

Vias connect the signal layers (L1, L4) to the plane layers (L2, L3).

### Via Types for TechBot4

| Via Type | Size (OD/Drill) | Use |
|----------|-----------------|-----|
| **Signal Via** | 0.5mm / 0.25mm | Layer transitions for signals |
| **Power Via** | 0.6mm / 0.3mm | 3V3 and GND connections |
| **Stitching Via** | 0.5mm / 0.25mm | GND plane connections |

### GND Via Placement

Place GND vias at these locations:

| Location | Quantity | Purpose |
|----------|----------|---------|
| Board corners | 4 | Edge grounding |
| Around ESP32 | 6-8 | RF shielding |
| Near decoupling caps | 1 per cap | Low-impedance ground |
| Along board edges | Every 10mm | EMI containment |

### Via Array for Ground Stitching

1. Click **Place** → **Via Array** (Pro feature)
2. Configure:
   - Via: 0.5mm / 0.25mm
   - Net: GND
   - Rows: 1
   - Columns: as needed
   - Spacing: 8-10mm
3. Place along board perimeter

### Power Via Requirements

| Component | 3V3 Vias Required |
|-----------|-------------------|
| ESP32 | 2 vias (one near each 3V3 pin) |
| XC6220 Output | 2 vias (for current capacity) |
| CH340C | 1 via |
| Display connector | 1 via |

---

## Design Rule Check and Manufacturing

### Running DRC in EasyEDA Pro

1. Click **Design** → **Check DRC** (or `Ctrl+D`)
2. Review errors and warnings:

| Error Type | Common Cause | Fix |
|------------|--------------|-----|
| Clearance violation | Traces too close | Reroute with proper spacing |
| Unconnected net | Missing route | Complete the connection |
| Minimum width | Track too thin | Increase track width |
| Plane isolation | Via touching plane edge | Adjust via position |

### Pre-Manufacturing Checklist

Before generating Gerber files:

| Check | Requirement |
|-------|-------------|
| ☐ All ratsnest lines routed | No unconnected nets |
| ☐ DRC passes with 0 errors | No rule violations |
| ☐ GND plane coverage | Full L2 coverage (except antenna) |
| ☐ 3V3 plane coverage | Covers required components |
| ☐ Antenna keepout | Clear on all layers |
| ☐ Via stitching complete | GND vias around perimeter |
| ☐ Silkscreen readable | Labels visible, correct size |

### Generating 4-Layer Gerber Files

1. Click **Fabrication** → **PCB Fabrication File (Gerber)**
2. Verify these layers are included:

| File | Layer | Description |
|------|-------|-------------|
| GTL | Top Copper | L1 signal routing |
| G1 | Inner Layer 1 | L2 GND plane |
| G2 | Inner Layer 2 | L3 3V3 plane |
| GBL | Bottom Copper | L4 signal routing |
| GTO | Top Silkscreen | Component labels |
| GBO | Bottom Silkscreen | Bottom labels |
| GTS | Top Soldermask | Solder mask openings |
| GBS | Bottom Soldermask | Bottom solder mask |
| GKO | Board Outline | Board shape |
| DRL | Drill File | All holes |

3. Click **Generate Gerber**
4. Download the ZIP file

### JLCPCB 4-Layer Order Settings

When ordering from JLCPCB:

| Option | Recommended Value |
|--------|-------------------|
| Layers | 4 |
| PCB Thickness | 1.6mm |
| Copper Weight | 1oz (all layers) |
| Surface Finish | HASL or LeadFree HASL |
| Via Covering | Tented (recommended) |
| Remove Order Number | Yes (for clean look) |

---

## Quick Reference

### Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `W` | Route track |
| `V` | Place via |
| `Shift+B` | Rebuild copper pours |
| `1` / `2` / `3` / `4` | Switch to layer 1/2/3/4 |
| `M` | Move component |
| `R` | Rotate component |
| `Ctrl+D` | Run DRC |
| `G` | Toggle grid |

### TechBot4 Net Summary

| Net | Layer | Width | Connection Method |
|-----|-------|-------|-------------------|
| GND | L2 (plane) | N/A | Via to plane |
| 3V3 | L3 (plane) | N/A | Via to plane |
| SPI signals | L1 | 0.2mm | Direct routing |
| USB D+/D- | L1 | 0.25mm | Differential pair |
| GPIO | L1/L4 | 0.2mm | Route on signal layers |
| VBAT, 5V | L1 | 0.4mm | Wide traces only |

---

*This guide is specific to TechBot4 PCB design in EasyEDA Pro. For wiring connections, see WIRING.md.*
