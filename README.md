# Autonomous Survival Robot

An Arduino-based survival robot designed for **battlefield** and **rescue missions**, capable of avoiding obstacles, pits, fire, and extreme temperatures.  
The robot can be controlled manually via **RF remote** or operate semi-autonomously using its distributed sensor architecture.

---

## 🎯 Project Overview
This project demonstrates how a robot can **survive and navigate hazardous environments** by combining multiple microcontrollers, sensors, and communication protocols.

- **Hazard Detection:**
  - Obstacles & pits → proximity sensors
  - Fire & high temperatures → flame & temperature sensors
- **Control:**
  - RF remote control by the user
  - Central Arduino Mega processes sensor data and commands the motors
- **Architecture:** Distributed system using I2C communication
- **Feedback:** LCD display shows system status, battery voltage, and current consumption

---

## 🛠 Components
- Arduino Mega (main controller)
- Arduino Pro Mini (sub-controllers)
- RF communication module
- Proximity sensors
- Flame & temperature sensors
- Motor drivers + DC motors
- LCD display
- LiPo battery (11.1V)
