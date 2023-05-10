/*
 *  This is a sample sketch to show how to use the ButtonOne Library
 * and the built-in LED in (a sort of) multitasking way
 *
 *  Four buttons will make the built-in LED blink in different ways
 *  
 *  - button 1 will toggle the LED between on and off
 *  
 *  - button 2 will blink the LED twice - and leave the LED off
 *  
 *  - button 3 will blink the LED 1.3 times  - and leave the LED off
 *      meaning: one blink - pause - three blinks
 *      
 *  - button 4 will blink the LED 2.2 times - and leave the LED off
 *      meaning: two blinks - pause - two blinks
 *      
 */
 
#include "ButtonOne.h"


//// declare buttons

// Setup a ButtonOne instance on pin D4  
ButtonOne button1(4);   // default active state is LOW

// Setup a ButtonOne instance on pin D5  
ButtonOne button2(5, LOW);  //it is possible to set the active state in the declaration

// Setup a ButtonOne instance on pin D6  
ButtonOne button3(6);  //it is possible to set the active state later. See button3.setActiveState() in setup()

// Setup a ButtonOne instance on pin D7  
ButtonOne button4(7);   // default active state is LOW

//// LED pin declaration
const byte blink_pin = 13;    //the pin number that the LED is connected to

//// global variables for 'Blik N times' function
byte _blinks = 0;
byte _blink_minor = 0;
int blinkN_on_delay = 100;       //change this value to adjust the number of MilliSeconds the LED is ON
int blinkN_off_delay = 100;      //change this value to adjust the number of MilliSeconds the LED is OFF
int blinkN_long_off_delay = 600; // milli seconds between major and minior blinks


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // enable the standard led on pin 13.
  pinMode(blink_pin, OUTPUT);      // sets the digital pin as output

  //initiate internal button management
  button1.begin(); 
  button2.begin();
  button3.begin();
  button4.begin();

  // link the Press function to be called on a button Press event.   
  button1.attachPress(btn1Press);
  button2.attachPress(btn2Press);
  button3.attachPress(btn3Press);
  button3.setActiveState(LOW);      // set button3 to be active on LOW
  button4.attachPress(btn4Press);
} // END setup()


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push buttons:
  button1.check();
  button2.check();
  button3.check();
  button4.check();

  // update blink LED 
  blinkN(); 
  
  // You can implement other code in here 
  
} // END loop()


//*********************************************
// button actions
//*********************************************

// this function will be called when button1 is pressed 
void btn1Press() {
  static byte m = LOW;   //used so we can toggle the LED 
  
  // reverse the LED 
  m = !m;

  // write to the LED pin
  digitalWrite(blink_pin, m);
} //END btn1Press

// this function will be called when button2 is pressed 
void btn2Press() {
  blinkN(2);  // blink twice
} // END btn1Press

// this function will be called when button3 is pressed 
void btn3Press() {
  blinkN(1,3);  // blink once - pause - then three times
} // END btn1Press

// this function will be called when button4 is pressed 
void btn4Press() {
  blinkN(2,2);  // blink twice - pause - then twice again 
} // END btn1Press



//*********************************************
// blink functions
//*********************************************

// blinkN function can be called with or without parameters

void blinkN(byte major){
  _blinks = major;
  _blink_minor = 0;
}//END blinkN(major)

void blinkN(byte major, byte minor){
  _blinks = major;
  _blink_minor = minor; 
}//END blinkN(major, minor)

void blinkN() {
  static unsigned long blinkN_millis = 0;
  static unsigned long blinkN_interval = 0;
  static unsigned long currentMillis = 0;         // stores the current millis(), eliminating the need to call millis() several times
  static boolean do_N_on = true;
  
  currentMillis = millis();
  if(_blinks > 0) { // still do a blink session 
    if ( currentMillis - blinkN_millis >  blinkN_interval )  { 
      if(do_N_on) { //use a flag to determine wether to turn on or off the Blink LED
        digitalWrite(blink_pin, HIGH);   // set the LED on, if okay to use power for it
        blinkN_millis = currentMillis;
        blinkN_interval = blinkN_on_delay; // wait for a second
        do_N_on = false;
      }else{
        digitalWrite(blink_pin, LOW);    // set the LED off
        // set the time to do next blink 
        blinkN_millis = currentMillis;
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
    // do next blink, if a longer sequence is defined -:- to be implemented at a later date
  }//else
} // END blinkN()

// End Sketch
