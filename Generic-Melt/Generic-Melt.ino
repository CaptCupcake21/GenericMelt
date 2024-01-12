#include "../ArduinoCRSF/ArduinoCRSF.h"
//#include <crc8.h>
//#include <crsf_protocol.h>
//#include <median.h>
//#include <SPI.h>
//#include <SparkFun_MMC5983MA_Arduino_Library.h>


//Constants for GPIO Numbers
//byte MISO =         1;
byte MAG_CS =       2;
byte SNS_VIN =      3;
byte IR_VIN =       4;
byte SNS_VER =      5;
byte IR_LED_A =     6;
//byte ELRS_TX =      7;
//byte ELRS_RX =      8;
byte ACCB_CS =      9;
byte ACCB_INT =    10;
byte ACCA_CS =     11;
byte ACCA_INT =    12;
byte MAG_INT =     13;
//byte MOSI =        14;
//byte SCK =         15;
byte IR_LED_B =    16;
byte ESC_A =       34; 
byte ESC_B =       35;
byte LED_STATUS =  36;
byte BOT_HDG_LED = 37;
byte TOP_HDG_LED = 38;


void setup() {
  //pinMode(MISO, OUTPUT);
  pinMode(MAG_CS, OUTPUT);
  pinMode(SNS_VIN, INPUT);
  pinMode(IR_VIN, INPUT);
  pinMode(IR_LED_A, OUTPUT);
  //pinMode(ELRS_TX, OUTPUT);
  //pinMode(ELRS_RX, INPUT);
  pinMode(ACCB_CS, OUTPUT);
  pinMode(ACCB_INT, OUTPUT);
  pinMode(ACCA_CS, OUTPUT);
  pinMode(ACCA_INT, OUTPUT);
  pinMode(MAG_INT, OUTPUT);
  //pinMode(MOSI, OUTPUT);
  //pinMode(SCK, OUTPUT);
  pinMode(IR_LED_B, OUTPUT);
  pinMode(ESC_A, OUTPUT);
  pinMode(ESC_B, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(BOT_HDG_LED, OUTPUT);
  pinMode(TOP_HDG_LED, OUTPUT);

}

void loop() {
  digitalWrite(BOT_HDG_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TOP_HDG_LED, LOW);
  delay(5);                       // wait for a second
  digitalWrite(TOP_HDG_LED, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(BOT_HDG_LED, LOW); 
  delay(5);                       // wait for a second
}
