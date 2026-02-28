# Arduino Brick Breaker Game

A classic **Brick Breaker / Breakout game** for Arduino UNO with a **0.96" I2C OLED display** and **joystick control**.
Play through multiple levels with bricks shrinking and increasing difficulty!  

---

## 🎮 Features

- Smooth paddle movement using an analog joystick
- Ball physics with wall, paddle, and brick collision
- Progressive levels (up to 15) with shrinking bricks
- Score tracking
- Continuous gameplay (no lives/game over required)
- Memory-efficient design for Arduino UNO (2KB RAM)
- 0.96" 128x64 I2C OLED support

---

## 🛠 Hardware Required

- **Arduino UNO**
- **0.96" I2C OLED display** (SSD1306, 128x64)
- **Analog Joystick Module** (with push button)
- Jumper wires and breadboard

---

## 📌 Wiring Guide

| OLED Pin | Arduino UNO |
|-----------|-------------|
| VCC       | 5V          |
| GND       | GND         |
| SDA       | A4          |
| SCL       | A5          |

| Joystick Pin | Arduino UNO |
|--------------|-------------|
| VRx          | A0          |
| SW (button)  | D2 (Digital Pin) |
| GND          | GND         |
| VCC          | 5V          |

---

## 🎛 Controls

- **Move Paddle:** Tilt joystick left/right  
- **Launch Ball:** Press joystick button  

---

## 🏗 Installation

### 1. Arduino IDE

- Make sure you have the **latest Arduino IDE** installed: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

### 2. Install Required Libraries

- **Adafruit SSD1306**  
- **Adafruit GFX**  

Use **Library Manager** in Arduino IDE:
Sketch → Include Library → Manage Libraries → Search "Adafruit SSD1306" → Install
Sketch → Include Library → Manage Libraries → Search "Adafruit GFX" → Install

### 3. Upload Code

1. Download `BrickBreaker.ino` from this repository.
2. Open in Arduino IDE.
3. Select **Board → Arduino UNO**.
4. Select correct **Port**.
5. Upload to Arduino.

---

## 💾 GitHub Releases

For easier use, you can download the pre-packaged **release ZIP**:

1. Go to the **Releases** tab on GitHub:  
   (https://github.com/Siddharthvrm/Arduino_brick_breaker/releases/tag/Brick_breaker)
2. Download the latest `BrickBreaker.zip`.
3. Extract and open `BrickBreaker.ino` in Arduino IDE.
4. Upload to your UNO.

---

## 📊 Gameplay

- Ball resets automatically when missed — no lives required  
- Bricks shrink as levels increase  
- Levels loop after 15 for endless fun  
- Score increments by **10 points per brick**  

---

## ⚡ Notes

- Only tested on **Arduino UNO** and **0.96" 128x64 I2C OLED**
- Power via USB recommended
- Ensure I2C address matches OLED (usually `0x3C`)  

---

## 🌐 Try It Online

You can **play and test the Arduino Brick Breaker game online** without hardware using Wokwi:  

[Check it online](https://wokwi.com/projects/457216639815523329)

---

## 📝 License

This project is open-source under **MIT License**. Feel free to fork, modify, and share!

---

## ⭐ Credits

Created by **[Siddharth Verma]**  
Inspired by classic Brick Breaker / Breakout games.
