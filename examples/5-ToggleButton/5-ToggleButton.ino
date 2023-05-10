/*
 *  This is a sample sketch to show how to use the ButtonOne Library
 *
 *  Sometimes one or two toggle switches are used to activate (or deactivate) the same LED
 *  
 *  Using the following settings, it is possible to turn on, or turn off
 *  the LED simply by doing one toggle of either of the two toggle switches.
 *
 */
 
#include "ButtonOne.h"

// Setup a ButtonOne instance on pin D5 and D6  
ButtonOne button1(5);
ButtonOne button2(6);


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output

  //initiate internal button management
  button1.begin(); 
  button1.attachPress(btn1Press);
  button1.setToggleAsPush();       // sets the input pin (the button pin) to be used with a toggle switch
  
  button2.begin();
  button2.attachPress(btn2Press); 
  button2.setToggleAsPush();       // sets the input pin (the button pin) to be used with a toggle switch
  
} // END setup()


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push button:
  button1.check();
  button2.check();

  // You can implement other code in here or just wait a while 

} // END loop()


// this function will be called when the button is pressed 
void btn1Press() {
  toggleLED();
} // END btn1Press()


// this function will be called when the button is pressed 
void btn2Press() {
  toggleLED();
} // END btn1Press()


// this function will be called when the LED is to be changed
void toggleLED() {
  static int m = LOW;   //remembers LED status - so we can toggle the LED 
  // reverse the LED 
  m = !m;
  digitalWrite(13, m);
} // END toggleLED()

// END Sketch
