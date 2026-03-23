#include <LiquidCrystal.h>
 
// Initialize the LCD with pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
// Define sensor pins
const int lm35Pin = A0;        // LM35 temperature sensor
const int humidSensorPin = A1; // Soil moisture sensor (used as humidity sensor)
const int windSensorPin = A2;  // Potentiometer simulating a wind speed sensor
 
void setup() {
  lcd.begin(16, 2);
  lcd.print("Weather Station");
  delay(2000);
  lcd.clear();
}
 
void loop() {
  // Read temperature from LM35 (LM35 outputs 10 mV per °C)
  int lm35Raw = analogRead(lm35Pin);
  // Convert ADC reading to temperature in °C:
  // 5V/1024 ~ 4.88 mV per unit; LM35 gives 10 mV/°C.
  float temperature = (lm35Raw * (5.0 / 1024)) / 0.01;  
  
  // Read the humidity sensor value and map it to a percentage.
  int humidRaw = analogRead(humidSensorPin);
  // For simulation, map the sensor's 0–1023 range to 0–100%.
  // (In a real system you’d calibrate this mapping based on your sensor's characteristics.)
  float humidity = map(humidRaw, 0, 1023, 0, 100);
  
  // Read the wind sensor (potentiometer) value and map it to wind speed.
  int windRaw = analogRead(windSensorPin);
  // Map the raw value to a wind speed range, e.g., 0–100 km/h.
  float windSpeed = map(windRaw, 0, 1023, 0, 100);
  
  // Update LCD Display:
  // First row: Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // One decimal place
  lcd.print("C   ");
  
  // Second row: Humidity (as percentage) and Wind Speed (km/h)
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 0);     // Display as integer percentage
  lcd.print("% ");
  lcd.print("W:");
  lcd.print(windSpeed, 0);    // Display wind speed as an integer
  lcd.print("km/h");
  
  delay(1000);  // Update display every second
}
