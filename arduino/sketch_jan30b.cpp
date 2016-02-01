#line 1 "sketch_jan30b.ino"
                       
#include <Nefry.h>
               
#include "Arduino.h"
void setup();
void loop();
#line 4
Nefry neff;

const int human = D5;  

void setup()
{ 
  pinMode(human, INPUT);
}
int hflg,count;
void loop()
{  
  if ( digitalRead(human)==HIGH ) {
    if(hflg==1){ 
      count++;
      neff.print("count : ");
      neff.println(count);
      hflg=0;
    }
  }else{
    hflg=1; 
                          
  }
}

