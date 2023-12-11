#include "../inc/Debug.h"
#include "../inc/Button.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Button::Button(const char* topic, uint8_t pin_number, void (*ISR_Button)() ) :
    Device(topic), _pinNumber(pin_number)
{
    _ISR_Button = ISR_Button;
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void Button::Init(){
    pinMode(_pinNumber, INPUT);

    // we will use isr approach
    attachInterrupt(digitalPinToInterrupt(_pinNumber), _ISR_Button, CHANGE);
}
void Button::Pressed()
{
    _buttonState = true;
}
void Button::Reset(){
    _buttonState = false;
}

const char* Button::Get_Current_State(){
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _buttonState ? '1' : '0');
    return jsonBuffer;
}


/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/

