/*
 *  This is a sample sketch to show how to use the OneButton Library
 *
 * Test circuit:
 * 
 *  Connect a pushbutton to pin A1 (ButtonPin), connect other side of button to ground.
 *  
 *  Pin 13 (StatusPin) is used for output 
 *    many Arduino versions already have a LED connected to this pin,
 *    otherwise connect: pin13 - LED - resistor - ground
 *
 */
 
#include "ButtonOne.h"

// Setup a ButtonOne instance on pin A1.  
ButtonOne button(A1);


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output

  //initiate internal button management values
  button.begin(); 
  
  // link the Press function to be called on a button Press event.   
  button.attachPress(btnPress);
} // setup


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push button:
  button.check();

  // You can implement other code in here or just wait a while 
  delay(10);
} // loop


// this function will be called when the button is pressed 
void btnPress() {
  static int m = LOW;   //used so we can toggle the LED 
  // reverse the LED 
  m = !m;
  digitalWrite(13, m);
} // btnPress

// End
