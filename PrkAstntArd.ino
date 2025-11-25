// Smart Parking Assistant

#include <Adafruit_LiquidCrystal.h>

// Pin Definitions
const int pingPin = 7;        
const int greenLED = 10;      
const int yellowLED = 9;      
const int redLED = 8;         
const int buzzerPin = 6;      

// LCD Setup 
Adafruit_LiquidCrystal lcd_1(0);

// Distance Thresholds (in cm)
const int safeDistance = 100;    // > 100cm = safe
const int cautionDistance = 50;  // 50-100cm = caution
const int warningDistance = 20;  // 20-50cm = warning
                                 // < 20cm = stop

// Buzzer timing
unsigned long previousMillis = 0;
bool buzzerState = false;

void setup() {
  // Initialize LED pins
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize I2C LCD
  lcd_1.begin(16, 2);
  lcd_1.setBacklight(1);
  
  // Initialize Serial Monitor 
  Serial.begin(9600);
  
  // Startup message
  lcd_1.setCursor(0, 0);
  lcd_1.print("Parking Assist");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Starting...");
  delay(2000);
  lcd_1.clear();
}

void loop() {
  // Get distance from PING sensor
  long distance = getDistance();
  
  // Print to Serial Monitor 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  //  zone and control outputs
  if (distance > safeDistance) {
    // Zone 1: Safe Distance
    updateLEDs(1);
    updateBuzzer(1, 0);
    updateLCD(distance, "Safe Distance");
    
  } else if (distance > cautionDistance) {
    // Zone 2: Caution
    updateLEDs(2);
    updateBuzzer(2, 500);  // Slow beeps 
    updateLCD(distance, "Slow Down");
    
  } else if (distance > warningDistance) {
    // Zone 3: Warning
    updateLEDs(3);
    updateBuzzer(3, 200);  // Fast beeps 
    updateLCD(distance, "Warning!");
    
  } else {
    // Zone 4: Stop
    updateLEDs(4);
    updateBuzzer(4, 0);    // Constant beeps
    updateLCD(distance, "STOP!");
  }
  
  delay(100);  
}

// Function to get distance from PING sensor
long getDistance() {
  long duration, cm;
  
  // Send trigger pulse
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  //  echo pulse
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  // Convert to centimeters
  cm = duration / 29 / 2;
  
  return cm;
}

// Function to control LEDs based on zone
void updateLEDs(int zone) {
  // Turn off all LEDs Initially
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  
  // Turn on appropriate LED
  switch(zone) {
    case 1:  // Safe
      digitalWrite(greenLED, HIGH);
      break;
    case 2:  // Caution
      digitalWrite(yellowLED, HIGH);
      break;
    case 3:  // Warning
    case 4:  // Stop
      digitalWrite(redLED, HIGH);
      break;
  }
}

// Function to control buzzer with non-blocking timing
void updateBuzzer(int zone, int interval) {
  unsigned long currentMillis = millis();
  
  if (zone == 1) {
    // Zone 1: No buzzer
    noTone(buzzerPin);
    buzzerState = false;
    
  } else if (zone == 4) {
    // Zone 4: Constant tone
    tone(buzzerPin, 1000);  
    
  } else {
    // Zone 2 & 3: Beeping pattern
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      buzzerState = !buzzerState;
      
      if (buzzerState) {
        tone(buzzerPin, 800);  
      } else {
        noTone(buzzerPin);
      }
    }
  }
}

// Function to update LCD display
void updateLCD(long distance, String message) {
  lcd_1.clear();
  
  // Line 1: Distance
  lcd_1.setCursor(0, 0);
  lcd_1.print("Dist: ");
  lcd_1.print(distance);
  lcd_1.print(" cm");
  
  // Line 2: Status message
  lcd_1.setCursor(0, 1);
  lcd_1.print(message);
}