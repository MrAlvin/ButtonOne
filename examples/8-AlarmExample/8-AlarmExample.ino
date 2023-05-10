/*
 * Alarm system example 
 * 
 *   State one: 2 LEDs blink alternatively
 * 
 *   State two: Upon press of the alarm button (or activation of Alarm Switch), 
 *               the 2 leds stop blinking, and an Alarm LED is lit.
 * 
 *               This state 2 is held, 
 *                until an Alarm-Release button is pressed
 *                and everything returns to State 1
 * 
 * Hardware:
 *   The alarm button/switch can be attached to pin 4 and/or pin 2
 *   as both pins will activate the alarm
 *     
 *    pin 4 is checked once in every loop
 *    pin2 has an interrupt function
 *    
 *    LEDs (and a limiting resistor (220 ohm to 560 ohm) 
 *    are attached to pins 9, 8 and 7
 *    
 *    
 *    This example is the result of a specific function request 
 *    made in an Arduino group on Facebook
 *    
 *    This example is basically created by combining three example sketches
 *    - blink_without_delay: is an example included with the Arduino IDE
 *    - interrupt example: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 *    - ButtoOne example: https://github.com/MrAlvin/ButtonOne/tree/master/examples/Button
 *    
 *    by MrAlvin, May 2023 
 *    
 */


#include "ButtonOne.h"  // https://github.com/MrAlvin/ButtonOne
                        // ButtonOne implements easy debounce of button presses
 

// constants won't change. Used here to set a pin number:
const int led1Pin =  9;            // the number of the LED pin
const int led2Pin =  8;            // the number of the LED pin
const int alarmLedPin =  7;        // the number of the LED pin

const byte interruptPin = 2;       // the number of the Button pin

// Setup Release_Alarm_Button
ButtonOne alarmReleaseButton(5);   // the number of the Button pin

// Setup Alarm_Button
ButtonOne alarmButton(4);          // the number of the Button pin

// Define two boolean states using ON/OFF
#define OFF false
#define ON true

// Variables that will change:
byte ledState = LOW;                // ledState used to set the blinking LEDs
volatile byte alarmState = OFF;     // volatile is used, as this variable is changed during the interrupt call

// You should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;         // Will store the current millis 
                                         // in a quick to reference variable
// constants won't change:
const unsigned long interval = 1000;     // interval at which to blink two LEDs (milliseconds)


// ------------------------------------------------------------------- //
//  setup()
//
void setup() {
  Serial.begin(115200); // serial port can be used for some debug info
  
  // set LED pins as output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(alarmLedPin, OUTPUT);


  // pinMode of ButtonOne pins are set within the library
  // with the with the function: button.begin()
  
  //activate the AlarmRelease button sensing
  alarmReleaseButton.begin();  
  // link to the Alarm Release Press function - that is called when the Alarm Release Button is pressed
  alarmReleaseButton.attachPress(alarmReleaseBtnPress);


  //activate the Alarm button sensing
  alarmButton.begin();
  // link to the Alarm Button Press function - that is called when the AlarmButton is pressed
  alarmButton.attachPress(alarmBtnPress);
  // sets an option to do something when the alarm button is released
  alarmButton.attachRelease(alarmBtnRelease); 


  // Enable interrupt on pin 2
  
  // pin2 is pulled high by the internal resistor
  pinMode(interruptPin, INPUT_PULLUP);
  
  // intFunc is called when pin 2 is pulled to LOW/GND
  attachInterrupt(digitalPinToInterrupt(interruptPin), intFunc, LOW); 
  
} // END setup()


// ------------------------------------------------------------------- //
//   loop()
//
void loop() {
  // here is where you'd put code that needs to be running all the time.
  
  // keep watching the buttons/switches
  alarmButton.check();
  alarmReleaseButton.check();

  // is there an alarm state
  if(alarmState){ 
    // yes - in an alarm state - the alarm button has been activated
    alarmLedOn(); 
    blink_leds_off();
  } else {  
    // not in an alarm state - no alarm button has been pressed 
    // or the alarm release button has been pressed
    alarmLedOff(); 
    blink_leds();
  }
  
  debug_status();  // gives an option to show stuff once a second via serial monitor
  
} // END loop()


// ------------------------------------------------------------------- //
//   Interrupt functon that is called when 
//      pin 2 is connected to ground 
//
void intFunc(){
  alarmState = ON;  
}


// ------------------------------------------------------------------- //
//   Alarm Release Button Press
//
void alarmReleaseBtnPress() {
  //Serial.println( F("Release Alarm Btn Pressed") );
  alarmState = OFF;
  digitalWrite(alarmLedPin, LOW); // turn LED off
} // END alarmReleaseBtnPress()


// ------------------------------------------------------------------- //
//   Alarm Button Press
//
void alarmBtnPress() {
  //Serial.println( F("Alarm Btn Pressed") );
  alarmState = ON;
} // END alarmBtnPress()


// ------------------------------------------------------------------- //
//   Alarm Button Released
//
void alarmBtnRelease(){
  // alarmState = OFF;
} // END alarmBtnRelease()


// ------------------------------------------------------------------- //
//   blink_leds()
//
void blink_leds(){
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // switch the LED state
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the blinking LEDs in opposite modes
    // turn one LED off and turn the other LED on
    digitalWrite(led1Pin, ledState);
    digitalWrite(led2Pin, !ledState);
  }
} // END blink_leds()


// ------------------------------------------------------------------- //
//   Turn Alarm LED off
//
void alarmLedOff(){
  digitalWrite(alarmLedPin, LOW); // turn LED off
} // END alarmLedOff()


// ------------------------------------------------------------------- //
//   Turn Alarm LED on
//
void alarmLedOn(){
  digitalWrite(alarmLedPin, HIGH); // turn LED on
} // END alarmLedOn()


// ------------------------------------------------------------------- //
//   Turn Blink LEDs off
//
void blink_leds_off(){
  //Turn OFF the blinking LEDs
  digitalWrite(led1Pin, LOW);  // turn LED off
  digitalWrite(led2Pin, LOW);  // turn LED off
} // blink_leds_off()


// ------------------------------------------------------------------- //
//   show something once a second
//
void debug_status() { 
  static unsigned long debug_millis = 0;
  static unsigned long debug_interval = 1000; // do something once a second
                                               // like, show the state of variables
  // is it time to show some debug info?
  if ( millis() - debug_millis >  debug_interval )  { 
      debug_millis = millis();  // get ready for the next interval

      //Serial.println( F("something") );        // use F() to store text in flashram only
      // Serial.println( F("something else") );   // F() saves RAM sopace
      Serial.println(alarmState);   
  }
}// END debug_status()
