// -----
// ButtonOne.cpp - Library for detecting and debouncing a button press on a single button.
// This class is implemented for use with the Arduino environment.
// by MrAlvin -  alvin@3iii.dk - Update: May 2023 - Initial creation: Jan 2016
//
// ButtonOne is inspired by OneButton ground work, done by Matthias Hertel, http://www.mathertel.de
// -----
// Changelog: see ButtonOne.h
// -----

#include "ButtonOne.h"

// ----- Initialization and Default Values -----

ButtonOne::ButtonOne(uint8_t pin) {
  _pin = pin;
  _active_state = LOW;  // when reching this state, we register a push of the button
} // ButtonOne

ButtonOne::ButtonOne(uint8_t pin,  bool state) {
  _pin = pin;
  _active_state = state;  // when reching this state, we register a push of the button
} // ButtonOne

void ButtonOne::begin(void) {
  pinMode(_pin, INPUT_PULLUP);    // set the Button Pin as input and activate the internal Arduino pull-up resistor.
  
  _pressDebounceTime = 75;    // number of millisec that have to pass before we test to see if the button state has changed
  _releaseDebounceTime = 175; // number of millisec that have to pass before we test to see if the button state has changed
  _longPressTime = 700;       // number of milliseconds that have to pass before we register a long press
  _repeatPressTimeInitial = 700;    // number of milliseconds that have to pass before the first repeat press is registered
  _repeatPressTimeSubsequent = 200; // number of milliseconds that have to pass before the following repeat press events (RapidFire button)
  _toggleRestTime = 500;      // number of milli seconds that have to pass  before we  consider the current state, as the rest-state of a toggle switch
  _toggleAsPush = false;
  _currentMillis = millis();
  
  _pressFunction = NULL;
  _releaseFunction = NULL;
  _longPressFunction = NULL;
  _repeatPressFunction = NULL;
}

// explicitly set the number of milli sec that have to pass  before we test to see if the button state has changed
void ButtonOne::setPressDebounceTime(int ms_ticks) { 
  _pressDebounceTime = ms_ticks;
} // setPressDebounceTime

// getPressDebounceTime
int ButtonOne::getPressDebounceTime(void) { 
  return _pressDebounceTime;
} // return _pressDebounceTime


// explicitly set the number of milli sec that have to pass  before we test to see if the button state has changed
void ButtonOne::setReleaseDebounceTime(int ms_ticks) { 
  _releaseDebounceTime = ms_ticks;
} // setReleaseDebounceTime

// getReleaseDebounceTime;
int ButtonOne::getReleaseDebounceTime(void) { 
  return _releaseDebounceTime;
} // getReleaseDebounceTime;


// explicitely set the number of milli sec that have to pass  before  we  consider a long press to have occured
void ButtonOne::setLongPressTime(int ms_ticks) { 
  _longPressTime = ms_ticks;
} // setLongPressTime

// getLongPressTime
int ButtonOne::getLongPressTime(void) { 
  return _longPressTime;
} // getLongPressTime


// explicitely set the number of milli sec that have to pass before a repeat press event will occur
void ButtonOne::setRepeatPressTime(int ms_ticks) { 
  _repeatPressTimeInitial = ms_ticks;
} // setRepeatPressTime

// getRepeatPressTime
int ButtonOne::getRepeatPressTime(void) { 
  return _repeatPressTimeInitial;
} // getRepeatPressTime


// explicitely set the number of milli sec that have to pass before the next repeat press event will occur
void ButtonOne::setRepeatPressTime2(int ms_ticks) { 
  _repeatPressTimeSubsequent = ms_ticks;
} // setRepeatPressTimeSubsequent

// getRepeatPressTimeSubsequent
int ButtonOne::getRepeatPressTime2(void) { 
  return _repeatPressTimeSubsequent;
} // getRepeatPressTimeSubsequent


void ButtonOne::setActiveState(bool state){
  _active_state = state;
}

int ButtonOne::getActiveState(void){
  return _active_state;
}

void ButtonOne::currentStateIsInactiveState(void) {
	_active_state = !digitalRead(_pin);
}

void ButtonOne::setToggleAsPush(void) {
	_toggleAsPush = true;
	currentStateIsInactiveState();
}

// save function for Press event
void ButtonOne::attachPress(callbackFunction newFunction) {
  _pressFunction = newFunction;
} // attachPress

// save function for Release event
void ButtonOne::attachRelease(callbackFunction newFunction) {
  _releaseFunction = newFunction;
} // attachClick

// save function for long press event
void ButtonOne::attachLongPress(callbackFunction newFunction) {
  _longPressFunction = newFunction;
} // attachLongPress

// save function for long press event
void ButtonOne::attachRepeatPress(callbackFunction newFunction) {
  _repeatPressFunction = newFunction;
} // attachLongPress

boolean ButtonOne::check(void) {
  boolean pinLevel = digitalRead(_pin); // detect the hardware button state
  buttonEvaluate(pinLevel); 
  return _btnEngagedState;
}

void ButtonOne::buttonEvaluate(boolean buttonLevel) {
  _currentMillis = millis();
  switch ( _state_idx ) {
    case 0: // read btn - waiting for press
        if (buttonLevel == _active_state) {
          _btnEngagedState = true;
          _btn_millis = _currentMillis;     // ready for debounce and Click and LongPress detection
          _start_millis = _currentMillis;   // ready for repeatPress detection
          _long_press_registered = false;  // ready to register a long press
          _repeatPressTimeInterval = _repeatPressTimeInitial; // ready to register a initial repeat press
          _state_idx++;
          if ( _pressFunction) _pressFunction(); // call pressFunction  as one of the first things to do
        }  // if
        break;
        
    case 1: // debounce btn
        if (_currentMillis - _btn_millis > _pressDebounceTime)  { 
          _state_idx++; 
        } // if
        break;
        
    case 2: // read btn - waiting for release
        // if pin active as a toggle switch
		if( _toggleAsPush){ 
            // has toggle rest time passed
           if( _currentMillis - _btn_millis  > _toggleRestTime ) {
              _active_state = !_active_state; // toggel to new state as the active state
           }
		} else { // toggle buttons can not have LongPress
            // has a long press occurred
            if( _currentMillis - _btn_millis > _longPressTime ) {
               if (!_long_press_registered){
                 if (_longPressFunction) _longPressFunction();
                 _long_press_registered = true;
               }
            }
            // has a repeat press occurred
            if( _currentMillis - _start_millis > _repeatPressTimeInterval ) {
                if (_repeatPressFunction) _repeatPressFunction();
                // get ready for next repeat press event
                _start_millis = _currentMillis; // ready to register the next repeat press event
                _repeatPressTimeInterval = _repeatPressTimeSubsequent; // ready to register the next repeat press event
            }
        }
        // check to see if the button has been released
        if (buttonLevel == !_active_state) { // the button has been released
          _btnEngagedState = false; 
          _btn_millis = _currentMillis;  // ready for debounce
          _state_idx++;   // ready for debounce
          if (_releaseFunction) _releaseFunction(); 
        }
        break;
        
    case 3: // debounce btn
        if (_currentMillis - _btn_millis > _releaseDebounceTime)   {
          _state_idx = 0;  // ready to register next push action
        } // if
        break;

    default: 
        _state_idx = 0; 
        break;
  } // switch
  return;
} // check
// end.
