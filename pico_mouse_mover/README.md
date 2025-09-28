# Pico Mouse Mover

A natural mouse movement simulator for Raspberry Pi Pico that prevents computers from going to sleep by creating realistic mouse movements.

## 📋 Overview

This project turns a Raspberry Pi Pico into a USB HID mouse device that automatically generates natural-looking mouse movements. Unlike traditional "mouse jigglers" that create repetitive patterns, this implementation uses randomized movements and timing to simulate human-like cursor activity.

## ✨ Features

- **Natural Movement Patterns**: Random X/Y movements (-15 to +15 pixels) instead of fixed directions
- **Smart Timing**: 5-second cycles with random active periods (1-3 seconds)
- **Variable Intervals**: Individual movements occur every 50-200ms during active periods
- **Rest Periods**: 2-4 seconds of inactivity between movement cycles
- **Plug & Play**: Works as a standard USB HID mouse on any operating system
- **No Software Required**: No drivers or software installation needed on target computers

## 🛠 Hardware Requirements

- Raspberry Pi Pico (or Pico W)
- USB cable (micro USB to USB-A or USB-C depending on your computer)

## 🔧 Software Requirements

- [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) (version 1.5.0 or later)
- CMake (3.13 or later)
- GCC ARM toolchain
- Git

## 📦 Installation & Setup

### 1. Install Pico SDK

#### On macOS:
```bash
# Install dependencies
brew install cmake
brew install --cask gcc-arm-embedded

# Clone and setup Pico SDK
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=/path/to/pico-sdk
```

#### On Linux (Ubuntu/Debian):
```bash
# Install dependencies
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential

# Clone and setup Pico SDK
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=/path/to/pico-sdk
```

###On Windows:
Follow the official Pico SDK installation guide


2. Clone This Repository
bashgit clone https://github.com/yourusername/pico-mouse-mover.git
cd pico-mouse-mover


## 🔨 Building the Project
1. Create Build Directory
bashmkdir build
cd build
2. Configure CMake
bashcmake ..
3. Build the Project
bashmake -j4
This will generate:

pico_mouse_mover.uf2 - Firmware file for direct upload
pico_mouse_mover.elf - ELF executable
pico_mouse_mover.bin - Binary file
pico_mouse_mover.hex - Intel HEX file

## 📤 Flashing the Firmware
Method 1: UF2 Bootloader (Recommended)

Hold the BOOTSEL button on your Pico while plugging it into your computer
The Pico will appear as a USB mass storage device named "RPI-RP2"
Copy pico_mouse_mover.uf2 to the RPI-RP2 drive
The Pico will automatically reboot and start running the mouse mover

Method 2: Using Picotool
bash# Put Pico in bootloader mode, then:
picotool load pico_mouse_mover.uf2
picotool reboot
## 🚀 Usage

Flash the firmware to your Pico using the steps above
Plug the Pico into any computer via USB
The device will be recognized as a standard USB mouse
Natural mouse movements will begin automatically after a few seconds

Movement Pattern

Cycle Duration: 5 seconds
Active Period: 1-3 seconds (random)
Rest Period: 2-4 seconds
Movement Range: ±15 pixels in X/Y directions
Movement Frequency: Every 50-200ms during active periods

🙏 Acknowledgments

Built using TinyUSB library
Based on Raspberry Pi Pico SDK examples

Note: This device is intended for legitimate use cases such as preventing screen savers or maintaining system activity during presentations. Please use responsibly and in accordance with your organization's IT policies.