// Header File for the Node_Serial_Functions 
// use for adding Libraries and Variables to the Sketch


#include <PCF8574.h>
#include <PCF8575.h>
#include <Adafruit_PWMServoDriver.h>

// Settings of the Port Expander
PCF8575 Port_Expander_PCF8575_00(0x20);  // Adding 16 Additional Input/Output Ports for Sensors or Switches
PCF8575 Port_Expander_PCF8574_01(0x21);  // Adding 8  Additional Input/Output Ports for Sensors or Switches

// Servo Drivers or Light Dimmers                                                        
Adafruit_PWMServoDriver Servo_Driver_00 = Adafruit_PWMServoDriver(0x40); // Adding the Servo Driver
#define PWM_Frequency    50  // Analog servos run at ~50 Hz updates

//the difference between USMIN and USMAX for the Servo results when changing in a 1 second delay
#define USMIN  612 // This is the rounded 'minimum' microsecond length based for the divergent setting
#define USMAX  850 // This is the rounded 'maximum' microsecond length based for the straight setting
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define delaytime 3   // delaytime to move the servo's of the Turnouts

#define Servo_TurnOut_01 00 // Servo Turnout 1
#define Pulse_Turnout_02 00 // SnapSwitch Turnout uses 2 pins as example here pin 0 and 1

// Return Sensors for the Turnouts  RS_TurnOut_01  = Return Sensor Turnout 1
bool RS_TurnOut_01 = true;   // default value set to Straight,  if false it is Divergent
bool RS_TurnOut_02 = true;   // default value set to Straight,  if false it is Divergent
