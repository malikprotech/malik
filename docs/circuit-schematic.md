# Industrial 5-Color Separator Circuit Schematic

## Arduino Uno Pin Map

| Component | Pin | Arduino Pin |
|---|---:|---:|
| TCS3200 S0 | Digital | D11 |
| TCS3200 S1 | Digital | D12 |
| TCS3200 S2 | Analog | A0 |
| TCS3200 S3 | Analog | A1 |
| TCS3200 OUT | Digital | D2 |
| TCS3200 LED | Digital | D4 |
| Servo 1 | Digital PWM | D3 |
| Servo 2 | Digital PWM | D5 |
| Servo 3 | Digital PWM | D6 |
| Servo 4 | Digital PWM | D9 |
| Servo 5 | Digital PWM | D10 |

## Schematic

```text
                   +----------------------------------------------+
                   |                 Arduino Uno                  |
                   |                                              |
          +--------+ D11  S0 ---------------------+             |
          |        |                             |             |
   TCS3200 S0 ---+                             +-- 5V --------+
          |        |                             |             |
          |        | D12  S1 ---------------------+             |
          |        |                             |             |
          |        | A0   S2 ---------------------+             |
          |        |                             |             |
          |        | A1   S3 ---------------------+             |
          |        |                             |             |
          |        | D2   OUT --------------------+             |
          |        |                             |             |
          |        | D4   LED --------------------+             |
          |        |                             |             |
          |        +---------------------------------+             |
          |
          |                 +--------------------+
          +-----------------+   TCS3200 Sensor   +
                            +--------------------+

    Servo 1 D3 ---+   Servo 2 D5 ---+   Servo 3 D6 ---+   Servo 4 D9 ---+   Servo 5 D10 ---+
        |               |               |               |               |               |
        +---------------+---------------+---------------+---------------+---------------+
                               Sorting Gates / Chutes
```

## Power Layout

```text
12V DC Supply ---------+-------------------------+-------------------------+
                       |                         |                         |
                  Servo Power Rail          5V Regulator         Arduino VIN
                       |                         |
                  +------------+            +----------+
                  | 1000uF     |            | 5V rail |
                  | capacitor  |            +----------+
                  +------------+

Arduino GND ---------+------------------------+----------------------+
                     |                        |
                Sensor GND                 Servo GND
```

## Conveyor and Sorting Layout

```text
Object Feed --> Sensor Zone --> Servo-Based Diverter --> Bin 1 / Bin 2 / Bin 3 / Bin 4 / Bin 5
                               |
                         Arduino Control
```

## Notes
- Keep sensor wiring short and shielded from servo noise.
- Use separate power sources for motors and logic if possible.
- Add a common ground between Arduino and sensors.
- For industrial environments, use an opto-coupled relay or MOSFET driver for actuators.
