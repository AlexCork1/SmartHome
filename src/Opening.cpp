#include "../inc/Debug.h"
#include "../inc/Opening.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Opening::Opening(
    String topic,
    uint8_t pin_number,
    uint32_t channel_number) :
    Device(topic),
    _pin_number(pin_number),
    _channel_number(channel_number)
{
    ledcSetup(_channel_number, FREQUENCY, RESOLUTION);
    ledcAttachPin(_pin_number, _channel_number);
    Close();
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
/* return single LED state as String */
String Opening::Get_Current_State()
{
    return "{ \"state\":" + String(_opening_state) + " }";
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Opening::MQTT_Message_Subscribe(String message)
{
    if (message == "open")
        Open();
    else if (message == "close")
        Close();
    else
    {
        Debugln("Unrecognized message");
    }
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
/* Open window/door */
void Opening::Open()
{
    _opening_state = true;
    ledcWrite(_channel_number, OPEN_STATE);
}

/* Close window/door  */
void Opening::Close()
{
    _opening_state = false;
    ledcWrite(_channel_number, CLOSED_STATE);
}
