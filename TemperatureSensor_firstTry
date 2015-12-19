//arduino uno port specification
#define SDA_PORT PORTD
#define SDA_PIN 6   //define the SDA pin         
#define SCL_PORT PORTD
#define SCL_PIN 5  //define the SCL pin

//a little change has been made in the library :
//the following public function has been added to class MLX90615 :
/*
 * float getObjTemperature(int Temperature_kind) {
    int dev = DEVICE<<1;
    int dataLow = 0;
    int dataHigh = 0;
    int pec = 0;
    
    i2c_start(dev+I2C_WRITE);
    i2c_write(Temperature_kind);  
    // read
    i2c_rep_start(dev+I2C_READ);
    dataLow = i2c_read(false); 
    dataHigh = i2c_read(false); 
    pec = i2c_read(true);
    i2c_stop();
    
    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point
    
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((dataHigh & 0x007F) << 8) + dataLow);
    tempData = (tempData * tempFactor)-0.01;
    
    float celcius = tempData - 273.15;
        
   
    return celcius;
 }
 */
#include "MLX90615.h"

//creating the object ,which controls the temperature sensor
MLX90615 TempSensor;

void setup(){
  
  Serial.begin(9600); //initialize serial communication
  Serial.println("Setup...");
  TempSensor.init(); //initialize soft i2c wires
  
}


void loop()
{ 
    Serial.print("Object temperature: ");

    //using the new function
    float cel = TempSensor.getObjTemperature(MLX90615_OBJECT_TEMPERATURE);
    Serial.print(cel);
    delay(1000);  
}
