# 🔐 Smart EVM (Electronic Voting Machine)

A **Smart and Secure Voting System** using fingerprint recognition to ensure only **genuine voters** cast their vote. Each voter can vote **only once**, and the system can detect **fake or duplicate attempts** using biometric identification.

---

## 💡 Features

- ✅ **Biometric Fingerprint Authentication**
- 🔒 **One Voter, One Vote Enforcement**
- ⚠️ **Fake Vote Detection**
- 📟 **LCD Display for Voter Feedback**
- 🔔 **Buzzer Notification**
- ☁️ **Optional Internet Connectivity** for real-time logging using Wi-Fi/Bluetooth Module
- ⚡ **Current & Voltage Sensors** to monitor power health

---

## 🧰 Components Used

| S.No | Component | Purpose | Estimated Cost (₹) |
|------|-----------|---------|--------------------|
| 1 | **Current Sensor (SCT-013)** | Senses current in the circuit | 225 |
| 2 | **Arduino UNO** | Main controller unit | 1870 |
| 3 | **Wi-Fi/Bluetooth Module** | To send data to the cloud (optional) | 230 |
| 4 | **16x2 LCD Display** | Displays messages to the user | 136 |
| 5 | **Voltage Sensor (ZMPT101B)** | Senses voltage input | 170 |
| 6 | **Breadboard and Wires** | For circuit connections | 270 |
| **Total Estimated Cost** | | | **₹2900** |

---

## 🖥️ How It Works

1. Voter places their finger on the **fingerprint sensor**.
2. System checks the fingerprint against stored templates.
3. If the fingerprint is found and **has not voted before**, the vote is allowed.
4. If the fingerprint is **already voted**, it shows "Already Voted".
5. If the fingerprint is **not found**, it flags as a "Fake ID".
6. A **buzzer** gives feedback on a successful vote.
7. The **LCD display** provides real-time status for user guidance.

---

## 📁 Project Structure

---

## 🚀 Getting Started

### Prerequisites

- Arduino IDE
- Adafruit Fingerprint Library
- LiquidCrystal Library
- SoftwareSerial Library

### Setup

1. Connect all the components as per the schematic.
2. Upload `Smart_EVM.ino` to Arduino UNO.
3. Open Serial Monitor and set baud rate to **9600**.
4. Place registered fingerprints to test.

---

## 🛡️ Security & Integrity

- ✅ Ensures **one person can vote only once** using fingerprint tracking.
- 🚫 Blocks **unauthorized or fake fingerprints**.
- 📡 Optional integration with Wi-Fi/Bluetooth for remote monitoring or logging.

---

## 📷 Preview

# Circuit Diagram
![Circuit Diagram](https://github.com/user-attachments/assets/741efa22-7e8e-4598-ac50-b8141d754c81)
# Overview
![Overview](https://github.com/user-attachments/assets/29df7691-bfd1-4392-b1a9-6f0d1f814cc8)



---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 🙌 Contributing

Feel free to fork this repo and enhance the features:
- Add real-time voting stats display.
- Integrate with cloud-based database.
- Support for more biometric sensors.

---

## 👤 Author

**Himanshu Dhage**  
`Electronics Enthusiast | Developer | Embedded Systems Explorer`

---

## 🌐 Connect with Me

- GitHub: [himanshudhage](https://github.com/himanshudhage)
- LinkedIn: [linkedin.com/in/himanshudhage](https://linkedin.com/in/himanshudhage)

