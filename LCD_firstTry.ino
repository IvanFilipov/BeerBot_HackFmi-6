#include <Wire.h>
#include <LiquidCrystal_I2C.h> // 

LiquidCrystal_I2C lcd(0x3F,16,2);   //   setting Arduino I2C address and dimensions 2 x 16 
/*************************************************************************************************************/

//some helping functions to manipulate LCD output
void PrintStr(const String& s){

     
   for(int i = 0 ; i <s.length() ; i++ )
       lcd.print(s[i]);
  
}

void PrintInt(const int& pInt){

     String num(pInt);
     
     PrintStr(num);
  
}

void PrintDouble(const double& pDouble){

     String num(pDouble);

     PrintStr(num);

  
}


void setup()
{

  //trying some of the library's features
  lcd.init();                            
  delay(100);
  lcd.clear();                         
  delay(100);
  lcd.setBacklight(0);
  lcd.setCursor(2,0);                
  lcd.blink_off();        
  
  
  
  //some tests of our functions
  PrintStr("Hi , Arduino");
  
  int a = 11 ;

  PrintInt(a);
 
  double d = 3.14 ;

  PrintDouble(d);

}


void loop(){
}
