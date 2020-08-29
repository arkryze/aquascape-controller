#include <DS3231.h> //Include the clock library
#include <Wire.h>

// Changable Vars
int fadeTimeOn  = 90; // Jeda waktu nyala 0 - 100% brightness (menit)
int fadeTimeOff = 90; // Jeda waktu mati  100 - 0% brightnes (menit)
int setHourOn   =  5; // Set hours to wake (military time / Format 24 jam)
int setMinOn    = 45; // Set minute to wake
int setHourOff  = 17; // Set hours off
int setMinOff   = 55; // Set minute off

// Set up Vars
#define led 3   //Pin PWM    untuk Lampu Dimmable
#define r1 A0   //Pin Analog untuk Relay 1 (lampu kecil)
#define r2 A1   //Pin Analog untuk Relay 2 (ATO)
#define r3 A2   //Pin Analog untuk Relay 3 (Aerator)
#define r4 A3   //Pin Analog untuk Relay 4 (lampu besar)

bool on=LOW;
bool off=HIGH;

DS3231  rtc(SDA, SCL);
Time t;
void malam();
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600); // Match to serial monitor
  rtc.begin();
  t = rtc.getTime();
  
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(r3,OUTPUT);
  pinMode(r4,OUTPUT);
  //malam();
  if ((t.hour>setHourOn)&&(t.hour<setHourOff))
  {
    siang();
  }
  else
  {
    malam();
  }
}

void loop()
{
  t = rtc.getTime();
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  Serial.println(rtc.getTimeStr());
  
  if (t.hour == setHourOn && t.min == setMinOn)
  {
    startOn();
  }
  
  if (t.hour == setHourOff && t.min == setMinOff)
  {    
    startOff();
  }
delay(1000);
}

void siang()
{
  digitalWrite(r1,on);
  digitalWrite(r2,on);
  digitalWrite(r3,off);
  digitalWrite(r4,on);
}

void malam()
{
  digitalWrite(r1,off);
  digitalWrite(r2,off);
  digitalWrite(r3,on);
  digitalWrite(r4,off);
}

void startOn()
{
  digitalWrite(r1,on);
  digitalWrite(r2,on);

  analogWrite(led, 0);
  delay(fadeTimeOn*240);
  for (int i = 0 ; i <= 255 ; i++)
  {
  analogWrite(led, i);
  delay(fadeTimeOn*240);
  Serial.print("PWM : " );
  Serial.print(i);
  Serial.print("    ");
  }
  delay(30000);
  analogWrite(led, 0);
  digitalWrite(r3,off);
  digitalWrite(r4,on);
}

void startOff()
{ 
  digitalWrite(r1,off);
  digitalWrite(r2,off);
  digitalWrite(r3,on);
  digitalWrite(r4,off);
  analogWrite(led,255);
  delay(30000); 
  for (int i = 255 ; i >= 0; i--)
  {
    analogWrite(led, i);
    delay(fadeTimeOff*240);
    Serial.print("PWM : " );
    Serial.print(i);
    Serial.print("    ");
  }
}
