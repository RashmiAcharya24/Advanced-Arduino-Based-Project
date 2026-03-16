#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h> 

Adafruit_LiquidCrystal lcd(0x27);  // Use your actual I2C address
Servo myservo;

// Ultrasonic sensor pins
const int entryTrigPin = 5;
const int entryEchoPin = 6;
const int exitTrigPin = 7;
const int exitEchoPin = 8;
const int DISTANCE_THRESHOLD = 130; // Distance in centimeters

int Slot = 2;           // Total parking slots
int flag1 = 0;
int flag2 = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);      // Initialize LCD
  lcd.setBacklight(1);   // Permanent backlight ON
  
  // Ultrasonic sensor setup
  pinMode(entryTrigPin, OUTPUT);
  pinMode(entryEchoPin, INPUT);
  pinMode(exitTrigPin, OUTPUT);
  pinMode(exitEchoPin, INPUT);

  myservo.attach(4);
  myservo.write(100);

  // Initial display message
  lcd.print(" SMART PARKING ");
  delay(2000);
  lcd.clear();
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration * 0.034 / 2; // Convert to cm
}

void loop() { 
  long entryDistance = measureDistance(entryTrigPin, entryEchoPin);
  long exitDistance = measureDistance(exitTrigPin, exitEchoPin);

  // Entry sensor logic
  if(entryDistance > 0 && entryDistance <= DISTANCE_THRESHOLD && flag1 == 0) {
    if(Slot > 0) {
      flag1 = 1;
      if(flag2 == 0) {
        myservo.write(0);
        Slot--;
      }
    } else {
      lcd.clear();
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  "); 
      delay(3000);
      lcd.clear(); 
    }
  }

  // Exit sensor logic
  if(exitDistance > 0 && exitDistance <= DISTANCE_THRESHOLD && flag2 == 0) {
    flag2 = 1;
    if(flag1 == 0) {
      myservo.write(0);
      Slot++;
    }
  }

  // Reset mechanism
  if(flag1 == 1 && flag2 == 1) {
    // delay(500);
    myservo.write(100);
    flag1 = 0;
    flag2 = 0;
  }

  // Update display
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
  
  delay(200);
}
