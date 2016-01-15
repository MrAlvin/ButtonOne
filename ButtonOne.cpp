// -----
// ButtonOne.cpp - Library for detecting and debouncing a button press on a single button.
// This class is implemented for use with the Arduino environment.
// by MrAlvin -  alvin@labitat.dk - Jan 2016
//
// ButtonOne is inspired by OneButton ground work, done by Matthias Hertel, http://www.mathertel.de
// -----
// Changelog: see ButtonOne.h
// -----

#include "ButtonOne.h"

// ----- Initialization and Default Values -----

ButtonOne::ButtonOne(byte pin) {
  _pin = pin;
  _active_state = LOW;  // when reching this state, we register a push of the button
} // ButtonOne

ButtonOne::ButtonOne(uint8_t pin,  bool state) {
  _pin = pin;
  _active_state = state;  // when reching this state, we register a push of the button
} // ButtonOne

void ButtonOne::begin(void) {
  pinMode(_pin, INPUT_PULLUP);    // set the Button Pin as input and activate the internal Arduino pull-up resistor.
  
  _pressDebounceTime = 75;   // number of millisec that have to pass before we test to see if the button state has changed
  _releaseDebounceTime = 175; // number of millisec that have to pass before we test to see if the button state has changed
  _toggleRestTime = 500; // number of milli seconds that have to pass  before we  consider the current state, as the rest-state of a toggle switch
  _toggleAsPush = false;
  
  _pressFunction = NULL;
  _releaseFunction = NULL;
}

// explicitly set the number of millisec that have to pass  before we test to see if the button state has changed
void ButtonOne::setPressDebounceTime(int ms_ticks) { 
  _pressDebounceTime = ms_ticks;
} // setPressDebounceTime

// explicitly set the number of millisec that have to pass  before we test to see if the button state has changed
void ButtonOne::setReleaseDebounceTime(int ms_ticks) { 
  _releaseDebounceTime = ms_ticks;
} // setReleaseDebounceTime

void ButtonOne::setActiveState(bool state){
  _active_state = state;
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

boolean ButtonOne::check(void) {
  boolean pinLevel = digitalRead(_pin); // detect the hardware button state
  buttonEvaluate(pinLevel); 
  return _btnEngagedState;
}

void ButtonOne::buttonEvaluate(boolean buttonLevel) {
  switch ( _state_idx ) {
    case 0: // read btn - waiting for press
        if (buttonLevel == _active_state) {
          _btnEngagedState = true;
          _btn_millis = millis(); // ready for debounce and Click and LongPress detection
          if ( _pressFunction) _pressFunction();
          _state_idx++;
        }  // if
        break;
    case 1: // debounce btn
        if (millis() - _btn_millis > _pressDebounceTime)  { 
          _state_idx++; 
        } // if
        break;
    case 2: // read btn - waiting for release
		if( _toggleAsPush && ( millis() - _btn_millis  > _toggleRestTime )  ) {
          _active_state = !_active_state; // toggel to new state as the active state
		 }
        // check to see if the button has been released
        if (buttonLevel == !_active_state) { // the button has been released
          _btnEngagedState = false; 
          _btn_millis = millis();  // ready for debounce
          _state_idx++;   // ready for debounce
          if (_releaseFunction) _releaseFunction(); {
          }// if
        }
        break;
    case 3: // debounce btn
        if (millis() - _btn_millis > _releaseDebounceTime)   {
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
