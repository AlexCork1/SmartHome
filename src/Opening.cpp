#include "../inc/Debug.h"
#include "../inc/Opening.h"

constexpr const char Opening::OPEN_COMMAND[];
constexpr const char Opening::CLOSE_COMMAND[];

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
    ledcSetup(_channelNumber, FREQUENCY, RESOLUTION);
    ledcAttachPin(_pinNumber, _channelNumber);
    Close();
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
String Opening::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _openingState == OpeningState::Open ? '1' : '0');
    return String(jsonBuffer);
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Opening::MQTT_Message_Subscribe(const String& message)
{
    OpeningCommand command = OpeningCommand::Unknown;
    if (strcmp(message.c_str(), OPEN_COMMAND) == 0) command = OpeningCommand::Open;
    else if (strcmp(message.c_str(), CLOSE_COMMAND) == 0) command = OpeningCommand::Close;
    
    Process_Command(command);
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
    ledcWrite(_channelNumber, OPEN_STATE);
}

/* Close window/door  */
void Opening::Close()
{
    _openingState = OpeningState::Closed;
    ledcWrite(_channelNumber, CLOSED_STATE);
}

void Opening::Process_Command(OpeningCommand command){
    switch (command)
    {
    case OpeningCommand::Open:
        Open();
        break;
    
    case OpeningCommand::Close:
        Close();
        break;

    default:
        Debugln("Opening :: Unknown command");
        break;
    }
}