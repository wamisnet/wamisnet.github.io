#line 1 "milkcocoa_esp8266.ino"
#include <ESP8266WiFi.h>
#include <Milkcocoa.h>

                                                                               

#define WLAN_SSID       "...SSID..."
#define WLAN_PASS       "...PASS..."


                                                                                  

#define MILKCOCOA_APP_ID      "...YOUR_MILKCOCOA_APP_ID..."
#define MILKCOCOA_DATASTORE   "esp8266"

                                                                                   

#define MILKCOCOA_SERVERPORT  1883

                                                                               

                                                                    
#include "Arduino.h"
void setup();
void loop();
void onpush(DataElement elem);
#line 22
WiFiClient client;

const char MQTT_SERVER[] PROGMEM    = MILKCOCOA_APP_ID ".mlkcca.com";
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ MILKCOCOA_APP_ID;

Milkcocoa milkcocoa = Milkcocoa(&client, MQTT_SERVER, MILKCOCOA_SERVERPORT, MILKCOCOA_APP_ID, MQTT_CLIENTID);

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Milkcocoa SDK demo"));

                                  
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println( milkcocoa.on(MILKCOCOA_DATASTORE, "push", onpush) );
};

void loop() {
  milkcocoa.loop();

  DataElement elem = DataElement();
  elem.setValue("v", 1);

  milkcocoa.push(MILKCOCOA_DATASTORE, elem);
  delay(7000);
};

void onpush(DataElement elem) {
  Serial.println("onpush");
  Serial.println(elem.getInt("v"));
};


