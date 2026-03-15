# 🪖 Smart Helmet-Based Road Safety Data Collection System

![IoT](https://img.shields.io/badge/Domain-IoT-blue)
![ESP32](https://img.shields.io/badge/Hardware-ESP32-green)
![ThingsBoard](https://img.shields.io/badge/Cloud-ThingsBoard-purple)
![HTTP](https://img.shields.io/badge/Protocol-HTTP%20API-orange)
![Wokwi](https://img.shields.io/badge/Simulation-Wokwi-yellow)

An IoT system that monitors riding behaviour and road conditions in real time using motion sensor data — transmitting telemetry to ThingsBoard via HTTP API for dashboard visualization and event detection.

---

## 📖 Overview

This project captures acceleration and gyroscope data from an **MPU6050 sensor** via an **ESP32 microcontroller** while riding. Sensor readings are converted to real-world units (g for acceleration, °/s for gyroscope) and transmitted over WiFi to **ThingsBoard Cloud** using its **HTTP Telemetry API** every 2 seconds.

Riding events — hard braking, sudden acceleration, sharp turns, and potholes — are detected on-device using threshold logic and sent as binary flags alongside the raw sensor data.

---

## 🏗️ System Architecture

```
MPU6050 Sensor  (I2C)
      ↓
ESP32 Microcontroller
  ├── Sensor reading & unit conversion
  ├── On-device event detection
  └── JSON payload assembly
      ↓
WiFi — HTTP POST (every 2 seconds)
      ↓
ThingsBoard Cloud (eu.thingsboard.cloud)
      ↓
Dashboard Visualization
```

---

## 🔧 Hardware Components

| Component | Description |
|-----------|-------------|
| **ESP32** | Microcontroller with built-in WiFi |
| **MPU6050** | 3-axis accelerometer + 3-axis gyroscope (IMU), connected via I2C |
| **Jumper Wires** | I2C connections (SDA/SCL) between sensor and ESP32 |
| **Breadboard** | Prototyping and circuit setup |

---

## 🛠️ Software & Tools

| Tool | Purpose |
|------|---------|
| Arduino Framework | ESP32 firmware programming |
| `MPU6050` Library | Sensor initialization and data reading |
| `WiFi.h` / `HTTPClient.h` | WiFi connection and HTTP POST requests |
| VS Code | Development environment |
| ThingsBoard Cloud | IoT cloud platform, HTTP API endpoint, and dashboard |
| Wokwi Simulator | Hardware simulation — no physical device required |
| GitHub | Version control and project hosting |

---

## ✨ Features

- **Real-time sensor data collection** from MPU6050 at 2-second intervals
- **Unit conversion** — raw ADC values converted to g (accelerometer) and °/s (gyroscope)
- **On-device event detection** using threshold-based logic:
  - Hard braking (`acc_y < -1.8g`)
  - Sudden acceleration (`acc_y > 1.8g`)
  - Sharp turn (`|gyro_z| > 150 °/s`)
  - Pothole / road bump (`acc_z > 1.8g`)
- **HTTP POST telemetry** to ThingsBoard Cloud every 2 seconds
- **ThingsBoard dashboard** with time-series charts and event widgets
- **Wokwi simulation support** — fully testable without physical hardware

---

## 📡 Telemetry Data

Sensor data is sent as a JSON payload via HTTP POST to the ThingsBoard Telemetry API. Temperature is intentionally excluded as it is not relevant to road safety analysis.

| Key | Description | Unit |
|-----|-------------|------|
| `acc_x` | Acceleration along X-axis | g |
| `acc_y` | Acceleration along Y-axis | g |
| `acc_z` | Acceleration along Z-axis | g |
| `gyro_x` | Angular rotation along X-axis | °/s |
| `gyro_y` | Angular rotation along Y-axis | °/s |
| `gyro_z` | Angular rotation along Z-axis | °/s |
| `hard_brake` | Hard braking detected (0 or 1) | binary |
| `sudden_acceleration` | Sudden acceleration detected (0 or 1) | binary |
| `sharp_turn` | Sharp turn detected (0 or 1) | binary |
| `pothole` | Pothole / road bump detected (0 or 1) | binary |

**Example payload:**
```json
{
  "acc_x": 0.02,
  "acc_y": -1.95,
  "acc_z": 0.98,
  "gyro_x": 1.2,
  "gyro_y": -0.8,
  "gyro_z": 162.4,
  "hard_brake": 1,
  "sudden_acceleration": 0,
  "sharp_turn": 1,
  "pothole": 0
}
```

---

## 📊 Dashboard

The ThingsBoard dashboard includes **four widgets**:

1. **Accelerometer Chart** — Time-series visualization of `acc_x`, `acc_y`, `acc_z`
2. **Gyroscope Chart** — Time-series visualization of `gyro_x`, `gyro_y`, `gyro_z`
3. **Total Acceleration** — Real-time combined magnitude display
4. **Event Detection Panel** — Live flags for hard brakes, sudden acceleration, sharp turns, and potholes

---

## 🖥️ Simulation

Physical hardware is **not required** to test this project.

The **Wokwi IoT Simulator** replicates ESP32 + MPU6050 behaviour and uses `Wokwi-GUEST` as the WiFi SSID (no password needed). Adjust the simulated sensor sliders in Wokwi to trigger different event thresholds and verify HTTP response codes in the Serial Monitor.

> Wokwi Project: *(add your Wokwi project link here)*

---

## 🚀 Getting Started

1. Clone this repository
   ```bash
   git clone https://github.com/<your-username>/smart-helmet-road-safety.git
   ```
2. Open the project in VS Code (Arduino framework)
3. Install the `MPU6050` library via Arduino Library Manager
4. Update `serverName` in the code with your ThingsBoard device access token:
   ```cpp
   String serverName = "http://eu.thingsboard.cloud/api/v1/<YOUR_ACCESS_TOKEN>/telemetry";
   ```
5. For simulation: open in [Wokwi](https://wokwi.com) — WiFi connects automatically via `Wokwi-GUEST`
6. Flash to your ESP32 or run the simulation and watch the Serial Monitor for HTTP response codes

---

## 🗺️ Roadmap

- [ ] GPS integration for real-time location tagging
- [ ] Accident detection and emergency alert system
- [ ] Push notifications to rider via mobile app
- [ ] Mobile application for live monitoring
- [ ] Data analytics pipeline for road safety insights

---

## 👤 Author

**Priyank Jain**  
IoT Course Project — Smart Helmet Road Safety System

---

## 📄 License

This project is developed for academic purposes as part of an IoT course project.
