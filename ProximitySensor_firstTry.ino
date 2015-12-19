#define sensorPin  12// 12 е пина за OUT сигнала от сензора

void setup() {
   
   Serial.begin(9600);
   pinMode(sensorPin, INPUT); // sets digital pin 12 as INPUT pin

}

void loop(){

  int sensorState = 0; 

  // reads senosor state 
  // and returns LOW if there is an object infront of it
  sensorState = digitalRead(sensorPin);
  
  if(sensorState == LOW){

    Serial.println("there is something!");
  }else{

    Serial.println("there isn't anything!");
  }

  delay(2000);

}
