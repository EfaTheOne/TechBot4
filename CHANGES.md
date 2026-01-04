# TechBot4 BOM and Wiring Changes

## Date: 2026-01-04

## Summary
Fixed discrepancies between the Bill of Materials (BOM) in README.md and the actual wiring requirements in WIRING.md. The BOM has been corrected to match the actual circuit requirements.

---

## Changes Made

### 1. 10μF Capacitors (CL21A106KOQNNNE | JLCPCB Part #C1713)
**Changed from:** 4x → **Changed to:** 5x

**Reason:** The wiring diagram requires 5 capacitors for proper power filtering:
- IP5306 Pin 1 (VIN) - USB input filtering
- IP5306 Pin 6 (BAT) - Battery connection filtering  
- IP5306 Pin 8 (VOUT) - 5V boost output filtering
- XC6220 Pin 1 (VIN) - LDO input filtering
- XC6220 Pin 5 (VOUT) - LDO output filtering

### 2. 100nF Capacitors (CL10B104KA8NNNC | JLCPCB Part #C1590)
**Changed from:** 4x → **Changed to:** 3x

**Reason:** The wiring diagram only requires 3 capacitors:
- XC6220 Pin 5 (VOUT) - LDO output stability (used alongside the 10μF cap)
- CH340C Pin 13 (VCC) - Decoupling capacitor
- CH340C Pin 12 (DTR#) to ESP32 EN - Auto-reset timing capacitor

---

## What You Need to Order/Have

### Updated Component Quantities

| Component | Part Number | Old Qty | New Qty | Change |
|-----------|-------------|---------|---------|--------|
| 10μF Capacitor | CL21A106KOQNNNE (JLCPCB #C1713) | 4x | **5x** | +1 ⚠️ |
| 100nF Capacitor | CL10B104KA8NNNC (JLCPCB #C1590) | 4x | **3x** | -1 ✓ |

### Action Required:
- **Order 1 additional 10μF capacitor** (CL21A106KOQNNNE) if you only have 4
- If you already ordered 4x 100nF capacitors, you'll have 1 spare (this is fine)

---

## Rewiring Instructions

### If You Already Built the Circuit:

#### Check Your Current Build:

1. **Count your 10μF capacitors** - You should have 5 total:
   - [ ] One at IP5306 Pin 1 (VIN - where USB 5V connects)
   - [ ] One at IP5306 Pin 6 (BAT - where battery connects)
   - [ ] One at IP5306 Pin 8 (VOUT - 5V boost output)
   - [ ] One at XC6220 Pin 1 (VIN - LDO input from power switch)
   - [ ] One at XC6220 Pin 5 (VOUT - 3.3V output rail)

2. **Count your 100nF capacitors** - You should have 3 total:
   - [ ] One at XC6220 Pin 5 (VOUT - alongside the 10μF cap)
   - [ ] One at CH340C Pin 13 (VCC - power decoupling)
   - [ ] One between CH340C Pin 12 (DTR#) and ESP32 EN (auto-reset)

#### If You're Missing the 5th 10μF Capacitor:

The most critical location for the missing capacitor is **XC6220 Pin 5 (VOUT)** as this stabilizes the 3.3V rail that powers all your logic circuits.

**Priority order for placing capacitors:**
1. **CRITICAL:** XC6220 Pin 5 (VOUT) - Must have 10μF for stable 3.3V output
2. **CRITICAL:** IP5306 Pin 8 (VOUT) - Stabilizes 5V boost output
3. **IMPORTANT:** XC6220 Pin 1 (VIN) - Filters input to LDO
4. **IMPORTANT:** IP5306 Pin 1 (VIN) - Filters USB input  
5. **IMPORTANT:** IP5306 Pin 6 (BAT) - Filters battery connection

**Temporary workaround if you only have 4 capacitors:**
- Place capacitors at locations 1-4 above
- The circuit should work but may have slightly more noise
- Order the 5th capacitor and add it to IP5306 Pin 6 (BAT) when it arrives

#### If You Have an Extra 100nF Capacitor:

You ordered 4 but only need 3. Keep the spare for future projects or potential repairs.

---

## No Other Changes Required

All other components remain unchanged:
- ✓ Buttons (7x) - Correct
- ✓ Resistors (5x 10kΩ, 2x 1kΩ, 2x 5.1kΩ) - Correct
- ✓ Transistors (2x S8050) - Correct
- ✓ All ICs and connectors - Correct

---

## Verification

After making changes, verify your circuit matches the updated quantities in both:
- README.md - PCBA Parts section
- WIRING.md - Component Summary table

Both documents now show:
- 5x 10μF capacitors
- 3x 100nF capacitors

---

## Questions or Issues?

If you encounter any problems or have questions about these changes, please refer to:
- Full wiring details: See WIRING.md
- Component datasheets: Check manufacturer part numbers in README.md
