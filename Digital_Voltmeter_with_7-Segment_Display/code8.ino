int a;
int vin;
int input=A0;
int disp1=1;
int disp2=2;
int disp3=3;
int segA=5;
int segB=6;
int segC=7;
int segD=8;
int segE=9;
int segF=10;
int segG=11;
int segDP=12;
void setup()
{
pinMode(disp1, OUTPUT);
pinMode(disp2, OUTPUT);
pinMode(disp3, OUTPUT);
pinMode(segA, OUTPUT);
pinMode(segB, OUTPUT);
pinMode(segC, OUTPUT);
pinMode(segD, OUTPUT);
pinMode(segE, OUTPUT);
pinMode(segF, OUTPUT);
pinMode(segG, OUTPUT);
pinMode(segDP, OUTPUT);
pinMode(input,INPUT);
}
void loop()
{
vin=analogRead(input);
vin=vin/2.046;
a = vin%10;
if(a<=5)
{a=0;}
else
{a=5;}
digitalWrite(disp1,LOW);
digitalWrite(disp2,LOW);
digitalWrite(disp3, HIGH);
digitalWrite(segDP,HIGH);
display(a);
delay(5);
vin = vin/10;
a = vin%10;
digitalWrite(disp3,LOW);
digitalWrite(disp2,HIGH);
digitalWrite(segDP,LOW);
display(a);
delay(5);
vin=vin/10;
a=vin;
digitalWrite(disp2,LOW);
digitalWrite(disp1,HIGH);
digitalWrite(segDP,HIGH);
display(a);
delay(5);

}
int display (int a)
{
switch (a)
{
case 0:
digitalWrite(segA, LOW);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, LOW);
digitalWrite(segE, LOW);
digitalWrite(segF, LOW);
digitalWrite(segG, HIGH);
break;

case 1:
digitalWrite(segA, HIGH);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, HIGH);
digitalWrite(segE, HIGH);
digitalWrite(segF, HIGH);
digitalWrite(segG, HIGH);
break;

case 2:
digitalWrite(segA, LOW);
digitalWrite(segB, LOW);
digitalWrite(segC, HIGH);
digitalWrite(segD, LOW);
digitalWrite(segE, LOW);
digitalWrite(segF, HIGH);
digitalWrite(segG, LOW);
break;

case 3:
digitalWrite(segA, LOW);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, LOW);
digitalWrite(segE, HIGH);
digitalWrite(segF, HIGH);
digitalWrite(segG, LOW);
break;

case 4:
digitalWrite(segA, HIGH);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, HIGH);
digitalWrite(segE, HIGH);
digitalWrite(segF, LOW);
digitalWrite(segG, LOW);
break;

case 5:
digitalWrite(segA, LOW);
digitalWrite(segB, HIGH);
digitalWrite(segC, LOW);
digitalWrite(segD, LOW);
digitalWrite(segE, HIGH);
digitalWrite(segF, LOW);
digitalWrite(segG, LOW);
break;

case 6:
digitalWrite(segA, LOW);
digitalWrite(segB, HIGH);
digitalWrite(segC, LOW);
digitalWrite(segD, LOW);
digitalWrite(segE, LOW);
digitalWrite(segF, LOW);
digitalWrite(segG, LOW);
break;

case 7:
digitalWrite(segA, LOW);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, HIGH);
digitalWrite(segE, HIGH);
digitalWrite(segF, HIGH);
digitalWrite(segG, HIGH);
break;

case 8:
digitalWrite(segA, LOW);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, LOW);
digitalWrite(segE, LOW);
digitalWrite(segF, LOW);
digitalWrite(segG, LOW);
break;

case 9:
digitalWrite(segA, LOW);
digitalWrite(segB, LOW);
digitalWrite(segC, LOW);
digitalWrite(segD, LOW);
digitalWrite(segE, HIGH);
digitalWrite(segF, LOW);
digitalWrite(segG, LOW);
break;
}}
