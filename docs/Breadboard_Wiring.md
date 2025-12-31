# Breadboard Wiring Diagram - TechBot4 ESP32 Marauder

Easy breadboard build without custom PCB - Perfect for beginners!

## Overview

This guide shows how to build a fully functional TechBot4 Marauder using common development boards and a breadboard. No PCB fabrication or SMD soldering required!

---

## Required Parts

### Essential Components

| Item | Quantity | Notes |
|------|----------|-------|
| ESP32 Development Board | 1 | Any ESP32 board (DevKitC, NodeMCU-32S, etc.) |
| 0.96" OLED Display (I2C) | 1 | SSD1306, 128x64, I2C interface |
| Tactile Push Buttons | 4 | 6mm momentary switches |
| Breadboard | 1 | 830 point standard size |
| Jumper Wires | 20+ | Male-to-male for breadboard |
| USB Cable | 1 | For ESP32 (Micro-USB or USB-C) |

### Optional but Recommended

| Item | Quantity | Notes |
|------|----------|-------|
| 10kΩ Resistors | 4 | Pull-up for buttons (can use internal) |
| Buzzer (5V Passive) | 1 | Audio feedback |
| LED + 330Ω Resistor | 1 | Status indicator |
| LiPo Battery + Holder | 1 | For portable operation |

**Total Cost:** $15-25 (without optional parts)

---

## Wiring Diagram

### Pin Connections Table

| Component | Component Pin | → | ESP32 Pin | Notes |
|-----------|---------------|---|-----------|-------|
| **OLED Display** |
| OLED | VCC | → | 3.3V | Power supply |
| OLED | GND | → | GND | Ground |
| OLED | SCL | → | GPIO 22 | I2C Clock |
| OLED | SDA | → | GPIO 21 | I2C Data |
| **Buttons** |
| SELECT Button | One side | → | GPIO 34 | Input |
| SELECT Button | Other side | → | GND | Ground |
| UP Button | One side | → | GPIO 35 | Input |
| UP Button | Other side | → | GND | Ground |
| DOWN Button | One side | → | GPIO 32 | Input |
| DOWN Button | Other side | → | GND | Ground |
| BACK Button | One side | → | GPIO 33 | Input |
| BACK Button | Other side | → | GND | Ground |
| **Optional Buzzer** |
| Buzzer | + (Positive) | → | GPIO 25 | Through 1kΩ resistor |
| Buzzer | - (Negative) | → | GND | Ground |
| **Optional Status LED** |
| LED | Anode (+) | → | GPIO 2 | Through 330Ω resistor |
| LED | Cathode (-) | → | GND | Ground |

---

## Visual Breadboard Layout

```
          ┌─────────────────────────────────────────┐
          │         Breadboard Layout               │
          └─────────────────────────────────────────┘

     3.3V ──────┬─────────────────────── OLED VCC
                │
     GND ───────┼───┬─┬─┬─┬──────────┬── OLED GND
                │   │ │ │ │          │
    GPIO 22 ────┼───┼─┼─┼─┼──────────┼── OLED SCL
                │   │ │ │ │          │
    GPIO 21 ────┼───┼─┼─┼─┼──────────┼── OLED SDA
                │   │ │ │ │          │
    GPIO 34 ────┼───● │ │ │          │   (● = Button)
                │     │ │ │          │
    GPIO 35 ────┼─────● │ │          │
                │       │ │          │
    GPIO 32 ────┼───────● │          │
                │         │          │
    GPIO 33 ────┼─────────●          │
                │                    │
    GPIO 25 ────┼────────────────────┼── Buzzer (+)
                │                    │
    GPIO 2  ────┼────────────────────┼── LED Anode
                │                    │
                └────────────────────┘

Legend:
● = Push button connected to GPIO and GND
```

---

## Step-by-Step Wiring Instructions

### Step 1: Insert ESP32 into Breadboard

1. Place ESP32 development board across the center divide of breadboard
2. Ensure pins on both sides have room for connections
3. Press firmly but gently into breadboard

### Step 2: OLED Display Connections

**If display has header pins:**
1. Insert display into breadboard (separate row from ESP32)
2. Or use 4 jumper wires directly to display

**Connections:**
```
OLED VCC → ESP32 3.3V pin (use breadboard power rail)
OLED GND → ESP32 GND pin (use breadboard ground rail)
OLED SCL → ESP32 GPIO 22 (direct jumper wire)
OLED SDA → ESP32 GPIO 21 (direct jumper wire)
```

