#include "../inc/Debug.h"
#include "../inc/Opening.h"

constexpr const char Opening::OPEN_COMMAND[];
constexpr const char Opening::CLOSE_COMMAND[];
constexpr const char Opening::TOGGLE_COMMAND[];

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Opening::Opening(
    const char*  topic,
    uint8_t pin_number,
    uint32_t channel_number) :
    Device(topic),
    _pinNumber(pin_number),
    _channelNumber(channel_number)
{
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void Opening::Init(){
    ledcSetup(_channelNumber, FREQUENCY, RESOLUTION);
    ledcAttachPin(_pinNumber, _channelNumber);
    Close();

    Debug("CLOSE:");Debugln(CLOSED_STATE);
    Debug("OPEN:");Debugln(OPEN_STATE);
}
const char* Opening::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _openingState == OpeningState::Open ? '1' : '0');
    return jsonBuffer;
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Opening::MQTT_Message_Subscribe(const String& message)
{
    if (strcmp(message.c_str(), OPEN_COMMAND) == 0) Open();
    else if (strcmp(message.c_str(), CLOSE_COMMAND) == 0) Close();
    else if (strcmp(message.c_str(), TOGGLE_COMMAND) == 0) Toggle();
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
    _openingState = OpeningState::Open;
    
    //gradully opening door
    for (uint32_t currentState = CLOSED_STATE; currentState < OPEN_STATE; currentState = currentState + 20){
        ledcWrite(_channelNumber, currentState);
        delay(30);
    }
    ledcWrite(_channelNumber, OPEN_STATE);
}

/* Close window/door  */
void Opening::Close()
{
    _openingState = OpeningState::Closed;

    //gradully closing door
    for (uint32_t currentState = OPEN_STATE; currentState > CLOSED_STATE; currentState = currentState - 20){
        ledcWrite(_channelNumber, currentState);
        delay(30);
    }

    ledcWrite(_channelNumber, CLOSED_STATE);
}
void Opening::Toggle(){
    if (_openingState == OpeningState::Open)
        Close();
    else
        Open();
}