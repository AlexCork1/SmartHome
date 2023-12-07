#include "../inc/Debug.h"
#include "../inc/LEDSingle.h"

constexpr const char LEDSingle::ON_COMMAND[];
constexpr const char LEDSingle::OFF_COMMAND[];
constexpr const char LEDSingle::TOGGLE_COMMAND[];


/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LEDSingle::LEDSingle(const char* topic) : LED(topic)
{
  pinMode(SINGLE_LED_PIN, OUTPUT);
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
/* return single LED state as String */
String LEDSingle::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _ledState == LedState::On ? '1' : '0');
    return String(jsonBuffer);
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void LEDSingle::MQTT_Message_Subscribe(const String& message){
  LedCommand command = LedCommand::Unknown;
  if (strcmp(message.c_str(), ON_COMMAND) == 0) command = LedCommand::On;
  else if (strcmp(message.c_str(), OFF_COMMAND) == 0) command = LedCommand::Off;    
  else if (strcmp(message.c_str(), TOGGLE_COMMAND) == 0) command = LedCommand::Toggle;
  
  Process_Command(command);
}

/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
/* Turn the single LED on */
void LEDSingle::On(){
  _ledState = LedState::On;
  digitalWrite(SINGLE_LED_PIN, HIGH);
}

/* Turn the single LED off */
void LEDSingle::Off(){
  _ledState = LedState::Off;
  digitalWrite(SINGLE_LED_PIN, LOW);
}

/* Toggle the state of the single LED */
void LEDSingle::Toggle(){
  if (_ledState == LedState::Off)
    On();
  else
    Off();
}

void LEDSingle::Process_Command(LedCommand command){
  switch (command) {
    case LedCommand::On:
      On();
      break;
    case LedCommand::Off:
      Off();
      break;
    case LedCommand::Toggle:
      Toggle();
      break;
    case LedCommand::Unknown:
      Debugln("LedSingle :: Unknown command");
      break;
  }
}