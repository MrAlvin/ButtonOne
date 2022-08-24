/*
 *  This is a sample sketch to show how to use the ButtonOne Library
 *
 *  Sometimes one or two toggle buttons are used to activate the same LED
 *  Using the following settings, it is possible to turn on or turn off
 *  the LED simply by doing one toggle of either of the two toggle buttons.
 *
 */
 
#include "ButtonOne.h"

// Setup a ButtonOne instance on pin A1.  
ButtonOne button1(5);
ButtonOne button2(6);


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output

  //initiate internal button management values
  button1.begin(); 
  button1.attachPress(btn1Press);
  button1.setToggleAsPush();
  
  button2.begin();
  button2.attachPress(btn2Press);
  button2.setToggleAsPush();
  
} // setup


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push button:
  button1.check();
  button2.check();

  // You can implement other code in here or just wait a while 

} // loop


// this function will be called when the button is pressed 
void btn1Press() {
  toggleLED();
} // btn1Press

void btn2Press() {
  toggleLED();
} // btn1Press

void toggleLED() {
  static int m = LOW;   //used so we can toggle the LED 
  // reverse the LED 
  m = !m;
  digitalWrite(13, m);
}
// End