**IMPORTANT:** Use 3.3V, NOT 5V! Many OLED displays are 3.3V only.

### Step 3: Button Connections

**For each button:**
1. Insert button across breadboard center divide
2. One side connects to ESP32 GPIO
3. Other side connects to GND rail

**Without external resistors (simpler):**
```
Button → ESP32 GPIO directly
Button → GND rail
(Use internal pull-ups in firmware: pinMode(34, INPUT_PULLUP))
```

**With external 10kΩ pull-up resistors (more stable):**
```
ESP32 GPIO → 10kΩ Resistor → 3.3V rail
ESP32 GPIO → Button → GND rail
```

**Button assignments:**
- GPIO 34 → SELECT button
- GPIO 35 → UP button
- GPIO 32 → DOWN button
- GPIO 33 → BACK button

### Step 4: Optional Buzzer (Recommended)

```
GPIO 25 → Buzzer Positive (+)
Buzzer Negative (-) → GND
```

**Note:** Some buzzers may need a transistor driver. If buzzer is weak, add:
```
GPIO 25 → 1kΩ Resistor → Transistor Base (2N3904)
Transistor Collector → Buzzer (+)
Transistor Emitter → GND
Buzzer (-) → 3.3V or 5V (check buzzer rating)
```

### Step 5: Optional Status LED

```
GPIO 2 → 330Ω Resistor → LED Anode (+, longer leg)
LED Cathode (-, shorter leg) → GND
```

### Step 6: Power Rails Setup

**Connect ESP32 power to breadboard rails:**
```
ESP32 3.3V pin → Breadboard + rail (red)
ESP32 GND pin → Breadboard - rail (blue/black)
```

**Connect both breadboard sides (if using both):**
```
Left + rail → Right + rail
Left - rail → Right - rail
```

---

## Detailed Connection Photos/Diagrams

### OLED Display 4-Pin Connector

```
┌─────────────┐
│   OLED      │
│  128 x 64   │
└─────────────┘
  │ │ │ │
  V G S S
  C N C D
  C D L A
  
  VCC → Red wire → 3.3V
  GND → Black wire → GND
  SCL → Yellow wire → GPIO 22
  SDA → Green wire → GPIO 21
```

### Button Wiring (Simple Method)

```
  ESP32                    Button               GND Rail
   GPIO 34 ─────────── [  ●  ●  ] ──────────── ─ (black)
                         \___/
```

### Button Wiring (With Pull-up Resistor)

```
  3.3V Rail               ESP32                 Button              GND Rail
      + ────── 10kΩ ────── GPIO 34 ────── [  ●  ●  ] ──────── ─
                                             \___/
```

---

## Complete Breadboard Layout Example

```
                    BREADBOARD TOP VIEW
     
     Power Rails              Center Divide              Power Rails
     + (red)  - (blue)                                + (red)  - (blue)
     ═══════  ═══════                                ═══════  ═══════
     │       │         ┌─────────────────┐          │       │
     │       │         │    ESP32 BOARD  │          │       │
     │       │         │                 │          │       │
     │       │         │  3V3    ●●● GND │          │       │
     └───────┼─────────┤  GPIO22 ●●● 21  ├──────────┼───────┘
             │         │  GPIO34 ●●● 35  │          │
             │         │  GPIO32 ●●● 33  │          │
             │         │  GPIO25 ●●● 2   │          │
             │         └─────────────────┘          │
             │                                       │
             │         ┌─────────────┐              │
             │         │    OLED     │              │
             └─────────┤ VCC GND     │──────────────┘
                       │ SCL SDA     │
                       └─────────────┘
                       
                       [BTN] [BTN] [BTN] [BTN]
                        SEL   UP   DOWN  BACK
```

---

## Firmware Configuration for Breadboard Build

The default firmware is configured for the breadboard pin layout. No changes needed!

### Pin Definitions (Already in firmware)

```cpp
// Button pins (INPUT_PULLUP mode)
#define BUTTON_SELECT 34
#define BUTTON_UP 35
#define BUTTON_DOWN 32
#define BUTTON_BACK 33

// Status LED and Buzzer
#define LED_STATUS 2
#define BUZZER_PIN 25

// I2C for OLED Display
#define OLED_SDA 21
#define OLED_SCL 22
```

---

## Testing Your Build

### Visual Inspection Checklist

- [ ] All wires firmly connected
- [ ] No loose connections
- [ ] OLED display connected to 3.3V (not 5V!)
- [ ] Buttons connect GPIO to GND
- [ ] LED polarity correct (longer leg to resistor/GPIO)
- [ ] No short circuits between power rails

