# Industrial 5-Color Object Separator with Arduino Uno

This project demonstrates a low-cost industrial color sorting system for 5 object colors using an Arduino Uno, a TCS3200/TCS34725 color sensor, and five sorting gates driven by servos.

## Features
- Detects five object colors: Red, Green, Blue, Yellow, White
- Uses Arduino Uno as the main controller
- Motorized sorting using 5 servo-controlled chutes
- Simple calibration and threshold system
- Suitable for prototype industrial sorting lines

## Hardware List
- Arduino Uno
- TCS3200 color sensor (or TCS34725 if preferred)
- 5x SG90 / MG996R servos
- 5 sorting bins or collection trays
- 12V DC power supply for servos
- 5V regulator for Arduino and sensors
- NPN transistor or MOSFET for relay-driven actuator control (optional)
- Breadboard or PCB
- Jumper wires

## Block Diagram

```text
Objects -> Conveyor Belt -> Color Sensor -> Arduino Uno -> Servo Gate Logic -> Bin 1..5
                                 |
                                 +-> Calibration / Thresholds
```

## Circuit Connections

### Sensor (TCS3200)
- VCC -> 5V
- GND -> GND
- OUT -> D2
- S0 -> D11
- S1 -> D12
- S2 -> A0
- S3 -> A1
- LED -> D4

### Servos
- Servo 1 -> D3
- Servo 2 -> D5
- Servo 3 -> D6
- Servo 4 -> D9
- Servo 5 -> D10

### Power Notes
- Connect Arduino 5V and sensor 5V to common 5V rail
- Use separate 5V/12V rails for servo power to reduce electrical noise
- Add 1000uF electrolytic capacitor near servo supply

## Sorting Logic

The sensor reads red, green, and blue values from the object. The Arduino compares the values against calibrated thresholds and assigns the object to one of 5 bins.

Example color map:
- Red -> Bin 1
- Green -> Bin 2
- Blue -> Bin 3
- Yellow -> Bin 4
- White -> Bin 5

## Code
The Arduino sketch is in:
- `industrial_5_color_separator.ino`

## Schematic (ASCII)

```text
                         +----------------------+
                         |      Arduino Uno     |
                         +----------------------+
                               |        |        |
                +--------------+        |        +--------------+
                |                       |                       |
          +---------+                +---------+                 +---------+
          | TCS3200 |                | Servo 1 |                 | Servo 2 |
          +---------+                +---------+                 +---------+
              | S0/S1/S2/S3/OUT            |                            |
              |                           |                            |
              +---------------------------+----------------------------+
                                      |
                              +---------+
                              | 5V/GND |
                              +---------+

    Servo 3   Servo 4   Servo 5
      |         |         |
      +---------+---------+
              |
          Sorting bins
```

## Calibration
1. Place each target color sample under the sensor.
2. Read the RGB raw values from Serial Monitor.
3. Update the threshold values in the code.
4. Repeat until detection is stable.

## Example Thresholds
Use the serial monitor to tune these values:
```cpp
const int RED_LOW = 30;
const int RED_HIGH = 110;
const int GREEN_LOW = 28;
const int GREEN_HIGH = 100;
const int BLUE_LOW = 25;
const int BLUE_HIGH = 95;
```

## Notes
- This version is designed for educational and prototype industrial sorting demonstration.
- For production use, consider using industrial conveyor sensors, PLC integration, and more robust actuators.
- Use opto-isolation and proper EMC layout for noisy factory environments.

## License
This project is provided for educational and prototype development use.
