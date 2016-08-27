#include <Nefry.h>

void setup() {
  // put your setup code here, to run once:
Nefry.setProgramName("Default Program");
}

void loop() {
  // put your main code here, to run repeatedly:
  Nefry.setLed(random(250),random(250),random(250));
  Nefry.ndelay(500);
}
