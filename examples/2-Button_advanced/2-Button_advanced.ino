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
 *
 * Other functions presented in this Sketch: 
 *   * longPress
 *   * setting the time (in milli seconds (ms) ) for the 
 *     - debounce
 *     - release debounce
 *     - longPress 
 *      
 *  Serial.print is used to show a Press, a Release, and a longPress
 *  
 *  
 *  by MrAlvin - May 2023
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

  Serial.begin(115200); // serial is used to indicate button events
  
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

  // btnLongPress function is called when the button has been pressed for a while (default 700 milli seconds)
  button.attachLongPress(btnLongPress);

  button.setLongPressTime(400);       // set number of millisec that have to pass before a LongPress is registered
                                      // default is 700 milli seconds
  
} // END setup()


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push button:
  button.check();

  // You can implement other code in here or just wait a while 

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

  Serial.println( F("button Pressed") );
} // END btnPress()


//********************************************************************
// Button Long Press function - will be called when the Button has been pressed for some time (default 700ms) 
//********************************************************************
void btnLongPress() {
  // do something when the button has been pressed for some time 
  Serial.println( F("button Long Press is registered") );
} // END btnLongPress()


//********************************************************************
// Button Release function - will be called when the Button press is released
//********************************************************************
void btnRelease() {
  // do something when the button is released
  Serial.println( F("button Released") );
} // END btnRelease()

// END Sketch
