# ESP32 Access Control System - Build Instructions

## Quick Start

### Prerequisites
```bash
# Install Python 3.x and PlatformIO
pip install platformio

# Verify installation
pio --version
```

### Build & Upload
```bash
# Clone repository
git clone <repository-url>
cd cewmpoi

# Validate project structure
./validate.sh

# Build project (when online)
pio run

# Upload to ESP32
pio run --target upload

# Monitor serial output
pio device monitor --baud 115200
```

### Alternative Build with Make
```bash
# Show all available commands
make help

# Build and flash in one step
make flash

# Just verify project structure
make verify
```

## Network Issues Workaround

If you encounter network issues with PlatformIO platform installation:

1. **Use a different network**: Try mobile hotspot or different internet connection
2. **Manual installation**: Download ESP32 platform manually
3. **Offline development**: Use Arduino IDE as fallback

### Manual Platform Installation
```bash
# Download platform manually (when online)
pio platform install espressif32

# Install libraries manually
pio lib install
```

## Hardware Setup

### Wiring Diagram
```
ESP32 DevKit v1 Pinout:
┌─────────────────────────────────┐
│ 3V3  │ VIN     GPIO21 │ GPIO22 │ ← I2C (SDA/SCL)
│ GND  │ GND     GPIO19 │ GPIO23 │ ← SPI (MISO/MOSI)
│ GPIO15│ GPIO13  GPIO18 │ GPIO5  │ ← SPI (SCK/SS1)
│ GPIO2│ GPIO12  GPIO17 │ GPIO16 │ ← RFID (RST1/RST2)
│ GPIO0│ GPIO14  GPIO4  │ GPIO0  │ ← SS2
│ GPIO4│ GPIO27  GPIO26 │ GPIO25 │ ← US/Buzzer
│ GPIO16│ GPIO26  GPIO33 │ GPIO32 │ ← Relays
└─────────────────────────────────┘
```

### Connection List
| Component | Pin | ESP32 GPIO |
|-----------|-----|------------|
| LCD SDA   | SDA | 21         |
| LCD SCL   | SCL | 22         |
| OLED SDA  | SDA | 21         |
| OLED SCL  | SCL | 22         |
| RC522-1 SS| SS  | 5          |
| RC522-1 RST| RST| 17         |
| RC522-2 SS| SS  | 4          |
| RC522-2 RST| RST| 16         |
| SPI SCK   | SCK | 18         |
| SPI MISO  | MISO| 19         |
| SPI MOSI  | MOSI| 23         |
| HC-SR04 TRIG| TRIG| 26       |
| HC-SR04 ECHO| ECHO| 27       |
| Buzzer    | SIG | 25         |
| Relay 1   | IN  | 32         |
| Relay 2   | IN  | 33         |

## Troubleshooting

### Common Issues

1. **"HTTPClientError" during build**
   - Solution: Check internet connection, try different network
   - Workaround: Use `make build` after manual platform installation

2. **"Platform not installed"**
   - Solution: `pio platform install espressif32`
   - Check: `pio platform list --installed`

3. **Upload fails**
   - Check: ESP32 connected via USB
   - Check: Correct COM port selected
   - Try: Press BOOT button during upload

4. **I2C devices not working**
   - Verify: SDA/SCL connections (GPIO 21/22)
   - Check: I2C addresses (LCD: 0x27, OLED: 0x3C)
   - Test: Use I2C scanner sketch

5. **RFID not detected**
   - Verify: SPI wiring (SCK: 18, MISO: 19, MOSI: 23)
   - Check: SS and RST pin connections
   - Test: Individual RFID modules

### Debug Mode
Enable verbose debugging by modifying `config.h`:
```cpp
#define DEBUG_LEVEL 2  // 0=none, 1=basic, 2=verbose
```

### Memory Issues
If you encounter memory problems:
```cpp
// In config.h, reduce buffer sizes
#define UID_ENTRY_SIZE 16  // Reduce from 24
```

## Development

### Adding New Features
1. Create header file in `include/`
2. Create implementation in `src/`
3. Add include to `main.cpp`
4. Update `README.md` documentation

### Code Style
- Use camelCase for methods
- Use PascalCase for classes
- Comment all public methods
- Include error handling

### Testing
- Use `validate.sh` for quick checks
- Test on actual hardware before committing
- Verify all features work independently

## Support

For issues or questions:
1. Check this documentation first
2. Run `validate.sh` to verify setup
3. Check serial output for debug info
4. Open GitHub issue with full error details

## License

This project is open source. See LICENSE file for details.