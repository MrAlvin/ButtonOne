/*
 *  This is a sample sketch to show how to use the ButtonOne Library
 *
 *  Sometimes one or two toggle buttons are used to activate (or deactivate) the same LED
 *  
 *  Using the following settings, it is possible to turn on, or turn off
 *  the LED simply by doing one toggle of either of the two toggle switches.
 *
 *
 *  The change from '5-ToggleButtons' example is;
 *  - the LED pin is now declared as a constant, by the name 'blink_pin'
 *
 */
 
#include "ButtonOne.h"

// Setup a ButtonOne instance on pin A1.  
ButtonOne button1(5);
ButtonOne button2(6);

//// LED pin declarations
const byte blink_pin = 13;    //the pin number that the LED is connected to

//// global variables for 'Blik N times' function
byte _blinks = 0;
byte _blink_minor = 0;
int blinkN_on_delay = 150;    //change this value to adjust the number of MilliSeconds the LED is ON
int blinkN_off_delay = 150;   //change this value to adjust the number of MilliSeconds the LED is OFF
int blinkN_long_off_delay = 600; // milli seconds between major and minior blinks


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // enable the standard led on pin 13.
  pinMode(blink_pin, OUTPUT);      // sets the digital pin as output

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

  // update blink LED 
  blinkN();

  // You can implement other code in here or just wait a while 

} // loop

//*********************************************
// button actions
//*********************************************

// this function is called if button is toggled quick, or when switvhed (slowly) from one to the other position
void btn1Press() {
  blinkN(2);
} // btn1Press

void btn2Press() {
  blinkN(4);
} // btn1Press


//*********************************************
// blink actions
//*********************************************

void blinkN(byte major){
  _blinks = major;
  _blink_minor = 0;
}//blinkN

void blinkN(byte major, byte minor){
  _blinks = major;
  _blink_minor = minor; 
}//blinkN

void blinkN() {
  static unsigned long blinkN_millis = 0;
  static unsigned long blinkN_interval = 0;
  static boolean do_N_on = true;
  if(_blinks > 0) { // still do a blink session 
    if ( millis() - blinkN_millis >  blinkN_interval )  { 
      if(do_N_on) { //use a flag to determine wether to turn on or off the Blink LED
        digitalWrite(blink_pin, HIGH);   // set the LED on, if okay to use power for it
        blinkN_millis = millis();
        blinkN_interval = blinkN_on_delay; // wait for a second
        do_N_on = false;
      }else{
        digitalWrite(blink_pin, LOW);    // set the LED off
        // set the time to do next blink 
        blinkN_millis = millis();
        blinkN_interval = blinkN_off_delay;  // wait for a second
        do_N_on = true;
        _blinks--;
        if(_blinks == 0) { 
          // a longer pause is necessary before doing next blink session
          blinkN_interval = blinkN_long_off_delay; 
          //next blink session will be; 
          if (_blink_minor) {
            _blinks = _blink_minor;
            _blink_minor = 0; 
          }  // else _blink_minor is already 0
        }//if
      }//else
    }//if 
  }else{ // no more blink sessions
    // do next blink, if a longer sequence is defined -:- to be implemented another day
  }
}//blinkN

// End
