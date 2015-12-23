// Proximity sensor.
#define sensorPin  12

// Temperature sensor
#define SDA_PORT PORTD
#define SDA_PIN 6           
#define SCL_PORT PORTD
#define SCL_PIN 5 

//Reductor defines
#define RedA1 2
#define RedB1 4
#define Enable 3

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "String.h"
#include "MLX90615.h"

LiquidCrystal_I2C lcd(0x3F,16,2);
MLX90615 TempSensor;

void PrintStr(const String& s)
{
   uint8_t len = s.length();
   for(uint8_t i = 0 ; i <len ; ++i)
       lcd.print(s[i]);
}

void PrintInt(const int& pInt)
{
     String num(pInt);
   
     PrintStr(num);
}

void PrintFloat(const float& pFloat)
{
     String num(pFloat);

     PrintStr(num);
}

void openContainer()
{
  lcd.setCursor(0, 1);
  PrintStr("Shit son");
}

inline void rotateRight(int duration, int power)
{
  digitalWrite(RedA1, HIGH);
  digitalWrite(RedB1, LOW);

  analogWrite(Enable, power);

  delay(duration);
}

inline void rotateLeft(int duration, int power)
{
  digitalWrite(RedA1, LOW);
  digitalWrite(RedB1, HIGH);

  analogWrite(Enable, power);

  delay(duration);
}

inline void stopRotation()
{
  digitalWrite(RedA1, HIGH);
  digitalWrite(RedB1, HIGH);
}

void openBeer()
{
  rotateRight(3000, 64);

  stopRotation();

  delay(500);

  rotateLeft(3000, 64);

  stopRotation();
}

void BeerMessage(float temp)
{
  PrintStr("The");
  lcd.write(1);
  lcd.write(2);
  PrintStr("is");
  PrintFloat(temp);
  PrintStr("C");
  lcd.write(0);
}

float getAverageTemp(uint8_t samples)
{
  float avrgTemp = 0.0;
  for(uint8_t i = 0; i < samples; ++i)
    avrgTemp += TempSensor.getTemperature(MLX90615_OBJECT_TEMPERATURE);

  return avrgTemp /= samples;
}

void setup_lcd()
{
  lcd.init();
  delay(100);
  lcd.clear();                       
  delay(100);
  lcd.setBacklight(0);
  delay(100);
    
  uint8_t letter[] = { 14, 17, 17, 17, 14,  0,  0,  0 };
  uint8_t beer1[8] = {  4,  6, 23, 23, 23, 15,  7, 31 };
  uint8_t beer2[8] = {  4, 12, 28, 28, 28, 28, 28, 31 };
  lcd.load_custom_character(0, letter);
  lcd.load_custom_character(1, beer1);
  lcd.load_custom_character(2, beer2);

  lcd.clear();
}

void setup() 
{ 
  Serial.begin(9600);

  TempSensor.init();

  setup_lcd();
    
  pinMode(sensorPin, INPUT);
  pinMode(RedA1,OUTPUT);
  pinMode(RedB1, OUTPUT);
  pinMode(Enable, OUTPUT);
}

void loop()
{
  lcd.clear();
  uint8_t sensorState = 0; // съхранява състоянието на сензора
  
  sensorState = digitalRead(sensorPin);// прочита състоянието на сензора 
  lcd.setCursor(0, 0);

  if(sensorState)
  {
    PrintStr("No beer -_-");
  }
  else
  {
    delay(2000);
    float avrgTemp =  getAverageTemp(16);
    if(avrgTemp < 30.0)
    {
       BeerMessage(avrgTemp);
       openBeer();                              
    }
    else
    {
      PrintStr("Fuck off");
      openContainer();
    }
  }
  
  delay(500);
}
