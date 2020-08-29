// Coder     : Rizky Firmansyah Alif, t.me/rizkyfirst


#include <DS3231.h> //RTC library
#include <Wire.h>

// Variabel Pengaturan
int fadeTimeOn  = 90; // Jeda waktu nyala 0 - 100% brightness (menit)
int fadeTimeOff = 90; // Jeda waktu mati  100 - 0% brightnes (menit)
int setHourOn   =  5; // Jam   untuk lampu nyala (Format 24 jam)
int setMinOn    = 45; // Menit untuk lampu nyala
int setHourOff  = 17; // Jam   untuk lampu mati
int setMinOff   = 55; // Menit untuk lampu mati

// Variabel Setup
#define led 3   //Pin PWM    untuk Lampu Dimmable
#define r1 A0   //Pin Analog untuk Relay 1 (Auto Top Off)
#define r2 A1   //Pin Analog untuk Relay 2 (Aerator)

bool on=LOW;
bool off=HIGH;

DS3231  rtc(SDA, SCL);
Time t;
void siang();
void malam();

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600); // Match to serial monitor
  rtc.begin();
  t = rtc.getTime();
  
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  
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
  digitalWrite(r2,off);
}

void malam()
{
  digitalWrite(r1,off);
  digitalWrite(r2,on);
}

void startOn()
{
  digitalWrite(r1,on);

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
  digitalWrite(r2,off);
}

void startOff()
{ 
  digitalWrite(r1,off);
  digitalWrite(r2,on);
  
  for (int i = 255 ; i >= 0; i--)
  {
    analogWrite(led, i);
    delay(fadeTimeOff*240);
    Serial.print("PWM : " );
    Serial.print(i);
    Serial.print("    ");
  }
}
