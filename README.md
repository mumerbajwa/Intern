# Smart Home Device Manager

## 📝 Project Overview

This is a **console-based C++ simulation** of a smart home system. The program allows users to manage different types of smart devices (like Lights, Thermostats, and Security Cameras) in different rooms. It uses object-oriented programming concepts and a simple Factory design pattern.

---

## ✅ Features Implemented

### 1. Object-Oriented Design
- **Base Class**: `SmartDevice` with common properties: `name`, `location`, and `isOn`
- **Methods**: `turnOn()`, `turnOff()`, `showStatus()`, `getType()`
- **Subclasses**:
  - `Light`: Schedulable device
  - `Thermostat`: Can set temperature and schedule
  - `SecurityCamera`: Can start recording

---

### 2. Interface (Abstract Class)
- `Schedulable` interface with methods `scheduleOn(time)` and `scheduleOff(time)`
- Implemented in:
  - `Light`
  - `Thermostat`

---

### 3. Aggregation & Composition
- **Room** class contains:
  - Multiple lights, thermostats, and cameras
  - Methods to add devices, turn all devices on, schedule them, and show their status
- **SmartHomeController** class manages multiple rooms

---

### 4. Menu-Driven System
- Add a new room
- Add a device to a room (based on type input)
- Show all devices and their status
- Turn all devices ON in a room
- Schedule devices in a room

---

### 5. Factory Pattern
- `DeviceFactory::create()` creates and returns the correct device (`Light`, `Thermostat`, or `Camera`) based on string input.

---

## 🛠️ How to Run
1. Save the code to `main.cpp`
2. Compile using g++:
   ```bash
   g++ -o SmartHome main.cpp
