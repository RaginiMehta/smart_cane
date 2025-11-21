# Multi-Sensor Safety Alert System

## Introduction
This project is a multi-sensor safety alert system designed to detect obstacles, collisions, and low-light conditions, providing both audible and visual alerts. The system is built using an Arduino and combines an ultrasonic sensor, a vibration sensor, and an LDR (light-dependent resistor) with a buzzer and LED for feedback. It can be used for personal safety, robotics, or vehicle proximity alerts.

---

## First Prototype

![First Prototype](stick.jpeg)

The first prototype utilized **only the ultrasonic sensor** to measure distances.  
The buzzer was programmed to beep **more frequently as objects got closer**, providing graded warnings based on proximity.  
This prototype used the script `final.ino` and served as the foundation for the expanded multi-sensor system.  

Key features of the first prototype:

- Measures distance using HC-SR04 ultrasonic sensor  
- Buzzer pattern changes depending on distance:
  - ≤ 70 cm → slow beep  
  - ≤ 50 cm → faster beep  
  - ≤ 15 cm → continuous beep  

---

## Other Sensors Considered

### SW-420 Vibration Sensor
- Purpose: Detect collisions or sudden shocks  
- Reason not fully integrated in final prototype: The vibration sensor sometimes gave false positives and needed additional debouncing logic.  

### LDR (Light-Dependent Resistor)
- Purpose: Detect low-light conditions to turn on a precaution LED  
- Reason not fully integrated in final prototype: While it worked, the LED functionality was optional and not critical for the main safety alerts, so it was left for future expansion.  

---

## Materials Required

- Arduino Uno (or compatible)  
- HC-SR04 Ultrasonic Sensor  
- SW-420 Vibration Sensor (optional)  
- LDR (Light Sensor) (optional)  
- Active Buzzer  
- LED (for low-light warning, optional)  
- Resistors (10kΩ for LDR voltage divider)  
- Jumper wires and breadboard  
- USB cable for programming Arduino  

---

## Circuit Diagram

![Circuit Diagram]()


*(A proper schematic image can be added here.)*

---

## How It Works

1. **Distance Detection**:  
   The ultrasonic sensor measures the distance to obstacles and triggers graded buzzer alerts based on proximity.

2. **Collision Detection** (optional):  
   The SW-420 sensor detects vibrations or collisions and sounds the buzzer for 2 seconds.

3. **Low-Light Detection** (optional):  
   The LDR detects darkness, turning on an LED to warn the user in low-light conditions.

---

## Notes

- The project is modular; additional sensors can be integrated as needed.  
- Debouncing or filtering may be required for vibration and LDR sensors for more stable readings.  
- The buzzer patterns and distance thresholds can be adjusted in the code to suit your application.  

---

## Files

- `final.ino` – Main Arduino sketch for the first prototype and foundation of the multi-sensor system.  

---

## License

This project is open-source and can be freely modified for educational or personal use.
