/*
 * This is a sample sketch to show how to use the OneButto nLibrary
 * to detect button press events on 2 buttons 
 *
 * Test circuit:
 *    Connect a pushbutton to pin A1 (ButtonPin) and ground.
 *    Connect a pushbutton to pin A2 (ButtonPin) and ground.
 *    
 * The Serial interface is used for detection output of the button events.
 */

#include "ButtonOne.h"

// Setup a ButtonOne instance on pin A1
ButtonOne button1(A1);

// Setup a ButtonOne instance on pin A2
ButtonOne button2(A2);


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // Setup the Serial port. see http://arduino.cc/en/Serial/IfSerial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting TwoButtons...");

  //initiate internal button management values
  button1.begin();
  button2.begin();
  
  // link the button 1 functions.
  button1.attachPress(btn1Press);

  // link the button 2 functions.
  button2.attachPress(btn2Press);
} // setup


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push buttons:
  button1.check();
  button2.check();

  // You can implement other code in here or just wait a while 
  delay(10);
} // loop



//*********************************************
// button functions
//*********************************************

// This function will be called when the button1 is pressed 
void btn1Press() {
  Serial.println("Button 1 pressed.");
} // btn1Press

// This function will be called when the button2 is pressed 
void btn2Press() {
  Serial.println("Button 2 pressed.");
} // btn2Press


// End
