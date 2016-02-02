#include <Arduino.h>
#line 1
#line 1 "C:\\Users\\wami\\Google ドライブ\\wifi\\イベント用\\cre8laser\\cre8laser.ino"
#include <Adafruit_NeoPixel.h>

#include <SPI.h>
#include <MFRC522.h>
#include "Stewitter.h"

#define RST_PIN		D1		// 
#define SS_PIN		D0		//
Stewitter twitter("bed549e5f58efc81f68c055eec017977");
char msg[150];
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance
bool cardset;     // MFRC522にカードが検知されているかどうか
int timeoutcount; // MFRC522からカードが連続で離れた回数を記録
int cre8ID;
int i;

void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown)"));
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
  }
}
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(1, 0, NEO_RGB + NEO_KHZ800);
void led(int r, int g, int b) {
  RGBLED.setBrightness(250) ;
  RGBLED.setPixelColor(0, r, g, b) ;
  RGBLED.show() ;
}
void led(int r, int g, int b, int w) {
  RGBLED.setBrightness(w) ;
  RGBLED.setPixelColor(0, r, g, b) ;
  RGBLED.show() ;
}
void setup() {
  Serial.begin(115200);		// Initialize serial communications with the PC
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();		// Init MFRC522
  ShowReaderDetails();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println("Scan PICC to see UID, type, and data blocks...");
  // MFRC522用変数初期化
  cardset = false;
  timeoutcount = 0;
  RGBLED.begin();
  led(0, 255, 0);
}

void ledblink() {
  int wait = 0;
  while (wait < 30) {
    led(255, 0, 255);delay(250);
    led(0, 0, 0, 0);delay(250);
    wait++;
  }
}
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    if (cardset) {
      if (timeoutcount > 4) {
        led(0,255,0);
        Serial.println("finish!"); i++;
        sprintf(msg, "%d番さんありがとうございます。レーザ加工機を使い終えました。mgtNo.%d", cre8ID, i);
        if (twitter.post(msg)) {
          int status = twitter.wait();
          Serial.println(status);
          if (status == 200) {
            Serial.println(twitter.response());
          } else {
            Serial.print("failed : code ");
            Serial.println(status);
          }
        } else {
          Serial.println("connection failed.");
        }
        cardset = false;
        timeoutcount = 0;
      } else {
        // ４回以内なら連続未検出回数を増やす
        timeoutcount++;
      }
    }
    delay(5);
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  int uid[4];
  for (byte i = 0; i < 4; i++)
    uid[i] = mfrc522.uid.uidByte[i];
  if (!cardset) {
    led(255,0,255);
    delay(100);
    char uid_ch[17];
    sprintf(uid_ch, "%d,%d,%d,%d", uid[0], uid[1], uid[2], uid[3]);
    String cre8 = String(uid_ch);
    Serial.print("card ID : "); Serial.println(cre8);

    if (cre8.compareTo("4,94,113,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 1;
    } else if (cre8.compareTo("4,155,113,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 2;
    } else if (cre8.compareTo("4,124,113,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 3;
    } else if (cre8.compareTo("4,186,113,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 4;
    } else if (cre8.compareTo("4,154,113,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 5;
    } else if (cre8.compareTo("4,247,113,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 6;
    } else if (cre8.compareTo("4,247,112,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 7;
    } else if (cre8.compareTo("4,24,112,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 8;
    } else if (cre8.compareTo("4,215,112,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 9;
    } else if (cre8.compareTo("4,246,112,130") == 0) {
      Serial.print("userID : ");
      cre8ID = 10;
    }
    Serial.println(cre8ID); i++;
    sprintf(msg, "%d番さん、おはようございます！レーザ加工機が動き始めました。 mgtNo.%d", cre8ID, i);
    if (twitter.post(msg)) {
      int status = twitter.wait();
      Serial.println(status);
      if (status == 200) {
        Serial.println(twitter.response());
      } else {
        Serial.print("failed : code ");
        Serial.println(status);
        ledblink();
      }
    } else {
      Serial.println("connection failed.");
      ledblink();
    }
    cardset = true;
  }
  timeoutcount = 0;
  delay(100);


}


