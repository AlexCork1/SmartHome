#include "../inc/Debug.h"
#include "../inc/Button.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Button::Button(
    String openning_description,
    uint8_t pin_number,
    void (*ISR_Button)()) :
    _pin_number(pin_number), _opening_desc(openning_description)
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
/* return single LED MQTT topic as String */
String Button::MQTT_Get_topic()
{
    return _opening_desc;
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Button::MQTT_Message_Subscribe(String message)
{
    // NOTHING - it is only send data
}
void Button::MQTT_Message_Publish()
{
    // TODO
    // MQTT_publish(MQTT_Get_topic().c_str(), GetData().c_str());
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/

