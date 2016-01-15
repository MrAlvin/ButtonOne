// -----
// ButtonOne.h - Library for detecting and debouncing a button press on a single button.
// This class is implemented for use with the Arduino environment.
// by MrAlvin -  alvin@labitat.dk - Jan 2016
//
// ButtonOne is inspired by OneButton ground work, done by Matthias Hertel, http://www.mathertel.de
// -----

#ifndef OneButton_h
#define OneButton_h

#include "Arduino.h"

// ----- Callback function types -----

extern "C" {
  typedef void (*callbackFunction)(void);
}


class ButtonOne
{
public:
  // ----- Constructor -----
  ButtonOne(byte pin);
  ButtonOne(uint8_t pin, bool state) ;
    
  // ----- Set runtime parameters -----
  void begin(void) ;
  void setPressDebounceTime(int ms_ticks);    // set # of millisec that have to pass before we test to see if the button state has changed
  void setReleaseDebounceTime(int ms_ticks);  // set # of millisec that have to pass before we test to see if the button state has changed
  void setActiveState(bool state);     // choose if LOW or HIGH is the active state of the push button
  void currentStateIsInactiveState(void);  // read current state of button, and set it to be the inacive state
  void setToggleAsPush(void); // call this function if you want a toggle switch to act as a push button.

  // attach functions that will be called when button was pressed
  void attachPress(callbackFunction newFunction);     // called when ever a button is pressed
  void attachRelease(callbackFunction newFunction);   // called whenever a button is released
    
  // ----- State machine functions -----

  // call this function every some milliseconds for handling button events.
  boolean check(void); // needs to be called often to allow all states of the button to be processed
  
  // hardware detached button state evaluation and debounce machine  
 void buttonEvaluate(boolean buttonLevel);  
 
private:
  byte _pin;        // hardware pin number. 
  int _pressDebounceTime;   // number of milli seconds that have to pass  before we test to see if the button state has changed
  int _releaseDebounceTime; // number of milli seconds that have to pass  before we test to see if the button state has changed
  bool _active_state;         // when reading this state,  we register a push of the button
  bool _btnEngagedState;         // true - when a push has been detected : false - when a release has been detected
  bool _toggleAsPush;  // using a toggle switch as a push button, allowing the user to simply toggle the switch once, to activate as a push
  int _toggleRestTime;    // number of milli seconds that have to pass  before we  consider the current switch state, as the rest-state of a toggle switch


  // These variables will hold functions acting as event source.
  callbackFunction _pressFunction;
  callbackFunction _releaseFunction;

  // These variables that hold information across the upcoming check calls.
  // They are initialized once on program start and are updated every time the check function is called.
  int _state_idx;    // index in the state machine
  unsigned long  _btn_millis;    // time in milli seconds.
};

#endif


