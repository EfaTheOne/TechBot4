# PCB Fabrication Guide - TechBot4 ESP32 Marauder

This guide explains how to manufacture the PCB for your TechBot4 ESP32 Marauder device.

## Prerequisites

Before ordering, you should have:
- [ ] PCB design files (created in KiCad, EasyEDA, or similar)
- [ ] Generated Gerber files
- [ ] Bill of Materials (BOM)
- [ ] Payment method for PCB manufacturer

---

## Step 1: Design Software Options

### Option A: KiCad (Recommended - Free & Professional)

**Why KiCad:**
- Completely free and open-source
- Professional-grade features
- Large component library
- Cross-platform (Windows, Mac, Linux)
- Direct Gerber export

**Installation:**
1. Download from: https://www.kicad.org/download/
2. Install for your operating system
3. Launch KiCad and create new project

**Creating the Design:**
```
1. Open KiCad
2. Create New Project → "TechBot4_Marauder"
3. Open Schematic Editor (Eeschema)
4. Import component libraries
5. Draw schematic based on /hardware/schematics/schematic.txt
6. Run Electrical Rules Check (ERC)
7. Assign footprints to all components
8. Open PCB Layout Editor (Pcbnew)
9. Import netlist from schematic
10. Arrange components per /hardware/pcb/layout_guide.txt
11. Route traces (manual or auto-router)
12. Add ground plane and power pour
13. Add silkscreen text and logos
14. Run Design Rules Check (DRC)
15. Generate Gerber files
```

### Option B: EasyEDA (Easiest - Browser-Based)

**Why EasyEDA:**
- No installation required (web-based)
- Beginner-friendly interface
- Direct integration with JLCPCB
- Free component libraries
- Auto-routing available

**Getting Started:**
1. Go to: https://easyeda.com/
2. Create free account
3. New Project → "TechBot4_Marauder"
4. Use schematic diagram to create circuit
5. Convert to PCB layout
6. Follow layout guide for component placement
7. Order directly from EasyEDA/JLCPCB

### Option C: Use Pre-Made Files

If design files are provided in the repository:
```bash
# Look for these files in /hardware/pcb/:
- TechBot4_Marauder.kicad_pcb
- TechBot4_Marauder.sch
- gerbers/ directory with .gbr files
```

---

## Step 2: Generate Gerber Files

Gerber files are the industry-standard format for PCB manufacturing.

### From KiCad:

1. **Open PCB file** in Pcbnew
2. **File → Plot**
3. **Select Plot Format**: Gerber
4. **Output directory**: gerbers/
5. **Select layers to include:**
   - ✓ F.Cu (Front copper)
   - ✓ B.Cu (Back copper)
   - ✓ F.SilkS (Front silkscreen)
   - ✓ B.SilkS (Back silkscreen)
   - ✓ F.Mask (Front solder mask)
   - ✓ B.Mask (Back solder mask)
   - ✓ Edge.Cuts (Board outline)
6. **Plot Options:**
   - ✓ Use Protel filename extensions
   - ✓ Exclude pads from silkscreen
   - ✓ Subtract mask from silk
7. **Click "Plot"**
8. **Click "Generate Drill Files"**
   - Drill units: Millimeters
   - Drill map file format: PostScript
   - Drill file format: Excellon
   - Click "Generate Drill File"

### Expected Output Files:
```
gerbers/
├── TechBot4_Marauder-F.Cu.gbr      (Top copper)
├── TechBot4_Marauder-B.Cu.gbr      (Bottom copper)
├── TechBot4_Marauder-F.SilkS.gbr   (Top silkscreen)
├── TechBot4_Marauder-B.SilkS.gbr   (Bottom silkscreen)
├── TechBot4_Marauder-F.Mask.gbr    (Top solder mask)
├── TechBot4_Marauder-B.Mask.gbr    (Bottom solder mask)
├── TechBot4_Marauder-Edge.Cuts.gbr (Board outline)
└── TechBot4_Marauder.drl           (Drill file)
```

### Verify Gerber Files:

Use online Gerber viewer to check files before ordering:
- https://www.pcbway.com/project/OnlineGerberViewer.html
- https://gerber-viewer.easyeda.com/

