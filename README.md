# TechBot4 - ESP32 Marauder Pen Testing Device

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![WiFi](https://img.shields.io/badge/WiFi-0078D4?style=for-the-badge&logo=wifi&logoColor=white)
![Bluetooth](https://img.shields.io/badge/Bluetooth-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)

**A phone-sized WiFi and Bluetooth pen testing device based on ESP32**

*Educational purposes only - Use responsibly and legally*

</div>

---

## 📋 Overview

TechBot4 is an ESP32-based pen testing device that functions like the popular ESP32 Marauder. It's designed as a phone-sized, portable device with a custom PCB that's easy to build and use.

### Features

- 🔍 **WiFi Network Scanning** - Discover and analyze WiFi networks
- ⚡ **WiFi Security Testing** - Deauth attacks, beacon spam, probe flooding
- 📡 **Bluetooth Scanner** - Detect nearby BLE devices
- 📊 **Packet Monitor** - Capture and analyze WiFi packets
- 🔋 **Battery Powered** - Built-in LiPo battery with USB-C charging
- 📱 **Phone-Like Form Factor** - Compact 80mm x 150mm design
- 🖥️ **OLED Display** - 128x64 display for menu navigation
- 🎮 **Button Controls** - Four tactile buttons for easy navigation
- 🔊 **Audio Feedback** - Buzzer for operation feedback

---

## ⚠️ Legal Disclaimer

**IMPORTANT:** This device is for **EDUCATIONAL AND AUTHORIZED TESTING ONLY**.

- ✅ Use on your own networks
- ✅ Use with written authorization from network owner
- ✅ Use in controlled test environments
- ❌ **DO NOT** use on networks without permission
- ❌ **DO NOT** use for malicious purposes

**Unauthorized access to computer networks is illegal and may result in criminal prosecution.**

By building and using this device, you agree to use it legally and ethically.

---

## 🚀 Quick Start

### What You Need

1. **Hardware Components** (see [BOM.md](docs/BOM.md))
   - ESP32-WROOM-32 module
   - Custom PCB (or breadboard)
   - Supporting components
   - 3.7V LiPo battery
   - Total cost: ~$20-30

2. **Tools**
   - Soldering iron
   - USB-C cable
   - Computer with Arduino IDE

3. **Software**
   - Arduino IDE 2.x
   - ESP32 board support
   - Required libraries (WiFi, BLE)

### Build Process

```
1. Order PCB         → See docs/PCB_Fabrication_Guide.md
2. Gather parts      → See docs/BOM.md
3. Assemble PCB      → See docs/Assembly_Guide.md
4. Flash firmware    → See docs/Firmware_Guide.md
5. Start testing     → See docs/Usage_Guide.md
```

**Estimated build time:** 4-6 hours  
**Difficulty:** Intermediate (SMD soldering required)

---

## 📁 Repository Structure

```
TechBot4/
├── firmware/               # ESP32 Arduino firmware
│   └── TechBot4_Marauder.ino
├── hardware/              # PCB design files
│   ├── pcb/              # PCB layout and design
│   └── schematics/       # Circuit schematics
├── docs/                 # Comprehensive documentation
│   ├── BOM.md           # Bill of Materials
│   ├── PCB_Fabrication_Guide.md
│   ├── Assembly_Guide.md
│   ├── Firmware_Guide.md
│   └── Usage_Guide.md
└── README.md            # This file
```

---

## 📚 Documentation

Complete step-by-step guides are available:

| Document | Description |
|----------|-------------|
| [BOM.md](docs/BOM.md) | Complete parts list with prices and sources |
| [PCB_Fabrication_Guide.md](docs/PCB_Fabrication_Guide.md) | How to order PCBs from manufacturers |
| [Assembly_Guide.md](docs/Assembly_Guide.md) | Step-by-step assembly instructions |
| [Firmware_Guide.md](docs/Firmware_Guide.md) | Firmware installation and configuration |
| [Usage_Guide.md](docs/Usage_Guide.md) | How to use all features safely and legally |

---

## 🔧 Hardware Specifications

### Main Components

- **MCU:** ESP32-WROOM-32 (WiFi + Bluetooth)
- **Display:** 0.96" OLED 128x64 (I2C)
- **Battery:** 3.7V LiPo (1000-2000mAh)
- **Charging:** TP4056 with USB-C
- **Voltage:** AMS1117-3.3 regulator
- **Communication:** CP2102 USB-UART bridge

### PCB Specifications

- **Size:** 80mm x 150mm (phone-sized)
- **Layers:** 2-layer PCB
- **Thickness:** 1.6mm
- **Color:** Black solder mask (recommended)
- **Components:** Mix of SMD and through-hole

### Features

- 4x tactile buttons (UP, DOWN, SELECT, BACK)
- 1x power switch
- 3x status LEDs
- 1x passive buzzer
- Battery charging indicator
- Compact phone-like design

---

## 💻 Software Capabilities

### WiFi Functions

- **Network Scanner**
  - Scan 2.4GHz networks
  - Display SSID, RSSI, channel, security
  - Identify hidden networks
  
- **Deauth Attack**
  - Test network resilience
  - Demonstrate 802.11 vulnerabilities
  - Educational demonstration
  
- **Beacon Spam**
  - Create fake access points
  - Test WIDS systems
  - Security awareness training
  
- **Probe Flood**
  - Stress test access points
  - DoS demonstration
  - Performance testing

### Bluetooth Functions

- **BLE Scanner**
  - Discover BLE devices
  - Display MAC addresses
  - Show device names and RSSI
  - Service enumeration

### Monitoring

- **Packet Monitor**
  - Promiscuous mode capture
  - Real-time packet counting
  - Traffic analysis
  - Frame type identification

---

## 🛠️ Building Your Device

### Option 1: Custom PCB (Recommended)

**Pros:** Professional, compact, reliable  
**Difficulty:** Intermediate  
**Cost:** ~$30 total

1. Generate Gerber files from design
2. Order PCB from JLCPCB/PCBWay (~$2 for 5 boards)
3. Order components from AliExpress/LCSC (~$20)
4. Solder components following assembly guide
5. Flash firmware and test

### Option 2: Breadboard Prototype

**Pros:** Easy, no PCB needed, great for learning  
**Difficulty:** Beginner  
**Cost:** ~$15

1. Get ESP32 development board
2. Connect display via I2C
3. Add buttons with pull-up resistors
4. Wire up on breadboard
5. Flash firmware and test

**Wiring diagram for breadboard version available in docs.**

---

## 📖 Usage Example

### Basic WiFi Scan

```
1. Power on device
2. Navigate to "WiFi Scanner"
3. Press SELECT
4. Wait for scan (3-5 seconds)
5. Review detected networks
6. Press BACK to return
```

### Authorized Pen Test

```
1. Obtain written authorization
2. Document network details
3. Select appropriate test (e.g., Deauth)
4. Run test and monitor results
5. Document findings
6. Report to network owner
7. Provide remediation recommendations
```

---

## 🎓 Educational Use

This project is ideal for:

- **Cybersecurity Students** - Learn wireless security concepts
- **Network Administrators** - Test your own infrastructure
- **Penetration Testers** - Demonstrate vulnerabilities to clients
- **Researchers** - Study WiFi/BLE protocols
- **Makers** - Learn ESP32 and embedded systems

### Learning Objectives

- Understand WiFi 802.11 protocol
- Learn about deauthentication vulnerabilities
- Explore Bluetooth Low Energy
- Practice responsible disclosure
- Develop embedded programming skills
- Learn PCB design (if making custom board)

---

## 🤝 Contributing

Contributions welcome! Please:

1. Fork the repository
2. Create feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open Pull Request

**Areas for contribution:**
- Additional attack modules
- UI improvements
- Documentation enhancements
- Bug fixes
- Hardware design improvements

---

## 🐛 Troubleshooting

### Common Issues

**Device won't power on:**
- Check battery charged
- Verify power switch position
- Test with USB power

**WiFi scan finds nothing:**
- Verify antenna not blocked
- Check ESP32 installed correctly
- Try in area with known WiFi

**Firmware upload fails:**
- Install CP210x drivers
- Try manual boot mode (hold BOOT, press RESET)
- Check USB cable (must support data)

**Display blank:**
- Verify I2C connections
- Check display power (3.3V)
- Try I2C scanner sketch

For more troubleshooting, see the documentation guides.

---

## 📜 License

This project is provided for educational purposes. 

**Usage Terms:**
- Free for personal educational use
- Free for authorized security testing
- Attribution required for derivative works
- Commercial use requires permission
- No warranty provided

**You are responsible for complying with all applicable laws in your jurisdiction.**

---

## 🙏 Credits

### Inspiration

- **ESP32 Marauder** - Original concept by justcallmekoko
- **ESP32 Community** - Extensive documentation and libraries
- **Arduino Project** - Development platform

### Technologies Used

- ESP32-WROOM-32 by Espressif
- Arduino framework
- ESP32 Arduino Core
- Various open-source libraries

---

## 📞 Support

### Getting Help

- **Issues:** [GitHub Issues](https://github.com/EfaTheOne/TechBot4/issues)
- **Documentation:** See `/docs` folder
- **Community:** ESP32 forums and Arduino community

### Reporting Bugs

Please include:
- Hardware version
- Firmware version
- Steps to reproduce
- Expected vs actual behavior
- Serial monitor output

---

## 🔐 Security & Privacy

### Responsible Use

- Always get permission before testing
- Respect privacy and data protection laws
- Don't capture or access personal data
- Report vulnerabilities responsibly
- Use for defense, not offense

### If You Find a Vulnerability

1. Do NOT exploit it
2. Document the vulnerability
3. Contact the affected party privately
4. Allow time for patching
5. Disclose responsibly

---

## 🌟 Star History

If you find this project useful, please give it a ⭐!

---

## 📝 Changelog

### Version 1.0 (2025-01-01)
- Initial release
- WiFi scanning and attacks
- Bluetooth scanning
- Packet monitoring
- Custom PCB design
- Complete documentation

---

## 🔮 Future Enhancements

Planned features:
- [ ] SD card logging
- [ ] Web interface for control
- [ ] GPS logging of scans
- [ ] WPA handshake capture
- [ ] Additional BLE attacks
- [ ] Improved UI with menus
- [ ] Save/load configurations
- [ ] OTA firmware updates
- [ ] 3D printed case design

---

## 📧 Contact

**Project Maintainer:** EfaTheOne  
**Repository:** [TechBot4](https://github.com/EfaTheOne/TechBot4)

---

<div align="center">

**Built with ❤️ for the security and maker communities**

*Remember: With great power comes great responsibility*

**Use ethically. Use legally. Use wisely.**

</div>
