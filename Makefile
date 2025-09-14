# ESP32 Access Control System Makefile
# Alternative build system when PlatformIO has issues

.PHONY: build check clean install help setup test

# Default target
help:
	@echo "ESP32 Access Control System Build Commands:"
	@echo ""
	@echo "  make build     - Build the project using PlatformIO"
	@echo "  make check     - Run static analysis"
	@echo "  make clean     - Clean build artifacts"
	@echo "  make install   - Install dependencies"
	@echo "  make setup     - Full setup (install platform + libs)"
	@echo "  make upload    - Upload to ESP32 device"
	@echo "  make monitor   - Monitor serial output"
	@echo "  make flash     - Build, upload and monitor"
	@echo "  make test      - Run syntax and structure tests"
	@echo ""
	@echo "Requirements:"
	@echo "  - PlatformIO Core installed (pip install platformio)"
	@echo "  - ESP32 connected via USB"

# Install PlatformIO if not present
install:
	@command -v pio >/dev/null 2>&1 || { echo "Installing PlatformIO..."; pip install platformio; }
	@echo "PlatformIO installation check complete"

# Verify project structure
verify:
	@echo "Checking project structure..."
	@test -f platformio.ini || { echo "ERROR: platformio.ini missing"; exit 1; }
	@test -d src || { echo "ERROR: src directory missing"; exit 1; }
	@test -d include || { echo "ERROR: include directory missing"; exit 1; }
	@test -f src/main.cpp || { echo "ERROR: main.cpp missing"; exit 1; }
	@echo "Project structure OK"

# Run validation script
test: verify
	@echo "Running validation tests..."
	@./validate.sh

# Build the project
build: install verify
	@echo "Building project..."
	@pio run || { echo "Build failed. Check BUILD.md for troubleshooting."; exit 1; }

# Check code quality  
check: install
	@echo "Running static analysis..."
	@pio check || echo "Static analysis completed with warnings"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@pio run --target clean

# Upload to ESP32
upload: build
	@echo "Uploading to ESP32..."
	@pio run --target upload || { echo "Upload failed. Check ESP32 connection."; exit 1; }

# Monitor serial output
monitor:
	@echo "Starting serial monitor (115200 baud)..."
	@echo "Press Ctrl+C to exit"
	@pio device monitor --baud 115200

# Build and upload in one step
flash: upload
	@echo "Starting monitor after upload..."
	@$(MAKE) monitor

# Install platform dependencies (when online)
setup: install verify
	@echo "Installing ESP32 platform..."
	@pio platform install espressif32 || echo "Platform installation failed - check network"
	@echo "Installing libraries..."
	@pio lib install || echo "Library installation failed - check network"
	@echo "Setup complete"

# Development helpers
dev-setup: setup
	@echo "Setting up development environment..."
	@chmod +x validate.sh
	@echo "Development setup complete"