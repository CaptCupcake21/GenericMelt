#include <Arduino.h>
#include <DShotESC.h>
#include <AlfredoCRSF.h>
#include <crc8.h>
#include <crsf_protocol.h>
#include <median.h>
#include <SparkFun_MMC5983MA_Arduino_Library.h>

HardwareSerial crsfSerial(1);
AlfredoCRSF crsf;


//Constants for GPIO Numbers
byte S2_MISO =      1; //GPIO Pin for: MISO on ESP32-S2
byte MAG_CS =       2; //GPIO Pin for: Magnetometer Chip Select
byte SNS_VIN =      3; //GPIO Pin for: 
byte IR_VIN =       4; //GPIO Pin for: IR Receiver Analog Voltage
byte SNS_VER =      5; //GPIO Pin for:
byte IR_LED_A =     6; //GPIO Pin for: IR LED A Control
byte ELRS_TX =      7; //GPIO Pin for: 
byte ELRS_RX =      8; //GPIO Pin for:
byte ACCB_CS =      9; //GPIO Pin for: Accelerometer B Chip Select
byte ACCB_INT =    10; //GPIO Pin for: Accelerometer B Interrupt
byte ACCA_CS =     11; //GPIO Pin for: Accelerometer A Chip Select
byte ACCA_INT =    12; //GPIO Pin for: Accelerometer A Interrupt
byte MAG_INT =     13; //GPIO Pin for: Magnetometer Interrupt
byte S2_MOSI =     14; //GPIO Pin for: MOSI on ESP32-S2
byte S2_SCK =      17; //GPIO Pin for: SCK on EESP32-S2
byte IR_LED_B =    21; //GPIO Pin for: IR LED B Control
byte ESC_A =       34; //GPIO Pin for: ESC A Control
byte ESC_B =       35; //GPIO Pin for: ESC B Control
byte LED_STATUS =  36; //GPIO Pin for: Status LED 
byte BOT_HDG_LED = 37; //GPIO Pin for: Bottom Heading LED
byte TOP_HDG_LED = 38; //GPIO Pin for: Top Heading LED
byte Mode = 0;

void setup() {
  pinMode(S2_MISO, OUTPUT);
  pinMode(MAG_CS, OUTPUT);
  pinMode(SNS_VIN, INPUT);
  pinMode(IR_VIN, INPUT);
  pinMode(IR_LED_A, OUTPUT);
  pinMode(ELRS_TX, OUTPUT);
  pinMode(ELRS_RX, INPUT);
  pinMode(ACCB_CS, OUTPUT);
  pinMode(ACCB_INT, OUTPUT);
  pinMode(ACCA_CS, OUTPUT);
  pinMode(ACCA_INT, OUTPUT);
  pinMode(MAG_INT, OUTPUT);
  pinMode(S2_MOSI, OUTPUT);
  pinMode(S2_SCK, OUTPUT);
  pinMode(IR_LED_B, OUTPUT);
  pinMode(ESC_A, OUTPUT);
  pinMode(ESC_B, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(BOT_HDG_LED, OUTPUT);
  pinMode(TOP_HDG_LED, OUTPUT);


  Serial.begin(115200);
  Serial.println("Snafoo we have started bitches!!!\n");


	Serial.begin(115200);


  crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1, ELRS_TX, ELRS_RX);
  if (!crsfSerial) while (1) Serial.println("Invalid crsfSerial configuration");

  crsf.begin(crsfSerial);
}

//Function Returns the Current Mode of the Robot.
// OUTPUT:
// 1 = Safe Mode
// 2 = Standard Drive Mode
// 3 = Melty Mode
byte getCurrentMode(){
byte CurrentMode;

int Mode = crsf.getChannel(7);
// Lowest Position Will Be Safe Mode
if((Mode >= 900) && (Mode < 1250)){
  CurrentMode = 1;
}
// Middle Position Will Be Standard Drive Mode
if((Mode >= 1250) && (Mode < 1750)){
  CurrentMode = 2;
}
// Highest Position Will Be Melty Mode
//TODO: Add Requirement for Deadman Switch(es) for Mode to be Active
if((Mode >= 1750) && (Mode <= 2100)){
  CurrentMode = 3;
}
//If Mode Has an Out of Bounds Value, Enter Safe Mode
if((Mode <900) || (Mode > 2100)){
  CurrentMode = 1;
}
return CurrentMode;
}

//Function Returns ESC Values Corresponding to Current Stick Positions
// OUTPUT:

//array getStandardDriveStickCommands(){
//int rightLR = crsf.getChannel(1);
//int rightUD = crsf.getChannel(2);
//}

//This function returns the angular velocity of the robot at a moment in time
//Acc_A_X = The raw acceleration value from Accelerometer A, in the X direction
//Acc_A_Y = The raw acceleration value from Accelerometer A, in the Y direction
//Acc_B_X = The raw acceleration value from Accelerometer B, in the X direction
//Acc_B_Y = The raw acceleration value from Accelerometer B, in the Y direction
//Acc_Gap_Distance = The distance between the center point of the accelerometers, in units of meters
int ReturnOmega(int Acc_A_X, int Acc_A_Y,int Acc_B_X, int Acc_B_Y, byte AccGapDistance){
//TODO: Insert conversions from raw data to m/s^2 
int Acc_A_n = -Acc_A_X*cos((7*PI)/4) + (-Acc_A_Y*((5*PI)/4));
int Acc_B_n = Acc_B_X*cos((3*PI)/4) + Acc_B_Y*cos(PI/4);
int Acc_Diff = Acc_A_n - Acc_B_n;
int Omega_Squared = Acc_Diff/AccGapDistance;
int Omega = sqrt(Omega_Squared); 
return Omega;

}

void loop() {
  DShotESC escA;
	escA.install(GPIO_NUM_34, RMT_CHANNEL_0);
	escA.init();
	escA.setReversed(false);
	escA.set3DMode(true);
	for (int i = 0; i < 5; i++)
	{
		escA.beep(i);
	}
  bool startupComplete = 1;
while (startupComplete == 1){
  crsf.update();
  Mode = getCurrentMode();
//Safe Control Loop -- This Loop Makes the Robot Safe When Connection is Dropped or Safe Mode is Activated
if(!crsf.isLinkUp() || Mode == 1){
  digitalWrite(LED_STATUS, HIGH);
}


//Standard Drive Control Loop -- This Loop Allows Controlling the Robot using Tank Controls. Motion is Limited to Tank Steering Only. All Motion is Controlled by Operator.
if(crsf.isLinkUp() && Mode==2){
  digitalWrite(LED_STATUS, LOW);
}

//Melty Control Loop -- This Loop Puts the Robot into Melty Mode. Operator Controls Angular Velocity, Direction, and Drift.
//WARNING -- THIS MODE IS EXTREMELY HAZARDOUS AND EXTREME CAUTION SHOULD BE USED WHEN ENTERING THIS MODE. USE PPE AND PROTECTIVE EQUIPMENT TO PREVENT INJURY.
if((crsf.isLinkUp()) && (Mode == 3)){
  escA.sendThrottle3D(50);
  delay(1);
}}
}

