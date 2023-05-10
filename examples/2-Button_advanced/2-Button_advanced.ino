/*
 *  This is a sample sketch to show how to use the ButtonOne Library
 *  
 *  When pushing a button connected to pin A1 
 *    the built-in LED will  change between on and off
 *  
 *
 * Test circuit:
 * 
 *  Connect a push-button to pin A1 (ButtonPin), connect other side of button to ground.
 *  
 *  The built-in LED is used for output 
 *    many Arduino versions already have a LED that is controlled via a pin
 *
 */
 
#include "ButtonOne.h"

// Setup a ButtonOne instance on pin A1.  
ButtonOne button(A1);

const int LED_Pin =  13;               // 13 for UNO, Nano and Mega
// const int LED_Pin =  LED_BUILTIN;   // for other boards try using LED_BUILTIN


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  
  // set the LED pin to output
  pinMode(LED_Pin, OUTPUT);      // sets the digital pin as output

  //Initiate internal button management
  //   within the button.begin() function, the button pin will be set to INPUT_PULLUP
  button.begin(); 
  
  // link the Press function to be called on a button Press event.   
  button.attachPress(btnPress);

  // adjust debounce details about the button press
  button.setPressDebounceTime(20);    // set number of millisec that have to pass before we test to see if the button state has changed
                                      // default is 75 milli seconds
                                      
  button.setReleaseDebounceTime(30);  // set number of millisec that have to pass before we test to see if the button state has changed
                                      // default is 175 milli seconds

  // btnRelease function is called when the button press is released.
  button.attachRelease(btnRelease);
  
} // END setup()


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push button:
  button.check();

  // You can implement other code in here or just wait a while 
  delay(10);
} // END loop()


//********************************************************************
// Button Press function - will be called when the Button is pressed
//********************************************************************
void btnPress() {
  static int m = LOW;   //used so we can toggle the LED 
  // reverse the LED 
  m = !m;
  // write to the LED pin
  digitalWrite(LED_Pin, m);
} // END btnPress()


//********************************************************************
// Button Release function - will be called when the Button press is released
//********************************************************************
void btnRelease() {
  // do something when the button is released
  
} // END btnRelease()

// END Sketch
