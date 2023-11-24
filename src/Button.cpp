#include "../inc/Debug.h"
#include "../inc/Button.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Button::Button(String topic, uint8_t pin_number, void (*ISR_Button)() ) :
    Device(topic), _pin_number(pin_number)
{
    pinMode(_pin_number, INPUT);

    // we will use isr approach
    attachInterrupt(digitalPinToInterrupt(_pin_number), ISR_Button, FALLING);
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void Button::Pressed()
{
    _button_state = true;
}
void Button::Reset(){
    _button_state = false;
}

/* return single LED state as String */
String Button::Get_Current_State()
{
    return String(_button_state);
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Button::MQTT_Message_Subscribe(String message)
{
    // NOTHING - it is only send data
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/

