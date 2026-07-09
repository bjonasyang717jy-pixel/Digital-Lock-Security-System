# 🔐 Digital Lock Security System

An embedded password-based access control system developed using the **STC89C52 (8051) Microcontroller**. The project integrates an IR sensor, keypad, LCD display, LEDs, buzzer, timer interrupts, and finite state machine (FSM) logic to provide secure user authentication and real-time system monitoring.

---

## 📌 Project Overview

This project was developed for the **NDJ20403 Microcontroller System** course at Universiti Malaysia Perlis (UniMAP).

The system provides a complete embedded access control solution that authenticates users through password verification while incorporating multiple security mechanisms, including limited login attempts, administrator recovery, timeout protection, and intrusion alarms.

Unlike a basic password lock, this project demonstrates the integration of multiple embedded system concepts including peripheral control, interrupt programming, finite state machine (FSM) design, and hardware-software integration.

---

## 🎯 Objectives

- Design a password-based digital lock using the STC89C52 (8051) microcontroller.
- Implement secure authentication with limited login attempts.
- Integrate multiple hardware peripherals into a single embedded system.
- Apply timer interrupts for timeout monitoring.
- Improve embedded system design and programming skills.

---

## ✨ Key Features

- Password authentication
- IR sensor automatic wake-up
- LCD status display (I2C)
- Door open counter
- Three-attempt security lock
- Administrator reset mode
- Intruder alarm
- Timeout detection
- LED status indicators
- Timer0 interrupt
- Finite State Machine (FSM)

---

## 🛠 Hardware Components

| Component | Function |
|-----------|----------|
| STC89C52 | Main microcontroller |
| 5×4 Matrix Keypad | Password input |
| IR Sensor | User detection |
| 16×2 LCD (I2C) | User interface |
| Green LED | Access granted |
| Yellow LED | Incorrect password |
| Red LED | System locked |
| Purple LED | System active |
| Buzzer | Security alarm |

---

## 💻 Development Tools

- Embedded C
- Keil μVision
- STC-ISP
- 8051 Architecture

---

## ⚙ System Workflow

```text
Standby
    │
IR Sensor Detects User
    │
Enter Password
    │
 ┌──────────────┐
 │Correct?      │
 └──────┬───────┘
        │
   Yes  │ No
        │
Access  Attempts++
Granted │
        │
        ▼
Three Failed Attempts
        │
System Locked
        │
Administrator Reset
```

---

## 📂 Repository Structure

```text
Digital-Lock-Security-System
│
├── Code/
├── Circuit/
├── Documentation/
├── Images/
├── README.md
```

---

## 📊 System States

| State | Description |
|-------|-------------|
| Standby | Waiting for user detection |
| Active | Password entry |
| Access Granted | Green LED ON |
| Access Denied | Yellow LED ON |
| Locked | Red LED + Buzzer |
| Admin Mode | Administrator authentication |
| Timeout | Return to standby |

---

## 🚀 Future Improvements

- RFID authentication
- Fingerprint recognition
- Bluetooth control
- EEPROM password storage
- WiFi / IoT monitoring
- Mobile application
- Event logging

---

## 📚 Skills Demonstrated

- Embedded Systems
- 8051 Microcontroller
- Embedded C
- Finite State Machine (FSM)
- Timer Interrupt
- LCD (I2C)
- Matrix Keypad
- Hardware Integration
- Circuit Debugging
- Electronic System Design

---

## 👨‍💻 Author

**Jonas Chin Jie Yang**

Diploma in Electronic Engineering

Universiti Malaysia Perlis (UniMAP)
bjonasyang717.jy@gmail.com

LinkedIn:
https://linkedin.com/in/jonaschinjieyang

---

## 📄 License

This project is intended for educational purposes.