**What to Check:**
- ✓ All layers present
- ✓ Board outline correct (80mm x 150mm)
- ✓ No missing traces
- ✓ Silkscreen readable
- ✓ Mounting holes present
- ✓ Component pads properly sized

---

## Step 3: Choose a PCB Manufacturer

### Recommended: JLCPCB (Best for Beginners)

**Pros:**
- Very cheap ($2 for 5 PCBs)
- Fast manufacturing (2-3 days)
- Good quality
- Easy ordering process
- Optional assembly service

**Cons:**
- Shipping from China (2-4 weeks)
- Assembly service more expensive

**Website**: https://jlcpcb.com/

### Alternative: PCBWay

**Pros:**
- High quality
- Assembly service available
- Customer support
- Various color options

**Cons:**
- Slightly more expensive ($5 for 5 PCBs)

**Website**: https://www.pcbway.com/

### Alternative: OSH Park (USA)

**Pros:**
- USA-based (faster for US customers)
- Purple PCBs (distinctive)
- High quality ENIG finish

**Cons:**
- More expensive ($20+ for 3 PCBs)
- Longer lead time (2-3 weeks)

**Website**: https://oshpark.com/

---

## Step 4: Order PCBs from JLCPCB (Detailed Steps)

### Create ZIP Archive

First, compress your Gerber files:
```bash
# On Linux/Mac:
cd gerbers/
zip -r ../TechBot4_Marauder_Gerbers.zip *

# On Windows:
# Right-click gerbers folder → Send to → Compressed folder
```

### Ordering Process:

1. **Go to JLCPCB.com**
2. **Click "Order Now"**
3. **Upload Gerber ZIP file**
   - System will auto-detect settings
4. **Review Auto-Detected Settings:**
   - Base Material: FR-4
   - Layers: 2
   - Dimensions: 80 x 150 mm
   - PCB Qty: 5 (minimum)
   - Product Type: Industrial/Consumer Electronics

5. **Customize PCB Options:**

   | Setting | Value | Notes |
   |---------|-------|-------|
   | Different Design | 1 | Single design |
   | Delivery Format | Single PCB | Individual boards |
   | PCB Thickness | 1.6mm | Standard |
   | PCB Color | Black | Recommended |
   | Silkscreen | White | Standard |
   | Surface Finish | HASL(with lead) | Cheapest |
   | Outer Copper Weight | 1 oz | Standard |
   | Gold Fingers | No | Not needed |
   | Confirm Production | No | Save $1 |
   | Flying Probe Test | Fully Test | Recommended |
   | Castellated Holes | No | Not needed |
   | Remove Order Number | No | Save $1.50 |

6. **Optional Upgrades:**
   - Surface Finish: ENIG (better for fine-pitch, +$15)
   - PCB Color: Blue/Red/Green (personal preference, +$0)
   - Remove Order Number: Yes (cleaner look, +$1.50)

7. **Review Total Cost:**
   - PCB: ~$2 (5 pieces)
   - Shipping: $3-20 (depends on speed)
   - **Total: $5-25**

8. **Select Shipping:**
   - **Regular (~30 days)**: Cheapest ($3-5)
   - **Express (~7-15 days)**: Faster ($10-15)
   - **DHL/FedEx (~3-7 days)**: Fastest ($20+)

9. **Click "Save to Cart"**

10. **Optional: SMT Assembly Service**
    - If you want JLCPCB to assemble the PCB
    - Click "SMT Assembly"
    - Upload BOM and CPL (component placement list)
    - Adds significant cost but saves time
    - Good for complex builds

11. **Checkout and Pay**
    - Create account or login
    - Enter shipping address
    - Select payment method (PayPal, Credit Card)
    - Complete payment

---

## Step 5: Wait for Manufacturing

### Timeline:
```
Order placed      → Day 0
PCB review        → Day 1 (you'll get email to confirm)
Manufacturing     → Day 1-3
Quality check     → Day 3
Shipping          → Day 3
Arrival           → Day 10-35 (depending on shipping)
```

### Tracking:
- Check order status at JLCPCB.com
- Tracking number provided when shipped
- Track at: https://www.17track.net/

---

