// -----
// ButtonOne.h - Library for detecting and debouncing a button press on a single button.
// This class is implemented for use with the Arduino environment.
// by MrAlvin -  alvin@3iii.dk - Update: May 2023 - Initial creation: Jan 2016
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
  int getPressDebounceTime(void);
  void setReleaseDebounceTime(int ms_ticks);  // set # of millisec that have to pass before we test to see if the button state has changed
  int getReleaseDebounceTime(void);
  void setLongPressTime(int ms_ticks);        // set #  of milliseconds that have to pass before a long press event has occurred
  int getLongPressTime(void);
  void setRepeatPressTime(int ms_ticks);      // set #  of milliseconds that have to pass before the first repeat press event has occurred
  int getRepeatPressTime(void);
  void setRepeatPressTime2(int ms_ticks);     // set #  of milliseconds that have to pass before the subsequent repeat press event has occurred
  int getRepeatPressTime2(void);
  void setActiveState(bool state);     // choose if LOW or HIGH is the active state of the push button
  int getActiveState(void);
  void currentStateIsInactiveState(void);  // read current state of button, and set it to be the inacive state
  void setToggleAsPush(void); // call this function if you want a toggle switch to act as a push button.

  // attach functions that will be called when button was pressed
  void attachPress(callbackFunction newFunction);     // called when ever a button is pressed
  void attachRelease(callbackFunction newFunction);   // called whenever a button is released
  void attachLongPress(callbackFunction newFunction); // called whenever a button has been pressed for longer than _longPress_time
  void attachRepeatPress(callbackFunction newFunction); // called whenever a button has been pressed for longer than _repeatPress_time
    
  // ----- State machine functions -----

  // call this function every some milliseconds for handling button events.
  boolean check(void); // needs to be called often to allow all states of the button to be processed
  
  // hardware detached button state evaluation and debounce machine  
 void buttonEvaluate(boolean buttonLevel);  
 
private:
  byte _pin;                // hardware pin number. 
  int _pressDebounceTime;   // number of milli seconds that have to pass  before we test to see if the button state has changed
  int _releaseDebounceTime; // number of milli seconds that have to pass  before we test to see if the button state has changed
  int _longPressTime;       // number of milli seconds that have to pass  before we consider a long press event to have occured
  int _repeatPressTimeInitial;        // number of milli seconds that have to pass  before we consider a repeat press event to have occured
  int _repeatPressTimeSubsequent;     // number of milli seconds that have to pass  before we consider the next repeat press event to have occured
  bool _long_press_registered; // helps to ensure only one long press event until button is released
  bool _active_state;       // when reading this state,  we register a push of the button
  bool _btnEngagedState;    // true - when a push has been detected : false - when a release has been detected
  bool _toggleAsPush;       // using a toggle switch as a push button, allowing the user to simply toggle the switch once, to activate as a push
  int _toggleRestTime;      // number of milli seconds that have to pass  before we  consider the current switch state, as the rest-state of a toggle switch
  


  // These variables will hold functions acting as event source.
  callbackFunction _pressFunction;
  callbackFunction _releaseFunction;
  callbackFunction _longPressFunction;
  callbackFunction _repeatPressFunction;

  // These variables that hold information across the upcoming check calls.
  // They are initialized once on program start and are updated every time the check function is called.
  int _state_idx;    // index in the state machine
  unsigned long  _btn_millis;    // time in milli seconds.
  unsigned long  _start_millis;  // time in milli seconds.
  unsigned long _currentMillis;  // time in milli seconds.
  unsigned int _repeatPressTimeInterval; // time in milli seconds.
  
};

#endif


