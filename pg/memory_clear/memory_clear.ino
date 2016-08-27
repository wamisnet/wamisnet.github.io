#include <Nefry.h>
void setup() {
  Nefry.setConfWifi("Nefry","Nefry-wifi");
  Nefry.setConfModule("","","");
  Nefry.setConfUser("","");
  for (int i = 0; i < 8; i++) {
    Nefry.setConfValue(0, i);
    Nefry.setConfStr("", i + 1);
  }
  Nefry.setLed(0,255,0);
  if(WiFi.status() != WL_CONNECTED)Nefry.reset();
  Nefry.setWebUpdate("wamisnet.github.io","/pg/default");
}

void loop() {

}
