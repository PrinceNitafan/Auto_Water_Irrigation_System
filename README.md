# Arduino Automated Water Irrigation System

An automated plant watering project built with an Arduino Uno, capacitive soil moisture sensors, and a 4-channel relay module.

## How It Works

Each `IrrigationZone` pairs one soil moisture sensor (`A0`-`A3`) with one relay pin (`2`-`5`):

1. Every second (`CHECK_INTERVAL_MS`), the Arduino reads each sensor three times and averages the result to smooth out minor fluctuations.
2. On the v1.2 capacitive moisture sensor, higher analog numbers mean drier soil.
3. When the moisture reading rises above `DRY_THRESHOLD` (`425`), the relay turns the pump on (`LOW` for active-low relay boards).
4. Once the reading drops to or below `WET_THRESHOLD` (`380`), the pump turns back off (`HIGH`). Having separate start and stop values stops the relay from rapidly clicking on and off when the soil moisture is right around `425`.

## Project Structure

```text
Auto_Water_Irrigation_System/
├── include/
│   ├── Config.h            # Pin numbers, thresholds, and timing constants
│   └── IrrigationZone.h    # IrrigationZone class definition
├── src/
│   ├── IrrigationZone.cpp  # Sensor reading and relay control logic
│   └── main.cpp            # Arduino setup() and loop()
└── platformio.ini          # PlatformIO configuration (multi and single environments)
```

## Equipment

1. Arduino Uno R3 (with USB cable)
2. Capacitive Soil Moisture Sensors v1.2 (1 to 4)
3. 5V 4-Channel Relay Module
4. Mini 5V submersible water pumps + vinyl tubing
5. External 5V power supply or battery pack for the pumps
6. Breadboard and jumper wires (male-to-male, male-to-female)

## Pin Connections

| Zone | Sensor Pin (`AOUT`) | Relay Pin | Power | Ground |
| :--- | :--- | :--- | :--- | :--- |
| Zone 1 | `A0` | Digital `2` (`IN1`) | `5V` | `GND` |
| Zone 2 | `A1` | Digital `3` (`IN2`) | `5V` | `GND` |
| Zone 3 | `A2` | Digital `4` (`IN3`) | `5V` | `GND` |
| Zone 4 | `A3` | Digital `5` (`IN4`) | `5V` | `GND` |

Note: Power the water pumps from an external 5V battery pack or power supply through the relay contacts rather than directly from the Arduino's `5V` pin so multiple pumps running at once do not overload the USB port.

## Configuration

Thresholds and pins can be adjusted in [`include/Config.h`]:

- `NUM_ZONES`: Number of active zones (`4` by default, or `1` when using the `single` build environment)
- `DRY_THRESHOLD`: `425` (pump turns on above this value)
- `WET_THRESHOLD`: `380` (pump turns off at or below this value)
- `CHECK_INTERVAL_MS`: `1000` (time in milliseconds between sensor checks)

## Building and Uploading

Using VS Code with the PlatformIO extension (or PlatformIO CLI):

```bash
# Build and upload for all 4 pumps (default)
pio run -e multi --target upload

# Build and upload for 1 pump (Zone 1 on A0 and pin 2)
pio run -e single --target upload

# Open the Serial Monitor (115200 baud)
pio device monitor
```
