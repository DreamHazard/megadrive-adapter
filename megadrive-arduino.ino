#include <Joystick.h> /* https://github.com/MHeironimus/ArduinoJoystickLibrary */
#include <SegaController.h> /* https://github.com/jonthysell/SegaController */


// Controller DB9 pins (looking face-on to the end of the plug):
//
// 5 4 3 2 1
//  9 8 7 6
//
// Connect pin 5 to +5V and pin 8 to GND
// Connect the remaining pins to digital I/O pins (see below)

// Specify the Arduino pins that are connected to
// DB9 Pin 7, DB9 Pin 1, DB9 Pin 2, DB9 Pin 3, DB9 Pin 4, DB9 Pin 6, DB9 Pin 9
SegaController controller(8, 2, 3, 4, 5, 6, 7);

// Controller states
word currentState = 0;
word lastState = 0;


//joystick initialisation - 8 buttons (including Mode), 1 hat
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 1,                  // Button Count, Hat Switch Count
  false, false, false,   // No standard analog Axes
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup()
{
    Joystick.begin();
}

void loop()
{
    currentState = controller.getState();
    sendState();
}



void sendState()
{
    // Only report controller state if it's changed
    if (currentState != lastState)
    {
        Joystick.setButton(0, ((currentState & SC_BTN_A) > 0));//each pin's value is different, however they are all > 0 so outputting the bool as the button value was the easiest way
        Joystick.setButton(1, ((currentState & SC_BTN_B) > 0));
        Joystick.setButton(2, ((currentState & SC_BTN_C) > 0));
        Joystick.setButton(3, ((currentState & SC_BTN_X) > 0));
        Joystick.setButton(4, ((currentState & SC_BTN_Y) > 0));
        Joystick.setButton(5, ((currentState & SC_BTN_Z) > 0));
        Joystick.setButton(6, ((currentState & SC_BTN_START) > 0));
        Joystick.setButton(7, ((currentState & SC_BTN_MODE) > 0));


        //POV hat - this makes an 8-directional output which is not covered in the MHeironimus/ArduinoJoystickLibrary examples
        //Scan each of the four directional inputs (invalid combinations are skipped as they are physically impossible on a stock controller) and output the corresponding value for each direction to the hat
        if (((currentState & SC_BTN_UP) == 0) && ((currentState & SC_BTN_RIGHT) == 0) && ((currentState & SC_BTN_DOWN) == 0) && ((currentState & SC_BTN_LEFT) == 0)) 
        {
            Joystick.setHatSwitch(0, -1);
        } 
        else if (((currentState & SC_BTN_UP) > 0) && ((currentState & SC_BTN_RIGHT) == 0) && ((currentState & SC_BTN_DOWN) == 0) && ((currentState & SC_BTN_LEFT) == 0)) 
        {
            Joystick.setHatSwitch(0, 0);
        } 
        else if (((currentState & SC_BTN_UP) > 0) && ((currentState & SC_BTN_RIGHT) > 0) && ((currentState & SC_BTN_DOWN) == 0) && ((currentState & SC_BTN_LEFT) == 0))
        {
            Joystick.setHatSwitch(0, 45);
        } 
        else if (((currentState & SC_BTN_UP) == 0) && ((currentState & SC_BTN_RIGHT) > 0) && ((currentState & SC_BTN_DOWN) == 0) && ((currentState & SC_BTN_LEFT) == 0))
        {
            Joystick.setHatSwitch(0, 90);
        } 
        else if (((currentState & SC_BTN_UP) == 0) && ((currentState & SC_BTN_RIGHT) > 0) && ((currentState & SC_BTN_DOWN) > 0) && ((currentState & SC_BTN_LEFT) == 0))
        {
            Joystick.setHatSwitch(0, 135);
        } 
        else if (((currentState & SC_BTN_UP) == 0) && ((currentState & SC_BTN_RIGHT) == 0) && ((currentState & SC_BTN_DOWN) > 0) && ((currentState & SC_BTN_LEFT) == 0))
        {
            Joystick.setHatSwitch(0, 180);
        } 
        else if (((currentState & SC_BTN_UP) == 0) && ((currentState & SC_BTN_RIGHT) == 0) && ((currentState & SC_BTN_DOWN) > 0) && ((currentState & SC_BTN_LEFT) > 0))
        {
            Joystick.setHatSwitch(0, 225);
        } 
        else if (((currentState & SC_BTN_UP) == 0) && ((currentState & SC_BTN_RIGHT) == 0) && ((currentState & SC_BTN_DOWN) == 0) && ((currentState & SC_BTN_LEFT) > 0))
        {
            Joystick.setHatSwitch(0, 270);
        }         
        else if (((currentState & SC_BTN_UP) > 0) && ((currentState & SC_BTN_RIGHT) == 0) && ((currentState & SC_BTN_DOWN) == 0) && ((currentState & SC_BTN_LEFT) > 0))
        {
            Joystick.setHatSwitch(0, 315);
        } 
        

        
        lastState = currentState;
    }
}
