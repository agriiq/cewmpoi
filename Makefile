# ESP32 Access Control System Makefile
# Alternative build system when PlatformIO has issues

.PHONY: build check clean install help

# Default target
help:
	@echo "ESP32 Access Control System Build Commands:"
	@echo ""
	@echo "  make build     - Build the project using PlatformIO"
	@echo "  make check     - Run static analysis"
	@echo "  make clean     - Clean build artifacts"
	@echo "  make install   - Install dependencies"
	@echo "  make upload    - Upload to ESP32 device"
	@echo "  make monitor   - Monitor serial output"
	@echo ""
	@echo "Requirements:"
	@echo "  - PlatformIO Core installed (pip install platformio)"
	@echo "  - ESP32 connected via USB"

# Install PlatformIO if not present
install:
	@command -v pio >/dev/null 2>&1 || { echo "Installing PlatformIO..."; pip install platformio; }
	@echo "PlatformIO installation check complete"

# Build the project
build: install
	pio run

# Check code quality
check: install
	pio check

# Clean build artifacts
clean:
	pio run --target clean

# Upload to ESP32
upload: build
	pio run --target upload

# Monitor serial output
monitor:
	pio device monitor --baud 115200

# Build and upload in one step
flash: upload monitor

# Verify project structure
verify:
	@echo "Checking project structure..."
	@test -f platformio.ini || { echo "ERROR: platformio.ini missing"; exit 1; }
	@test -d src || { echo "ERROR: src directory missing"; exit 1; }
	@test -d include || { echo "ERROR: include directory missing"; exit 1; }
	@test -f src/main.cpp || { echo "ERROR: main.cpp missing"; exit 1; }
	@echo "Project structure OK"

# Install platform dependencies (when online)
setup: install
	pio platform install espressif32
	pio lib install