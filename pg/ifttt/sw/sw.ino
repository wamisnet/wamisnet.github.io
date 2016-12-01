#include <Nefry.h>
String Event, SecretKey;
 
bool IFTTT_send(String,String,String data="");
 
void setup() {
  Nefry.setConfHtml("SecretKey",0);
  Nefry.setConfHtml("EventName",1);
  SecretKey = Nefry.getConfStr(0);
  Event = Nefry.getConfStr(1);
}
 
void loop() {
  if (Nefry.push_SW()) {//SWを押した時
    if (!IFTTT_send(Event, SecretKey)) {
      Nefry.setLed(255, 0, 0);//Errの時、赤色点灯
      Nefry.ndelay(5000);
    }
  }
}
 
bool IFTTT_send(String event, String Secretkey, String data) {
  WiFiClient client;
  if (client.connect("maker.ifttt.com", 80)) {
    Nefry.println("connection");
    client.println("POST /trigger/" + event + "/with/key/" + Secretkey + " HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("User-Agent: ESP8266/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    delay(10);
    Nefry.println("OK");
    return true;
  } else {
    Nefry.println("Err");
    return false;
  }
}
