/***********************************************************************
  Program      :  CMRI - Node-Serial-Functions
  Author       :  H&HExpres, Hai faessen
  Description  :  This Section Contains the Functions for CMRI Reading/Setting values and Checking that JMRI can Talk to the Node 
                  
  Version      :  1.01
  Date         :  3 January 2025
  CopyRight (c): H&HExpress 1996-2025

  Change History:

      1.01     :  Re-arranging the Functions in additional Tabs and Adding I2C
*/

void InitializingPinsToBeUsed() {                  // Do not Change the Name of the Function
  
  // Initialize the I2C Components
  Serial.println(F("Init:   Additinal I2C Components"));
  Serial.print(F("  Servo_Driver_00 : "));
  Servo_Driver_00.begin();
  Servo_Driver_00.setOscillatorFrequency(27000000);
  Servo_Driver_00.setPWMFreq(PWM_Frequency);  // Analog servos run at ~50 Hz updates between 40-1600  1600 = This is the maximum PWM frequency
  for ( int i=0; i<=15; i++) { Servo_Driver_00.setPWM(i, 0, 4096); } //Fully Off
  Serial.println(F("OK"));
  delay(5000);
  Serial.println(F("  Set Servo Turnouts Straight: "));
  Servo_Driver_00.writeMicroseconds(Servo_TurnOut_01, USMAX);  //Default to straight = USMAX   divergent = USMIN
  delay(3000);
  Serial.println(F("  Set Servo Turnouts Diverted: "));
  Servo_Driver_00.writeMicroseconds(Servo_TurnOut_01, USMIN);  //Default to straight = USMAX   divergent = USMIN
  delay(3000);
  Serial.println(F("  Set Servo Turnouts Straight: "));
  Servo_Driver_00.writeMicroseconds(Servo_TurnOut_01, USMAX);  //Default to straight = USMAX   divergent = USMIN
  delay(5000);

  Serial.print(F("  Port Expander 00 : "));
  for (int i=0; i<16;i++) { Port_Expander_PCF8575_00.pinMode(i,OUTPUT); }
  for (int i=0; i<16;i++) { Port_Expander_PCF8575_00.digitalWrite(i,HIGH); }
  Serial.println(F("OK"));

  Serial.print(F("  Port Expander 01 : "));
  for (int i=0; i<8;i++) { Port_Expander_PCF8574_01.pinMode(i,INPUT); }
  Serial.println(F("OK"));

  //Individual Pins..
  // pinMode(23, INPUT_PULLUP);
  // pinMode(14, OUTPUT);
  // digitalWrite(14,HIGH);
}


void ReadingSensors() {                 // Do not Change the Name of the Function
  
  cmri.set_bit(0, !digitalRead(HeartBeatLed)); // In JMRI this would be 1001
  //cmri.set_bit(1, !digitalRead(23));

  // Reading Track Sensors for detecting that a train entered the Shadow Station 
  // cmri.set_bit(2, !Port_Expander_PCF8574_01.digitalRead(0));  // Shadow Track Power Section Sensor In  1003

  // Returning the Turnout Status as a Sensor used the Same numbers.
  cmri.set_bit(10,!RS_TurnOut_01);            // In JMRI this would be 1011 according to the Turnout Status
  cmri.set_bit(11,!RS_TurnOut_02);            // In JMRI this would be 1012 according to the Turnout Status

}

void SettingOutputs() {                 // Do not Change the Name of the Function

  // Turnouts With a Servo Conencted
  int TurnOut_01a = cmri.get_bit(36);                 // In JMRI this would be 1037
  if (TurnOut_01a == 1) {Servo_Driver_00.writeMicroseconds(Servo_TurnOut_01, USMIN); RS_TurnOut_01=true; }  
     else { Servo_Driver_00.writeMicroseconds(Servo_TurnOut_01, USMAX); RS_TurnOut_01=false; }             


  // Turnouts with a SnapSwitch 
  int TurnOut_02a = cmri.get_bit(24);                 // In JMRI this would be 1025
  int TurnOut_02b = cmri.get_bit(25);                 // In JMRI this would be 1026
  if (TurnOut_02a == 1) { Port_Expander_PCF8575_00.digitalWrite(Pulse_Turnout_02,LOW); }
     else { Port_Expander_PCF8575_00.digitalWrite(0,HIGH); }
  if (TurnOut_02b == 1) { Port_Expander_PCF8575_00.digitalWrite(Pulse_Turnout_02+1,LOW); }
     else { Port_Expander_PCF8575_00.digitalWrite(1,HIGH); }
  if ((TurnOut_02a==1) && (TurnOut_02b==0)) { RS_TurnOut_02=false; }
  if ((TurnOut_02a==0) && (TurnOut_02b==1)) { RS_TurnOut_02=true; }
  
}
