#include <ArduinoCRSF.h>
#include <crc8.h>
#include <crsf_protocol.h>
#include <median.h>
#include <SPI.h>
//#include <SparkFun_MMC5983MA_Arduino_Library.h>


//Constants for GPIO Numbers
byte ACC_MISO =     1;
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
byte ACC_MOSI =        14;
byte S2_SCK =         17;
byte S2_D1 =       19;
byte S2_D2 =       20;
byte IR_LED_B =    21;
byte ESC_A =       34; 
byte ESC_B =       35;
byte LED_STATUS =  36;
byte BOT_HDG_LED = 37;
byte TOP_HDG_LED = 38;

bool oddLoop = true;

SPIClass SPIA;
SPIClass SPIB;


void setup() {
  //pinMode(MISO, OUTPUT);
  pinMode(MAG_CS, OUTPUT);
  pinMode(SNS_VIN, INPUT);
  pinMode(IR_VIN, INPUT);
  pinMode(IR_LED_A, OUTPUT);
  //pinMode(ELRS_TX, OUTPUT);
  //pinMode(ELRS_RX, INPUT);
  //pinMode(ACCB_CS, OUTPUT);
  pinMode(ACCB_INT, OUTPUT);
  //pinMode(ACCA_CS, OUTPUT);
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

  //general
  Serial.begin(115200);
  Serial.println("Snafoo we have started bitches!!!\n");

  //Bluetooth

  //InitAcel
  SPIA = SPIClass(ACCA_CS);
  SPIA.begin(S2_SCK, ACC_MISO, ACC_MOSI);

  SPIB = SPIClass(ACCB_CS);
  SPIB.begin(S2_SCK, ACC_MISO, ACC_MOSI);

  //initPWM
}

void loop() {
  uint32_t dataA, dataB;
  //read accel
  SPIA.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPIA.setHwCs(LOW);
  dataA = SPIA.transfer(0x00);
  SPIA.setHwCs(HIGH);
  SPIA.endTransaction();
  Serial.print("DataA: ");
  Serial.println(dataA);
  
  SPIB.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPIA.setHwCs(LOW);
  dataB = SPIB.transfer(0x00);
  SPIA.setHwCs(HIGH);
  SPIB.endTransaction();
  Serial.print("DataB: ");
  Serial.println(dataB);

  //Packet / control section

  //Check State
  
    //melty -> spin saft enough to drift
    //Tank -> Drive like Tank
    //Safe -> Do nothing

  
}
