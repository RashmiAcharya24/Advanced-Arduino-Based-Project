#define TEMPERATURE A0
#define MOTOR 3
void setup(){
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
}
 int speed_decider(int temp){
  if(temp<20)
    return 0;
  else if(temp>40)
    return 255;
  else
    return map(temp, 20, 40, 0, 255);
}
 
void loop(){
  int temperature = analogRead(TEMPERATURE);
  temperature = map(temperature, 20, 358, -40, 125);
  Serial.println(speed_decider(temperature));
  analogWrite(MOTOR, speed_decider(temperature));
}
