# ESP32-Smart-Sensor-Hub

An embedded systems project demonstrating custom I2C routing, ADC light sensing, and IR remote integration on the ESP32-S3. It uses an IR remote to seamlessly toggle an I2C LCD screen between displaying physical distance and ambient light levels.

## Features
* **Ultrasonic Ranging:** Uses an HC-SR04 sensor to calculate distance in centimeters.
* **Light Detection:** Reads a photoresistor (LDR) using the ESP32-S3's 12-bit ADC and maps the voltage to a 0-100% luminosity scale.
* **IR Remote Control:** Uses standard NEC IR commands to switch the active sensor display.
* **Custom I2C Routing:** Demonstrates remapping standard hardware I2C pins to custom GPIOs on the ESP32-S3.

## Hardware Requirements
* **Microcontroller:** ESP32-S3 Development Board
* **Display:** 16x2 LCD with I2C Backpack (Address: `0x27`)
* **Sensors:** 
  * HC-SR04 Ultrasonic Distance Sensor
  * Photoresistor (LDR) with a 10kΩ pull-down resistor (Voltage Divider)
* **Input:** IR Receiver Module (e.g., VS1838B) and a standard IR Remote

## Wiring & Pin Mapping

| Component | ESP32-S3 Pin | Notes |
| :--- | :--- | :--- |
| **I2C LCD SDA** | GPIO 4 | Custom I2C Data pin |
| **I2C LCD SCL** | GPIO 5 | Custom I2C Clock pin |
| **HC-SR04 Trig** | GPIO 6 | Digital Output |
| **HC-SR04 Echo** | GPIO 7 | Digital Input |
| **IR Receiver OUT** | GPIO 16 | Digital Input |
| **Photoresistor** | GPIO 17 | Analog Input (ADC, 0-4095 range) |

> **Warning:** Ensure the HC-SR04 and I2C LCD are powered with 5V if required by your specific modules, while the IR receiver and LDR voltage divider should be tied to 3.3V logic to protect the ESP32-S3 GPIO pins.

## Dependencies
This project requires the following libraries. Install them via the Arduino IDE Library Manager:
* `LiquidCrystal I2C` by Frank de Brabander
* `IRremote` by shirriff, z3t0, ArminJo (Version 3.0 or higher)

## Usage
1. Clone this repository and open the `.ino` file in the Arduino IDE.
2. Install the required dependencies.
3. Compile and flash the code to your ESP32-S3.
4. Aim your IR remote at the receiver.
5. Press **Button 1** (Hex code `0x16`) to display the live distance reading.
6. Press **Button 2** (Hex code `0x19`) to display the live room luminosity as a percentage. 

*(If using a different IR remote, open the Serial Monitor at 115200 baud, press your desired buttons to find their unique hex codes, and update the `0x16` and `0x19` values in the `loop()` function).*

## Author
**Lakhlef Zine Elabidine Islam (Zinou)**  
Autonomous Systems Engineering Student, National Higher School Of Autonomous Systems Technology
