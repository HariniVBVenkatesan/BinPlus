# BinPlus

# BinPulse — IoT-Based Smart Waste Management System

An IoT-based smart waste monitoring system that measures dustbin fill levels and waste weight using an ESP32 and sensors. BinPulse integrates sensor monitoring, threshold-based alerts, and a Supabase-connected dashboard to support smarter and more efficient waste collection.

## 📌 Project Overview

BinPulse aims to improve waste management by monitoring dustbin capacity and identifying bins that may require collection.

The system uses two sensing methods:
- **Ultrasonic sensing:** Estimates the dustbin fill percentage by measuring the distance between the sensor and the waste surface.
- **Weight sensing:** Measures the collected waste weight using a load cell connected through an HX711 amplifier.

Sensor readings are processed by the ESP32 to determine the bin status and trigger alerts. The data is connected to a dashboard through Supabase for remote monitoring.

## 🎯 Objectives

- Monitor dustbin fill levels in real time.
- Measure the weight of collected waste.
- Classify bin status using predefined thresholds.
- Provide visual and audible alerts for different bin conditions.
- Store and display sensor data through Supabase and a dashboard.
- Support more efficient waste collection and overflow prevention.

## 🛠️ Hardware Components

| Component | Purpose |
|---|---|
| ESP32 Dev Module | Microcontroller for sensor processing and Wi-Fi connectivity |
| HC-SR04 Ultrasonic Sensor | Measures the distance to the waste surface |
| Load Cell | Measures the waste weight |
| HX711 Amplifier | Amplifies and converts load-cell measurements |
| Green LED | Indicates a low-fill or normal condition |
| Yellow LED | Indicates a warning condition |
| Red LED | Indicates a full or overflow condition |
| Buzzer | Provides audible alerts |
| Power Supply | Powers the prototype |

## 💻 Software and Technologies

- **Programming:** Arduino C++
- **Microcontroller Platform:** ESP32
- **Cloud Database:** Supabase
- **Dashboard:** Project dashboard connected to Supabase
- **Communication:** Wi-Fi
- **Development Environment:** Arduino IDE

## ⚙️ How It Works

1. The HC-SR04 ultrasonic sensor measures the distance between the sensor and the waste surface.
2. The ESP32 uses the measured distance and configured bin height to calculate the estimated fill percentage.
3. The load cell and HX711 measure the weight of the waste.
4. The ESP32 processes both readings using predefined thresholds.
5. The system classifies the bin status and determines alert priority.
6. LEDs and the buzzer provide visual and audible indications.
7. Sensor data is sent to Supabase and displayed on the connected dashboard for remote monitoring.

## 📊 Bin Status Classification

The system uses threshold-based logic to classify the bin condition.

| Fill Percentage | Status |
|---|---|
| Below 50% | Empty / Low Fill |
| 50% to below 80% | Half Full |
| 80% to below 100% | Full |
| 100% | Overflow |

*Note: The labels and exact boundary conditions should match the thresholds implemented in the Arduino code.*

## 🚨 Alert Logic

The system evaluates fill level and weight to determine alert priority.

- **Low Priority:** Bin conditions remain below the configured warning thresholds.
- **Medium Priority:** The bin reaches a configured fill or weight threshold.
- **High Priority:** The bin reaches a high fill level together with a high waste weight.

LED indicators and the buzzer communicate the detected condition locally.

## ☁️ Supabase Dashboard Integration

Supabase provides the cloud database layer for storing sensor readings and making them available to the dashboard.

The dashboard can be used to display information such as:
- Bin fill percentage
- Waste weight
- Current bin status
- Alert priority
- Latest sensor readings

The exact data fields and dashboard features depend on the implemented database schema and application.

## 🔌 Hardware Connections

The following pin assignments were used in the prototype:

| Component | ESP32 Pin |
|---|---|
| HC-SR04 TRIG | GPIO 5 |
| HC-SR04 ECHO | GPIO 18 |
| HX711 DT | GPIO 4 |
| HX711 SCK | GPIO 2 |
| Buzzer | GPIO 15 |
| Green LED | GPIO 25 |
| Yellow LED | GPIO 26 |
| Red LED | GPIO 27 |


## 👩‍💻 Project Information

**Project Name:** BinPulse  
**Domain:** Internet of Things (IoT), Embedded Systems, Smart Waste Management  
**Hardware:** ESP32, HC-SR04, Load Cell, HX711  
**Cloud:** Supabase  
**Dashboard:** Connected monitoring dashboard
