// Pin Definitions
int tempSensor = A0;
int lightSensor = A1;
int forceSensor = A2;
int soilSensor = A3;
int gasSensor = A4;
 
int triggerPin = 2;
int echoPin = 7;
 
long duration;
float cm, inches;
 
void setup()
{
  pinMode(tempSensor, INPUT);
  pinMode(lightSensor, INPUT);
  pinMode(forceSensor, INPUT);
  pinMode(soilSensor, INPUT);
  pinMode(gasSensor, INPUT);
 
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  Serial.begin(9600);
}
 
void loop()
{
  // 🌡️ Temperature
  int tempReading = analogRead(tempSensor);
  float voltage = tempReading * 5.0 / 1024.0;
  float tempC = (voltage - 0.5) * 100;
 
  // 🌞 Light
  int lightReading = analogRead(lightSensor);
 
  // 💪 Force
  int forceValue = analogRead(forceSensor);
 
  // 🌱 Soil Moisture
  int soilValue = analogRead(soilSensor);
 
  // 🌫️ Gas Sensor
  int gasValue = analogRead(gasSensor);
 
  // 📏 Ultrasonic Distance
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2.0) / 29.1;
  inches = (duration / 2.0) / 74.0;
 
  // 📊 Data Logging Output
  Serial.println("------ Sensor Data ------");
 
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");
 
  Serial.print("Light: ");
  Serial.println(lightReading);
 
  Serial.print("Force: ");
  Serial.println(forceValue);
 
  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);
 
  Serial.print("Gas Level: ");
  Serial.println(gasValue);
 
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print(" cm | ");
  Serial.print(inches);
  Serial.println(" inches");
 
  Serial.println("-------------------------");
  Serial.println();
 
  delay(1000);
}
