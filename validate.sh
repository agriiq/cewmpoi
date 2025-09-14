#!/bin/bash
# Build validation script for ESP32 Access Control System

echo "=== ESP32 Access Control System Build Validation ==="
echo

# Check project structure
echo "1. Checking project structure..."
required_files=(
    "platformio.ini"
    "src/main.cpp"
    "include/config.h"
    "Makefile"
    "README.md"
)

for file in "${required_files[@]}"; do
    if [ -f "$file" ]; then
        echo "   ✓ $file"
    else
        echo "   ✗ $file (missing)"
        exit 1
    fi
done

echo "   Project structure OK"
echo

# Check source files
echo "2. Checking source files..."
src_files=$(find src -name "*.cpp" | wc -l)
header_files=$(find include -name "*.h" | wc -l)

echo "   Source files: $src_files"
echo "   Header files: $header_files"

# Check for common issues
echo
echo "3. Checking for common issues..."

# Check for missing includes
echo "   Checking includes..."
grep -n "#include" src/*.cpp | grep -v "Arduino.h" | grep -v "config.h" > /tmp/includes.txt
if [ -s /tmp/includes.txt ]; then
    echo "   ✓ Library includes found"
else
    echo "   ⚠ Warning: Few library includes found"
fi

# Check for DEBUG_SERIAL usage without config.h
echo "   Checking DEBUG_SERIAL usage..."
for file in src/*.cpp; do
    if grep -q "DEBUG_SERIAL" "$file" && ! grep -q "#include.*config.h" "$file"; then
        echo "   ⚠ Warning: $file uses DEBUG_SERIAL but doesn't include config.h"
    fi
done

# Check for Wire.begin() in main.cpp
echo "   Checking I2C initialization..."
if grep -q "Wire.begin" src/main.cpp; then
    echo "   ✓ I2C initialized in main.cpp"
else
    echo "   ⚠ Warning: I2C might not be initialized"
fi

echo
echo "4. PlatformIO configuration check..."
if pio --version > /dev/null 2>&1; then
    echo "   ✓ PlatformIO installed"
    echo "   Platform: $(grep "^platform" platformio.ini | cut -d'=' -f2 | tr -d ' ')"
    echo "   Board: $(grep "^board" platformio.ini | cut -d'=' -f2 | tr -d ' ')"
    echo "   Framework: $(grep "^framework" platformio.ini | cut -d'=' -f2 | tr -d ' ')"
else
    echo "   ✗ PlatformIO not installed or not in PATH"
fi

echo
echo "=== Validation Complete ==="
echo "Ready for build with: pio run"