### Power-On Test

1. **Connect USB cable to ESP32**
2. **ESP32 power LED should light up**
3. **OLED display should power on** (may show random pixels)
4. **No smoke or burning smell** (disconnect immediately if any!)

### Button Test (Before Firmware)

Use multimeter in continuity mode:
1. Touch probes to button terminals
2. Press button → Should beep (continuity)
3. Release button → Should not beep (open)

### After Firmware Upload

1. **OLED should show TechBot4 Marauder menu**
2. **Press buttons → Menu selection changes**
3. **SELECT button → Enters menu option**
4. **Buzzer beeps on button press** (if connected)
5. **Status LED blinks** (if connected)

---

## Troubleshooting

### Display Shows Nothing

**Check:**
- Display powered (3.3V not 5V)
- SDA and SCL not swapped
- I2C address correct (usually 0x3C)
- Connections firm in breadboard
- Try different display (they can be fragile)

**Test:**
```
Upload I2C scanner sketch to find display address
```

### Buttons Don't Work

**Check:**
- Button actually making contact in breadboard
- Correct GPIO pins used
- Firm connections
- Try different buttons (they can be faulty)

**Test:**
```cpp
// Simple button test sketch
void setup() {
  pinMode(34, INPUT_PULLUP);
  Serial.begin(115200);
}
void loop() {
  Serial.println(digitalRead(34));
  delay(100);
}
```

### No WiFi Networks Found

**Check:**
- Near WiFi networks (try near your router)
- ESP32 antenna not covered
- Try different location
- ESP32 might be damaged (rare)

### ESP32 Won't Program

**Check:**
- Correct COM port selected
- CP210x or CH340 drivers installed
- USB cable supports data (not charge-only)
- Try holding BOOT button while uploading

---

## Power Options

### USB Power (Development)

- Simplest option
- Connect to computer or USB charger
- Always available power
- Good for testing

### Battery Power (Portable)

**Option 1: Power Bank**
- Connect USB power bank to ESP32
- Easiest portable solution
- No wiring needed

**Option 2: LiPo Battery (Advanced)**
- Need TP4056 charging module
- Connect to ESP32 VIN and GND
- Check ESP32 board voltage requirements
- Most boards accept 3.7-5V on VIN pin

**Wiring:**
```
LiPo Battery (+) → TP4056 (BAT+)
LiPo Battery (-) → TP4056 (BAT-)
TP4056 (OUT+) → ESP32 VIN or 5V pin
TP4056 (OUT-) → ESP32 GND
TP4056 USB → Charging port
```

---

## Upgrading Your Build

### From Breadboard to Perfboard

Once your breadboard version works:
1. Transfer design to perfboard (solderable breadboard)
2. Solder all connections
3. More permanent than breadboard
4. Still no custom PCB needed

### From Breadboard to Custom PCB

When ready for professional build:
1. Order custom PCB (see PCB_Fabrication_Guide.md)
2. Much more compact
3. Phone-sized form factor
4. All features integrated

---

## Tips for Success

### Breadboard Tips

1. **Push wires in firmly** - Loose connections cause intermittent issues
2. **Use solid core wire** - Stranded wire doesn't work well in breadboards
3. **Keep wires short** - Reduces noise and looks cleaner
4. **Color code wires** - Red=power, Black=ground, others=signals
5. **Take photos** - Document your build for troubleshooting

### Component Tips

1. **Buy extra displays** - They're fragile, good to have spares
2. **Test buttons first** - Some cheap buttons are faulty
3. **Check ESP32 pinout** - Different boards have different layouts
4. **Verify 3.3V vs 5V** - Don't burn out 3.3V components!

### Debugging Tips

1. **Start simple** - Get display working first, then add buttons
2. **Test incrementally** - Don't wire everything at once
3. **Use serial monitor** - Debug output very helpful
4. **Check power first** - Measure voltages with multimeter
5. **Verify continuity** - Use multimeter to check connections

---

## Next Steps

### Your breadboard build works! Now:

✓ **Learn to use it** → See Usage_Guide.md  
✓ **Customize firmware** → Add your own features  
✓ **Share your build** → Post photos, help others  
✓ **Plan PCB build** → When ready for portable version  

---

## Support

**Need help with breadboard build?**

- GitHub Issues: Ask questions
- Share photos: We can spot wiring problems
- Community: Discord/Forums for real-time help

---

**Happy breadboarding! 🍞🔌**

*Breadboards: Making electronics accessible since 1971!*
