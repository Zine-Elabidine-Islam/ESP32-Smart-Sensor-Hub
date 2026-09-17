#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>

// --- Pin Definitions ---
#define SDA_PIN 4      // I2C Data
#define SCL_PIN 5      // I2C Clock
#define TrigPin 6      // Ultrasonic Trigger
#define EchoPin 7      // Ultrasonic Echo
#define IRpin 16       // IR Receiver Signal (OUT)
#define Light 17       // Photoresistor Analog Input (ADC)

// --- Object Initialization ---
// Initialize the LCD at I2C address 0x27 with 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  // Configure sensor pins
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  // Initialize I2C communication with custom ESP32-S3 pins
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize the LCD screen and turn on the backlight
  lcd.init();
  lcd.backlight();
  
  // Start the IR receiver
  IrReceiver.begin(IRpin);
}

void loop() {
  // Check if an IR signal has been successfully received
  if (IrReceiver.decode()) {
    int command = IrReceiver.decodedIRData.command;
    
    // Command 0x16 (Button 1): Display Ultrasonic Distance
    if (command == 0x16) { 
      // Trigger the ultrasonic sensor
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      
      // Calculate distance based on the speed of sound
      long duration = pulseIn(EchoPin, HIGH);
      float distanceCm = duration * 0.0343 / 2;
      
      // Update the LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Distance :");
      lcd.setCursor(0, 1); 
      lcd.print(distanceCm);
      lcd.print(" cm");
    }
    
    // Command 0x19 (Button 2): Display Luminosity Percentage
    else if (command == 0x19) {
      // Read the analog value from the photoresistor (0 to 4095 on ESP32-S3)
      int lightLevel = analogRead(Light);
      
      // Convert the 12-bit ADC reading to a percentage (0-100%)
      int lightLevel1 = (lightLevel * 100) / 4095;
      
      // Update the LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Luminosity :");
      lcd.setCursor(0, 1); 
      lcd.print(lightLevel1);
      lcd.print(" %");
    }
    
    // Reset the IR receiver to capture the next button press
    IrReceiver.resume();
  }
}