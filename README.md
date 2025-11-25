# Smart Parking Assistant 🚗 AI written description (mostly)

An Arduino-based parking assistance system that helps drivers park safely by providing real-time distance feedback through visual and audio alerts.

## Overview

This project uses an ultrasonic sensor to measure the distance to obstacles and provides intuitive feedback through LEDs, a buzzer, and an LCD display - similar to modern car parking sensors.

## Features

- 📏 **Real-time Distance Measurement** - PING ultrasonic sensor accurately measures distance to obstacles
- 🚦 **Visual Indicators** - Three LEDs (Green/Yellow/Red) show proximity levels
- 🔊 **Audio Alerts** - Buzzer with variable beep patterns based on distance
- 📺 **LCD Display** - Shows exact distance and status messages
- ⚡ **4 Distance Zones** - Safe, Caution, Warning, and Stop alerts

## Components Required

- Arduino Uno
- PING Ultrasonic Sensor
- 16x2 I2C LCD Display (Adafruit)
- 3x LEDs (Green, Yellow, Red)
- 3x 220Ω Resistors
- Piezo Buzzer
- Breadboard
- Jumper Wires


## Circuit Diagram
[Arduino-CrDiagram.png]
### Pin Connections:
**PING Sensor:**
- SIG → Pin 7
- VCC → 5V
- GND → GND

**LEDs (with 220Ω resistors):**
- Green LED → Pin 10
- Yellow LED → Pin 9
- Red LED → Pin 8

**Buzzer:**
- Positive → Pin 6
- Negative → GND

**I2C LCD:**
- SDA → A4
- SCL → A5
- VCC → 5V
- GND → GND

## CODE
[PrkAstntArd.ino]

## How It Works

The system operates in **4 distance zones**:

| Distance | LED | Buzzer | LCD Message | Action |
|----------|-----|--------|-------------|--------|
| > 100cm | Green | Silent | "Safe Distance" | Continue |
| 50-100cm | Yellow | Slow beeps (500ms) | "Slow Down" | Reduce speed |
| 20-50cm | Red | Fast beeps (200ms) | "Warning!" | Stop soon |
| < 20cm | Red | Constant tone | "STOP!" | Stop immediately |
| It resets automatically if the distance is closer than 2cm|


## Installation & Setup
### For TinkerCAD:
1. Create new circuit in TinkerCAD
2. Add all components as listed above
3. Wire according to pin connections
4. Copy code into code editor
5. Start simulation

### For Physical Arduino:
1. Wire components according to circuit diagram
2. Install required library: `Adafruit_LiquidCrystal`
3. Upload code to Arduino Uno
4. Open Serial Monitor (9600 baud) for debugging


## Usage

1. Power on the Arduino
2. LCD displays "Parking Assist - Starting..."
3. Position sensor facing the obstacle
4. Move vehicle/object closer to see zones activate
5. Follow LED and buzzer alerts to park safely

## Real-World Applications
- Home garage parking assistance
- Warehouse vehicle guidance



## Troubleshooting
**LCD not displaying:**
- Check I2C connections (SDA/SCL to A4/A5)
- Verify library is `Adafruit_LiquidCrystal`

**LEDs not lighting:**
- Verify 220Ω resistors are installed
- Check LED polarity (long leg = positive)



**Note:** This project was developed and tested in TinkerCAD Arduino Simulator.
