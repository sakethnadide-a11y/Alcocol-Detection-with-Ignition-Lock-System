
# Alcohol Detection and Ignition Lock System

An Arduino-based alcohol detection system designed to prevent vehicle operation when alcohol is detected beyond a predefined threshold. The system uses an MQ-3 alcohol sensor, Arduino, and an L298N motor driver to detect alcohol levels, trigger alerts, and gradually stop a DC motor.

## Hardware Prototype

![Alcohol Detection System](images/hardware-prototype.jpg)

## Project Overview

The system continuously monitors alcohol levels using the MQ-3 sensor. When the detected alcohol value reaches or exceeds the configured threshold, the system triggers an alert and gradually reduces the motor speed to zero.

The motor remains stopped even if the alcohol reading subsequently falls below the threshold, until the system is reset.

## Key Features

- Real-time alcohol detection using MQ-3 sensor.
- Automatic motor speed control using L298N.
- Gradual motor shutdown when alcohol is detected.
- Audible warning through a buzzer.
- LCD display for alcohol readings and motor speed.
- SMS alert functionality using SIM808 GSM module.
- Persistent alcohol detection state until reset.

## Components Used

| Component | Purpose |
|---|---|
| Arduino | Main controller |
| MQ-3 Sensor | Alcohol detection |
| L298N Motor Driver | Motor speed control |
| DC Motor | Simulates vehicle engine |
| I2C Display | Displays sensor readings |
| Buzzer | Audio alert |
| SIM808 Module | SMS notifications |

## Pin Configuration

| Component | Arduino Pin |
|---|---|
| MQ-3 Sensor | A0 |
| L298N ENA | 5 |
| L298N IN1 | 7 |
| L298N IN2 | 8 |
| Buzzer | 13 |
| SIM808 RX | 10 |
| SIM808 TX | 11 |
| LCD SDA | SDA |
| LCD SCL | SCL |

## Working Principle

1. The MQ-3 sensor continuously monitors alcohol levels.
2. Arduino reads the sensor's analog output.
3. The sensor value is compared against a predefined threshold of 500.
4. If the threshold is exceeded:
   - The buzzer activates for 10 seconds.
   - Motor speed gradually decreases from 255 to 0.
   - An SMS alert is initiated through the SIM808 module.
   - The display updates the alcohol reading and motor speed.
5. The motor remains stopped until the system is reset.

## Software and Technologies

- Arduino C/C++
- Arduino IDE
- U8g2 Library
- SoftwareSerial
- DFRobot SIM808 Library
- Embedded Systems
- PWM Motor Control

## Repository Structure

```text
Alcohol-Detection-System/
│
├── README.md
├── images/
│   └── hardware-prototype.jpg
│
└── src/
    └── alcohol_detection.ino
```

## How to Run

1. Install Arduino IDE.
2. Install the required libraries:
   - U8g2
   - DFRobot SIM808
3. Connect the hardware according to the pin configuration.
4. Open `src/alcohol_detection.ino`.
5. Select the appropriate Arduino board and COM port.
6. Upload the program.
7. Open Serial Monitor at 9600 baud.

## Future Improvements

- Improve alcohol sensor calibration.
- Implement non-blocking motor control.
- Add GPS-based vehicle location tracking.
- Improve GSM communication and SMS delivery verification.
- Develop a more robust fault detection and reset mechanism.

## Safety Disclaimer

This project is an educational prototype intended for demonstration using a low-voltage DC motor. It is not a certified automotive safety system or ignition interlock and must not be connected to or used to control a real vehicle.

## Author

Developed as an Embedded Systems and IoT project.
