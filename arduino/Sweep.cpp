#line 1 "Sweep.ino"
        
                                         
                                           

                     
                     
                    
                    

                                    
   

#include <Servo.h> 
 
#include "Arduino.h"
void setup();
void loop();
#line 15
Servo myservo;                                            
                                                                     
Servo myservo1;Servo myservo2;Servo myservo3; 

void setup() 
{ 
  myservo.attach(D5);                                                    
   myservo1.attach(D4);
    myservo2.attach(D3);
     myservo3.attach(D2);
} 
 
void loop() 
{ 
  int pos;

  for(pos = 0; pos <= 180; pos +=5)                                       
  {                                                          
    myservo.write(pos);                                                                
    myservo1.write(pos);
    myservo2.write(pos);
    myservo3.write(pos);
    delay(15);                                                                         
  } 
  for(pos = 180; pos>=0; pos-=5)                                           
  {                                
    myservo.write(pos);                                                                
        myservo1.write(pos);
    myservo2.write(pos);
    myservo3.write(pos);
    delay(15);                                                                         
  } 
} 