## Step 6: Receive and Inspect PCBs

When PCBs arrive:

### Visual Inspection Checklist:
- [ ] Correct quantity received (usually 5)
- [ ] Board dimensions correct (80mm x 150mm)
- [ ] No physical damage or cracks
- [ ] Solder mask even and complete
- [ ] Silkscreen clear and readable
- [ ] Holes drilled correctly
- [ ] Copper traces visible and continuous
- [ ] Board color as ordered

### Electrical Testing:
```
1. Use multimeter in continuity mode
2. Test for shorts:
   - 3.3V rail to GND: Should be OPEN
   - 5V rail to GND: Should be OPEN
   - Any power rail to power rail: Should be OPEN
3. Test critical connections:
   - GND pad to GND pad: Should BEEP (connected)
   - Test points to respective nets
```

### Common Issues and Solutions:

| Issue | Cause | Solution |
|-------|-------|----------|
| Missing traces | Design error | Check Gerber files, re-order |
| Wrong dimensions | Wrong unit in design | Re-order with correct dimensions |
| Broken board | Shipping damage | Contact manufacturer for replacement |
| Holes too small | Drill file error | Use smaller components or re-order |
| Silkscreen over pads | Design error | Not critical, proceed or re-order |

---

## Step 7: Proceed to Assembly

Once PCBs are verified:
1. Gather all components (see BOM.md)
2. Prepare soldering workspace
3. Follow Assembly Guide (see Assembly_Guide.md)

---

## Cost Comparison (5 PCBs)

| Manufacturer | Base Cost | Shipping | Total | Lead Time |
|--------------|-----------|----------|-------|-----------|
| JLCPCB Regular | $2 | $3-5 | $5-7 | 30 days |
| JLCPCB Express | $2 | $15-20 | $17-22 | 7-10 days |
| PCBWay Regular | $5 | $5-10 | $10-15 | 20-30 days |
| OSH Park | $20 | Free (USA) | $20 | 14-21 days |

---

## Troubleshooting

### Gerber Upload Fails
- **Problem**: Files rejected by manufacturer
- **Solution**: Check file format, re-export from KiCad, ensure ZIP contains all layers

### Wrong Board Size Detected
- **Problem**: Dimensions shown as incorrect
- **Solution**: Check Edge.Cuts layer in design, ensure proper board outline

### Manufacturing Put on Hold
- **Problem**: Design violates manufacturer's rules
- **Solution**: Review design rules, fix violations, re-upload

### High Price Quote
- **Problem**: Unexpected costs
- **Solution**: Check PCB size (large boards cost more), reduce layers, simplify design

---

## Advanced Options

### Panelization
For mass production:
- Combine multiple boards into one panel
- Reduces per-unit cost
- Requires V-groove or tab routing
- Minimum panel size usually 100x100mm

### Stencil Order
For SMT assembly:
- Order solder paste stencil ($7-15)
- Makes SMD soldering much easier
- Frameless or framed options
- Choose stencil thickness: 0.12mm standard

### Assembly Service
Let manufacturer assemble the board:
- Upload BOM and placement files
- They source and solder components
- Costs $8-30 per board + component costs
- Great for complex designs or mass production

---

## Environmental Considerations

### Lead-Free Option
- RoHS-compliant (recommended)
- HASL lead-free or ENIG finish
- Slightly higher cost
- Required for commercial products in many countries

### Recycling
- PCBs contain recyclable materials
- Don't throw away in regular trash
- Find local e-waste recycling facility

---

## Next Steps

After receiving PCBs:
1. ✓ Inspect boards carefully
2. → Proceed to Assembly Guide
3. → Gather all components from BOM
4. → Set up soldering workspace
5. → Follow step-by-step assembly

---

## Resources

- **KiCad Tutorial**: https://docs.kicad.org/
- **JLCPCB Capabilities**: https://jlcpcb.com/capabilities/pcb-capabilities
- **Gerber Format Guide**: https://www.ucamco.com/en/gerber
- **PCB Design Best Practices**: https://www.proto-electronics.com/blog

---

**Document Version**: 1.0  
**Last Updated**: 2025-01-01  
**Project**: TechBot4 ESP32 Marauder
