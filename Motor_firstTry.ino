//Setting digital outputs of Arduino and the Enable pin
//for communication with DC Dual Motor Driver 30V 4A
#define Dir1a  2  
#define Dir1b  4  
#define Enable1  3 
   
// Initialization
void setup() 
{
  // Setting pin mode to output  
  
  pinMode(Dir1a, OUTPUT);
  pinMode(Dir1b, OUTPUT);
  pinMode(Enable1, OUTPUT);  

  // Setting speed of reductor
   analogWrite(Enable1,500);   
}

// main loop
void loop() 
{  
   // Motor running for 3 seconds
   digitalWrite(Dir1a, HIGH);     
   digitalWrite(Dir1b, LOW);
  
   delay(3000);             

   // Stopping motor for 3 second
   digitalWrite(Dir1a,LOW);     
   digitalWrite(Dir1b, LOW);

   delay(3000);

   //running motor again in reverse direction
   //for 3 seconds
   digitalWrite(Dir1a, LOW);     
   digitalWrite(Dir1b, HIGH);

   delay(3000);

}
