/*
 * This is a sample sketch to show how to use the ButtonOne Library
 * to detect button press events on 2 buttons 
 *
 * Test circuit:
 *    Connect a pushbutton to pin A1 (ButtonPin) and ground.
 *    Connect a pushbutton to pin A2 (ButtonPin) and ground.
 *    
 * The Serial interface is used to show button press events.
 * 
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
    // wait for serial port to connect. Needed for Leonardo only
    // see http://arduino.cc/en/Serial/IfSerial
  }
  
  Serial.println("Starting TwoButtons...");

  //initiate internal button management values
  button1.begin();
  button2.begin();
  
  // link the button 1 Press function.
  button1.attachPress(btn1Press);      // btn1Press() function will be called - when button 1 is pressed
                                       // see below for btn1Press() declaration

  // link the button 2 Press function.
  button2.attachPress(btn2Press);      // btn2Press() function will be called - when button 2 is pressed
                                       // see below for btn2Press() declaration

  // Put your setup code here, to run once:
  
} // END setup()


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push buttons:
  button1.check();
  button2.check();

  // You can implement other code in here or just wait a while 
  // Put your main code here, to run repeatedly:

} // END loop()



//*********************************************
// button functions
//*********************************************

// This function will be called when the button1 is pressed 
void btn1Press() {
  Serial.println("Button 1 pressed.");
} // END btn1Press()


// This function will be called when the button2 is pressed 
void btn2Press() {
  Serial.println("Button 2 pressed.");
} // END btn2Press()


// END Sketch
