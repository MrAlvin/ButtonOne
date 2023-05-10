/*
 * This is a sample sketch to show how to use the ButtonOne Library
 * to detect button press events on 9 buttons 
 *
 * Test circuit:
 *    Connect a pushbutton between pin A5 (ButtonPin) and ground.
 *    continue to connect push buttons on pins:    A4, A3, A2, A1, A0, 12, 11, 10
 *    
 * The Serial interface is used as a debug option for detection of a button press.
 * 
 */

#include "ButtonOne.h"

// Setup ButtonOne instances
ButtonOne button1(A5);
ButtonOne button2(A4);
ButtonOne button3(A3);
ButtonOne button4(A2);
ButtonOne button5(A1);
ButtonOne button6(A0);
ButtonOne button7(12);
ButtonOne button8(11);
ButtonOne button9(10);

//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  // Setup the Serial port. 
  Serial.begin(9600);
  Serial.println( F("Starting All-Buttons...") );

  //initiate internal button management values
  button1.begin();
  button2.begin();
  button3.begin();
  button4.begin();
  button5.begin();
  button6.begin();
  button7.begin();
  button8.begin();
  button9.begin();
  
  // link the button Press  functions.
  button1.attachPress(btn1Press);
  button2.attachPress(btn2Press);
  button3.attachPress(btn3Press);
  button4.attachPress(btn4Press);
  button5.attachPress(btn5Press);
  button6.attachPress(btn6Press);
  button7.attachPress(btn7Press);
  button8.attachPress(btn8Press);
  button9.attachPress(btn9Press);
  
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
  button5.check();
  button6.check();
  button7.check();
  button8.check();
  button9.check();

  // You can implement other code in here or just wait a while 

} // / END loop()



//*********************************************
// button functions
//*********************************************

// This function will be called when the button1 is pressed 
void btn1Press() {
  Serial.println( F("Button 1 pressed.") );
} // END btn1Press()

// This function will be called when the button2 is pressed 
void btn2Press() {
  Serial.println( F("Button 2 pressed.") );
} // END btn2Press()

// This function will be called when the button3 is pressed 
void btn3Press() {
  Serial.println( F("Button 3 pressed.") );
} // END btn3Press()

// This function will be called when the button4 is pressed 
void btn4Press() {
  Serial.println( F("Button 4 pressed.") );
} // END btn4Press()

// This function will be called when the button5 is pressed 
void btn5Press() {
  Serial.println( F("Button 5 pressed.") );
} // END btn5Press()

// This function will be called when the button6 is pressed 
void btn6Press() {
  Serial.println( F("Button 6 pressed.") );
} // END btn6Press()

// This function will be called when the button7 is pressed 
void btn7Press() {
  Serial.println( F("Button 7 pressed.") );
} // END btn7Press()

// This function will be called when the button8 is pressed 
void btn8Press() {
  Serial.println( F("Button 8 pressed.") );
} // END btn8Press()

// This function will be called when the button9 is pressed 
void btn9Press() {
  Serial.println( F("Button 9 pressed.") );
} // END btn9Press()

// END Sketch
