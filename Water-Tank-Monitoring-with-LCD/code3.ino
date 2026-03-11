/*
  Ping))) Sensor
 
  This sketch reads a PING))) ultrasonic
  rangefinder and returns the distance to the
  closest object in range. To do this, it sends a
  pulse to the sensor to initiate a reading, then
  listens for a pulse to return.  The length of
  the returning pulse is proportional to the
  distance of the object from the sensor.
 
  The circuit:
   * +V connection of the PING))) attached to +5V
   * GND connection attached to ground
   * SIG connection attached to digital pin 7
 
  http://www.arduino.cc/en/Tutorial/Ping
 
  This example code is in the public domain.
*/
#include <LiquidCrystal.h>
#include <EEPROM.h>
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
#define menuBtn  	 A4
#define plusBtn   	 8
#define minusBtn  	 9
#define saveBtn  	 6
#define motorPin 	 A5
 
#define homePage     0
#define menuPage     1
 
uint8_t page = homePage;
uint8_t getLevelFlag = 0;
uint8_t tank_size = EEPROM.read(0);
int inches = 0;
int cm = 0;
float feet = 0;
uint8_t waterLevel = 0;
 
void openHomePage();
void openMenuPage();
void displayTankSize();
 
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
 
void setup()
{
  pinMode(menuBtn, INPUT);
  pinMode(plusBtn, INPUT);
  pinMode(minusBtn, INPUT);
  pinMode(saveBtn, INPUT);
  
  pinMode(motorPin, OUTPUT);
  
  digitalWrite(menuBtn, HIGH); 
  digitalWrite(plusBtn, HIGH); 
  digitalWrite(minusBtn, HIGH); 
  digitalWrite(saveBtn, HIGH); 
    
  
  pinMode(7, INPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Management");
  lcd.setCursor(5, 1);
  lcd.print("System");
  delay(1000);
  openHomePage();
}
 
void loop()
{  
  if(page == homePage && getLevelFlag == 1){
    cm = 0.01723 * readUltrasonicDistance(7, 7);
    // convert to inches by dividing by 2.54
    inches = (cm / 2.54);
    feet = inches/12;
    if(feet > tank_size) feet = tank_size;
   	waterLevel = ((tank_size - feet)/tank_size)*100;
    Serial.println(waterLevel);
    if(waterLevel < 0) waterLevel = 0;
    if(waterLevel > 100) waterLevel = 100;
    
    lcd.setCursor(6, 1);
    
    if(waterLevel < 10){
     lcd.print("  ");
     lcd.setCursor(8, 1);
    }
    else if(waterLevel < 100){
    lcd.print(" ");
    lcd.setCursor(7, 1);  
    }
    lcd.print(waterLevel);
    lcd.setCursor(9, 1);
    lcd.print("%");
    
    if(waterLevel == 100) digitalWrite(motorPin, LOW);
    else if(waterLevel < 20) digitalWrite(motorPin, HIGH);
  }
  else{
    
  }
  if(!digitalRead(menuBtn)){
    if(page != menuPage){
      openMenuPage();
    }
    else{
      tank_size = EEPROM.read(0);
      openHomePage();
    }
   	while(digitalRead(menuBtn) == LOW);
  }
  if(!digitalRead(plusBtn)){
    if(page == menuPage){
      tank_size++;
      displayTankSize();
      while(digitalRead(plusBtn) == LOW);
    }
  }
  if(!digitalRead(minusBtn)){
    if(page == menuPage){
      tank_size--;
      displayTankSize();
      while(digitalRead(minusBtn) == LOW);
    }
  }
  if(!digitalRead(saveBtn)){
    if(page == menuPage){
      EEPROM.write(0, tank_size);
      openHomePage();
      while(digitalRead(saveBtn) == LOW);
    }
  }
}
void openHomePage(){
    page = homePage;
    if(!tank_size){
      getLevelFlag = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please Set Tank");
      lcd.setCursor(0, 1);
      lcd.print("Size From Menu");
    }
  	else{
  	  getLevelFlag = 1;
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Tank Level");
      lcd.setCursor(6, 1);
    }
}
void openMenuPage(){
  	getLevelFlag = 0;
    page = menuPage;
    lcd.clear();
	lcd.setCursor(3, 0);
    lcd.print("Tank Size");
  	displayTankSize();
}
void displayTankSize(){
  if(tank_size > 10) tank_size=10;
  lcd.setCursor(4, 1);
  if(tank_size < 10){
    lcd.print("0");
	lcd.setCursor(5, 1);
  }
  lcd.print(tank_size);
  lcd.print(" Feet");
}
 
