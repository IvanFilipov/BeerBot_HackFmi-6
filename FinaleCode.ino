// Proximity sensor pin define
#define sensorPin  12

// Temperature sensor pin defines
#define SDA_PORT PORTD
#define SDA_PIN 6           
#define SCL_PORT PORTD
#define SCL_PIN 5 

//Motor Driver pin defines
#define RedA1 2
#define RedB1 4
#define Enable 3

//how many times to mesure the beer temperature
#define PROBING_TIMES 8

//min and max temp for the perfect beer
//info from our survey
#define TEMP_LOW_LEVEL 5
#define TEMP_HIGH_LEVEL 11


//our custom char defines
#define DEGREE_SYM 0
#define BEER_1 1
#define BEER_2 2

//Motor parameters
#define RIGHT_SIDE_SPEED 64
#define RIGHT_SIDE_DURATION 3000 //miliseconds
#define LEFT_SIDE_SPEED  64
#define LEFT_SIDE_DURATION 3000 //ms


#include "Wire.h"

//for LCD 
#include "LiquidCrystal_I2C.h"

//for temperature sensor
#include "MLX90615.h"

//creating an object to control the lcd
LiquidCrystal_I2C lcd(0x3F,16,2); //setting Arduino I2C address and dimensions 2 x 16 

//creating an object to control the temperature sensor
MLX90615 TempSensor;


//some useful Print functions
void PrintStr(const String& s){
  
   uint8_t len = s.length();
   for(uint8_t i = 0 ; i <len ; ++i)
       lcd.print(s[i]);
}

void PrintFloat(const float& pFloat){
  
     String num(pFloat);

     PrintStr(num);
}

void PrintNewLine(){

   lcd.setCursor(0,1);
}

//prints new line with indentation
void PrintNewLineIndt(){

  lcd.setCursor(1,4);
}


//Prints our custom 'beer' char
void PrintBeerSym(){
  
  lcd.write(BEER_1);
  lcd.write(BEER_2);
}

//not used
/*
void openContainer()
{
  lcd.setCursor(0, 1);
  PrintStr("Shit son");
}
*/

//motor control functions

inline void rotateRight(int duration, int power){
  
  digitalWrite(RedA1, HIGH);
  digitalWrite(RedB1, LOW);

  analogWrite(Enable, power);

  delay(duration);
}

inline void rotateLeft(int duration, int power){
  
  digitalWrite(RedA1, LOW);
  digitalWrite(RedB1, HIGH);

  analogWrite(Enable, power);

  delay(duration);
}

inline void stopRotation(){
  
  digitalWrite(RedA1, LOW);
  digitalWrite(RedB1, LOW);
}


//commands for the motor to open the beer
void openBeer(){
  
  rotateLeft(LEFT_SIDE_DURATION,LEFT_SIDE_SPEED);

  stopRotation();

  delay(1000);

  rotateRight(RIGHT_SIDE_DURATION,RIGHT_SIDE_SPEED);

  stopRotation();
}


//mesures the beer temperature 
//and returns the average
float getAverageTemp(uint8_t samples){
  
  float avrgTemp = 0.0;
  
  for(uint8_t i = 0; i < samples; ++i)
    avrgTemp += TempSensor.getObjTemperature(MLX90615_OBJECT_TEMPERATURE);

  return avrgTemp /= samples;
}

void setup_lcd(){
  lcd.init();
  delay(100);
  lcd.clear();                       
  delay(100);
  lcd.setBacklight(0);
  delay(100);

  //arrays that defines our custom chars
  uint8_t letter[] = { 14, 17, 17, 17, 14,  0,  0,  0 };
  uint8_t beer1[] = {  4,  6, 23, 23, 23, 15,  7, 31 };
  uint8_t beer2[] = {  4, 12, 28, 28, 28, 28, 28, 31 };

  
  lcd.load_custom_character(DEGREE_SYM, letter);
  lcd.load_custom_character(BEER_1, beer1);
  lcd.load_custom_character(BEER_2, beer2);

  lcd.clear();
}

void setup(){ 
  
  TempSensor.init();
  
  setup_lcd();
    
  pinMode(sensorPin, INPUT);
  
  pinMode(RedA1,OUTPUT);
  pinMode(RedB1, OUTPUT);
  pinMode(Enable, OUTPUT);
}

bool FirstTruningOn = true;

void loop(){

  //checks if this is the first usage of the bot
  //after switching on
  
  if(FirstTruningOn){
    
    PrintStr("starting the");
    lcd.setCursor(1,4);
    PrintStr("BeerBoot...");
    delay(4000);

   FirstTruningOn = false;
  
  }
  
  lcd.clear();

  PrintStr("Please put a");
  lcd.setCursor(1,4);
  PrintBeerSym();
  PrintStr("...");
  
  
  uint8_t sensorState = HIGH; // there isn't an object

  //trying to catch an object every second
  while(sensorState == HIGH){
    sensorState = digitalRead(sensorPin);// returns LOW if there is an object
    delay(1000); 
  }

  //checking if the object is there for 3 seconds
  for(int i=0;i <3  ;i++){
    sensorState = digitalRead(sensorPin);
    delay(1000);
  }
   
  
  lcd.clear();

  if(sensorState == LOW)
  {
    PrintStr("A ");
    PrintBeerSym();
    PrintStr(" has been");
    PrintNewLineIndt();
    PrintStr("detected!");
    
    delay(4000);

    lcd.clear();
    
    PrintStr("Measuring the ");
    PrintBeerSym();
    PrintNewLineIndt();
    PrintStr("temperature...");
    
    delay(5000);
    
    float avrgTemp =  getAverageTemp(PROBING_TIMES);

    if(avrgTemp > TEMP_LOW_LEVEL && avrgTemp < TEMP_HIGH_LEVEL){
      
       lcd.clear();

       PrintStr("The ");
       PrintBeerSym();
       PrintStr(" is ");
       PrintFloat(avrgTemp);
       PrintStr("C");
       lcd.write(DEGREE_SYM);
     
       delay(5000);


       lcd.clear();
       PrintStr("Proceeding to");
       PrintNewLine(); 
       PrintStr("open the ");
       lcd.write(BEER_1);
       lcd.write(BEER_2);
       PrintStr(" ...");
       openBeer();

       delay(5000);
       lcd.clear();
       PrintStr("ENJOY YOUR BEER!!!");

       delay(5000);
     }
     else{

      lcd.clear();   
   
       PrintStr("the ");
       PrintBeerSym();
       PrintStr(" temp is");
       PrintNewLine();
       PrintStr("NOT acceptable!");

       delay(5000);

       lcd.clear();
    
       PrintStr("opening is up");
       PrintNewLine(); //new line
       PrintStr("to your decision..") ;
  }

  

   delay(5000);
   lcd.clear();
   PrintStr("HACKED BY TEAM");
   PrintNewLine();
   PrintStr("BEEROVERLORDS");

   //waiting the beer to be removed
   while(sensorState == LOW){

     delay(1000);

     sensorState = digitalRead(sensorPin);
    
   }
 }
}
