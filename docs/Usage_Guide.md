# Usage Guide - TechBot4 ESP32 Marauder

Complete guide to using your TechBot4 ESP32 Marauder pen testing device.

## ⚠️ Legal Disclaimer

**READ THIS FIRST:**

This device is designed for **EDUCATIONAL PURPOSES ONLY**. You must:

- ✓ Use only on networks you own or have explicit written permission to test
- ✓ Comply with all local, state, and federal laws
- ✓ Understand that unauthorized network access is illegal
- ✓ Take responsibility for your actions

**Unauthorized use of this device may result in:**
- Criminal prosecution
- Civil liability
- Fines and imprisonment
- Network access termination

**By using this device, you agree that you are solely responsible for ensuring legal and ethical use.**

---

## Table of Contents

1. [Getting Started](#getting-started)
2. [Basic Operation](#basic-operation)
3. [WiFi Scanner](#wifi-scanner)
4. [WiFi Attacks](#wifi-attacks)
5. [Bluetooth Scanner](#bluetooth-scanner)
6. [Packet Monitor](#packet-monitor)
7. [Battery Management](#battery-management)
8. [Tips and Best Practices](#tips-and-best-practices)
9. [Troubleshooting](#troubleshooting)

---

## Getting Started

### First Power-On

1. **Charge the battery:**
   - Connect via USB-C
   - Red LED indicates charging
   - Yellow LED indicates fully charged
   - First charge: 2-3 hours

2. **Power on the device:**
   - Slide power switch to ON position
   - Status LED should blink
   - Buzzer makes startup sound
   - Display shows "TechBot4 Marauder"

3. **Navigate the menu:**
   - **UP button**: Move selection up
   - **DOWN button**: Move selection down
   - **SELECT button**: Choose current option
   - **BACK button**: Return to previous menu

### Understanding the Interface

**Display Layout:**
```
┌────────────────────────┐
│ TechBot4 Marauder      │ ← Title
│========================│
│ > WiFi Scanner         │ ← Current selection (>)
│   WiFi Attacks         │
│   Bluetooth Scanner    │
│   Packet Monitor       │
│   Settings             │
│                        │
│ Battery: 85%  📶 WiFi  │ ← Status bar
└────────────────────────┘
```

**Status Indicators:**
- **Blue LED**: System active
- **Red LED (charge)**: Battery charging
- **Yellow LED**: Battery full/standby
- **Buzzer beeps**: Feedback on button press

---

## Basic Operation

### Navigating Menus

**Main Menu Options:**
1. WiFi Scanner
2. WiFi Attacks
3. Bluetooth Scanner
4. Packet Monitor
5. Settings

**Navigation:**
```
1. Press UP/DOWN to highlight option
2. Press SELECT to enter that option
3. Press BACK to return to main menu
4. Hold BACK for 3 seconds to power off
```

### Serial Monitor Mode

For advanced users, connect via USB and use Serial Monitor:

```
1. Connect USB cable
2. Open Arduino IDE Serial Monitor (115200 baud)
3. More detailed output and debugging info
4. Can type commands directly
5. Better for analyzing results
```

---

## WiFi Scanner

### Purpose
Scan for WiFi networks in the area to identify available networks, their channels, signal strength, and security settings.

### How to Use

1. **From main menu, select "WiFi Scanner"**
2. **Press SELECT to start scanning**
3. **Wait 3-5 seconds** for scan to complete
4. **Review results:**

**Display Output:**
```
=== WiFi Networks ===
Total: 12 networks

1. HomeNetwork_5G
   RSSI: -45 dBm
   Ch: 36 | Secured
   
2. CoffeeShop-Guest
   RSSI: -67 dBm
   Ch: 6 | Open
   
3. FBI_Van_2
   RSSI: -82 dBm
   Ch: 11 | Secured
```

**Serial Monitor Output** (more detailed):
```
 1: HomeNetwork_5G              | RSSI:  -45 dBm | Ch:  36 | SECURED
 2: CoffeeShop-Guest            | RSSI:  -67 dBm | Ch:   6 | OPEN
 3: FBI_Van_2                   | RSSI:  -82 dBm | Ch:  11 | SECURED
```

### Understanding the Results

**RSSI (Signal Strength):**
- -30 to -50 dBm: Excellent signal
- -51 to -60 dBm: Good signal
- -61 to -70 dBm: Fair signal
- -71 to -80 dBm: Weak signal
- -81 to -90 dBm: Very weak signal
- Below -90 dBm: Unusable signal

**Channel Information:**
- 2.4 GHz: Channels 1-14
- 5 GHz: Channels 36, 40, 44, etc.
- Congested channels: Many networks on same channel

**Security:**
- OPEN: No password required (risky for users)
- SECURED: Password protected (WPA, WPA2, WPA3)

### Actions

- **Press SELECT**: Re-scan for networks
- **Press UP/DOWN**: Scroll through results
- **Press BACK**: Return to main menu

### Use Cases

✓ **Legitimate uses:**
- Survey your own network coverage
- Check for rogue access points on your network
- Optimize your WiFi channel selection
- Verify your network name broadcasts correctly

✗ **Illegal uses:**
- Identifying networks to attack without permission
- Stalking or surveillance

---

## WiFi Attacks

### ⚠️ WARNING

**These features are for AUTHORIZED TESTING ONLY!**

Use only on:
- Your own network
- Networks where you have written permission to conduct penetration testing
- Isolated test environments

### Attack Types

From WiFi Attacks menu:
1. Deauth Attack
2. Beacon Spam
3. Probe Request Flood

### 1. Deauth Attack

**What it does:**
Sends deauthentication packets to disconnect clients from access point.

**How to use:**
```
1. Select "WiFi Attacks" from main menu
2. Select "Deauth Attack"
3. Press SELECT to start
4. Attack runs for 100 cycles (~10 seconds)
5. Observe results on display/serial
6. Press BACK to stop early
```

**What you'll see:**
```
[!] Starting Deauth Attack...
[!] WARNING: Educational purposes only!
..........
[✓] Attack cycle complete
```

**Legitimate uses:**
- Testing your own network's resilience
- Verifying IDS/IPS detection
- Demonstrating vulnerability to clients
- Research and education

**How it works:**
- Sends forged deauth frames
- Targets broadcast (all clients)
- May temporarily disrupt connections
- Modern networks have protections (802.11w)

**Defense:**
- Enable 802.11w (Protected Management Frames)
- Use WPA3 if available
- Monitor for deauth floods
- Implement wireless IDS

### 2. Beacon Spam

**What it does:**
Creates multiple fake WiFi networks that appear in WiFi scanners.

**How to use:**
```
1. Select "WiFi Attacks" → "Beacon Spam"
2. Press SELECT to start
3. Sends beacon frames for fake networks
4. Check nearby devices - they'll see fake networks
5. Press BACK to stop
```

**Example fake networks:**
- FREE_WIFI
- FBI_Surveillance_Van
- Virus.exe
- HackTheGibson
- Pwned

**What you'll see:**
```
[!] Starting Beacon Spam...
..........
[✓] Beacon spam complete
```

**Legitimate uses:**
- Demonstrate rogue AP detection
- Test WiFi scanning applications
- Security awareness training
- Network clutter simulation

**How it works:**
- Broadcasts beacon frames
- Creates "virtual" access points
- Networks appear but can't be connected to
- Can confuse WiFi analyzers

**Defense:**
- Whitelist known networks
- Use MAC address filtering (limited effectiveness)
- Implement WIDS to detect rogue APs
- Educate users about suspicious networks

### 3. Probe Request Flood

**What it does:**
Floods the air with WiFi probe requests.

**How to use:**
```
1. Select "WiFi Attacks" → "Probe Request Flood"
2. Press SELECT to start
3. Generates rapid probe requests
4. Can stress test access points
5. Press BACK to stop
```

**Legitimate uses:**
- Test AP handling of high probe request rates
- Stress test WiFi infrastructure
- Demonstrate DoS vulnerabilities
- Benchmark AP performance

---

## Bluetooth Scanner

### Purpose
Scan for Bluetooth Low Energy (BLE) devices in the area.

### How to Use

1. **Select "Bluetooth Scanner" from main menu**
2. **Press SELECT to start scan**
3. **Wait 3-5 seconds for scan**
4. **Review detected devices**

**Display Output:**
```
=== Bluetooth Devices ===
Total: 5 devices

1: A4:C1:38:XX:XX:XX
   RSSI: -55 dBm
   Name: iPhone 12
   
2: 00:1A:7D:XX:XX:XX
   RSSI: -72 dBm
   Name: Fitness Tracker
   
3: B8:27:EB:XX:XX:XX
   RSSI: -68 dBm
   Name: Smart Watch
```

### Understanding Results

**Device Information:**
- **MAC Address**: Unique identifier
- **RSSI**: Signal strength (closer = stronger)
- **Name**: Device broadcast name (if available)
- **Services**: Available BLE services (advanced)

### Actions

- **Press SELECT**: Re-scan for devices
- **Press UP/DOWN**: Scroll through results
- **Press BACK**: Return to main menu

### Use Cases

✓ **Legitimate uses:**
- Inventory your own BLE devices
- Check for unauthorized BLE devices nearby
- Test BLE security on your devices
- Locate lost BLE devices

✗ **Illegal uses:**
- Tracking individuals without consent
- Unauthorized device enumeration

### Privacy Note

Many devices randomize MAC addresses for privacy. Repeated scans may show different addresses for the same device.

---

## Packet Monitor

### Purpose
Capture and monitor WiFi packets in promiscuous mode.

### How to Use

1. **Select "Packet Monitor"**
2. **Press SELECT to start monitoring**
3. **Device captures all WiFi packets it can receive**
4. **Counter shows packet count**
5. **Press BACK to stop**

**Display Output:**
```
=== Packet Monitor ===
Capturing...

Packets: 1,247
Rate: 150 pkt/sec
Channel: 6

[BACK] to stop
```

### What It Captures

- **Management frames**: Beacons, probes, auth
- **Control frames**: ACK, RTS, CTS
- **Data frames**: Actual data packets (encrypted)

### Understanding the Data

**Packet count:**
- High rate: Congested area or active network
- Low rate: Quiet area or specific channel
- Fluctuating: Variable network activity

### Use Cases

✓ **Legitimate uses:**
- Monitor your own network traffic levels
- Identify interference sources
- Baseline normal network behavior
- Troubleshoot connectivity issues

### Limitations

- Cannot decrypt WPA2/WPA3 encrypted data (by design)
- Only captures packets within radio range
- May miss packets due to timing
- Encrypted payloads cannot be read

---

## Battery Management

### Charging

**To charge:**
1. Connect USB-C cable
2. Can charge while powered off or on
3. **Red LED**: Currently charging
4. **Yellow LED**: Fully charged
5. Charging time: 2-3 hours (1500mAh battery)

**Charge indicators:**
- Blinking red: Actively charging
- Solid yellow: Charge complete
- No LED: No USB power or battery issue

### Battery Life

**Expected runtime:**
- Idle (display on): 4-6 hours
- WiFi scanning: 3-4 hours
- Active attacks: 2-3 hours
- Bluetooth scanning: 3-5 hours
- Mixed use: 3-4 hours

**Factors affecting battery life:**
- Screen brightness
- WiFi/BT activity
- Attack intensity
- Temperature
- Battery age

### Battery Care

**Best practices:**
- Don't fully discharge regularly
- Store at 50-70% charge if not using for weeks
- Avoid extreme temperatures
- Charge every 2-3 months if stored
- Replace battery if runtime drops significantly

### Low Battery Warning

When battery low:
- Display shows battery icon
- Buzzer beeps periodically
- Device auto-shuts down at ~3.2V
- Save work and charge soon

---

## Tips and Best Practices

### Maximizing Range

**For better WiFi/BT range:**
- Keep antenna area clear
- Hold device upright
- Avoid metal obstacles
- Go to higher ground
- Consider external antenna (if connector present)

### Avoiding Detection

If conducting authorized penetration testing:
- Use attack bursts, not continuous
- Monitor for WIDS alerts
- Coordinate with network admin
- Document all activities
- Have authorization letter ready

### Effective Scanning

**WiFi scanning tips:**
- Scan multiple times for complete results
- Change locations to find all APs
- Note RSSI trends (signal mapping)
- Document findings for reporting

**BLE scanning tips:**
- Stay in one place for consistent results
- Devices may appear/disappear as they sleep
- Note time of day (affects device activity)
- Some devices only advertise when active

### Data Collection

For professional testing:
- Use Serial Monitor for detailed logs
- Copy results to computer
- Take screenshots of display
- Document methodology
- Create comprehensive report

---

## Troubleshooting

### Display Issues

**Display blank:**
- Check power on
- Verify battery charged
- Check display connection
- Try re-seating display

**Display garbled:**
- Reset device
- Re-upload firmware
- Check I2C connections

### WiFi Issues

**No networks found:**
- Verify in area with WiFi
- Check antenna not blocked
- Try different location
- Reset ESP32

**WiFi range poor:**
- Check antenna positioning
- Verify ESP32 antenna area clear
- Consider external antenna
- Check for interference

### Bluetooth Issues

**BLE scan finds nothing:**
- Ensure BLE devices nearby
- Check if devices in pairing mode
- Verify ESP32 BLE working
- Try restart

### Button Issues

**Buttons not responding:**
- Check battery charged
- Verify firmware uploaded
- Test buttons electrically
- Check GPIO connections

### Power Issues

**Device won't turn on:**
- Check battery charged
- Verify power switch on
- Test with USB power
- Check voltage regulator

**Random shutdowns:**
- Battery may be low
- Check for shorts
- Verify stable power
- Temperature too high

---

## Ethical Hacking Guidelines

### The Hacker Ethic

1. **Access to computers should be unlimited and total** - on systems you own/have permission for
2. **All information should be free** - your own data and legally obtained data
3. **Mistrust authority** - but follow the law
4. **Hackers should be judged by their hacking** - not illegal activity
5. **You can create art and beauty on a computer** - creatively and legally

### Professional Conduct

If doing penetration testing:
- **Get written authorization** before any testing
- **Define scope clearly** - what's in/out of bounds
- **Document everything** - actions, findings, timestamps
- **Report responsibly** - disclose to owners before public
- **Provide solutions** - not just problems
- **Respect privacy** - don't access personal data unnecessarily

### Red Flags - DON'T DO THIS

✗ Testing networks without permission
✗ Disrupting services maliciously  
✗ Accessing confidential data
✗ Selling exploits to criminals
✗ Helping others commit crimes
✗ Bragging about unauthorized access

---

## Learning Resources

### WiFi Security
- **Book**: "The Hacker Playbook" by Peter Kim
- **Course**: WiFi Hacking on Udemy
- **Tool**: Wireshark for packet analysis

### Penetration Testing
- **Certification**: CEH (Certified Ethical Hacker)
- **Platform**: HackTheBox for practice
- **Community**: /r/netsec on Reddit

### ESP32 Development
- **Documentation**: ESP32 Arduino Core docs
- **Forum**: ESP32.com community
- **Projects**: Hackster.io ESP32 projects

---

## Advanced Features

### Custom Scripts

Add custom attack patterns:
```cpp
// Edit firmware to add custom functions
void customAttack() {
  // Your custom code here
}
```

### Logging to SD Card

Add SD card module for logging:
- Save scan results
- Log packet captures
- Store attack results
- Export for analysis

### Remote Control

Add WiFi web server:
- Control via smartphone
- View results on laptop
- Remote logging
- No display needed

---

## FAQ

**Q: Is this device legal?**
A: The device itself is legal. Using it on networks without permission is illegal.

**Q: Can it crack WPA2 passwords?**
A: No, this version doesn't include password cracking. It demonstrates vulnerabilities.

**Q: How far does it reach?**
A: WiFi range: ~50-100m typical. BLE: ~10-30m. Depends on environment.

**Q: Can I get in trouble?**
A: Yes, if you use it illegally. Only use on your own networks or with permission.

**Q: Does it work on 5GHz WiFi?**
A: ESP32 supports 2.4GHz only, not 5GHz.

**Q: Can it attack WPA3?**
A: WPA3 has better protection against these attacks. Best used for WPA2 testing.

---

## Support and Community

### Getting Help

- **GitHub Issues**: https://github.com/EfaTheOne/TechBot4/issues
- **Documentation**: All guides in /docs folder
- **Forums**: ESP32 community forums

### Contributing

Found a bug or want to add features?
1. Fork the repository
2. Make improvements
3. Submit pull request
4. Share with community

### Sharing Responsibly

If sharing your findings:
- ✓ Notify network owner first
- ✓ Wait for patch before public disclosure
- ✓ Share educational content
- ✓ Help improve security

---

## Final Words

This device is a powerful tool for learning about wireless security. Use it responsibly, legally, and ethically. 

**Remember:**
- Always get permission
- Never access what's not yours
- Learn to protect, not harm
- Share knowledge freely
- Stay curious and ethical

**Happy (ethical) hacking! 🔐**

---

**Document Version**: 1.0  
**Last Updated**: 2025-01-01  
**Project**: TechBot4 ESP32 Marauder
