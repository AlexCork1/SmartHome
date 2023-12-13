#include "../inc/LEDRGB.h"
#include "../inc/Debug.h"
#include <sstream>


/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LEDRGB::LEDRGB(const char* topic) : 
  LED(topic),
   _rgbLights(LED_TYPE, LED_TYPE_IS_RGBW),
  _led0{0,0,0,0},
  _led1{1,0,0,0},
  _led2{2,0,0,0},
  _led3{3,0,0,0}
{  
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
void LEDRGB::Init(){
  _rgbLights.begin(RGB_PIN, 4);
  _rgbLights.brightness(BRIGHTNESS);
}
const char* LEDRGB::Get_Current_State(){
  snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT,
           _led0.red, _led0.green, _led0.blue,
           _led1.red, _led1.green, _led1.blue,
           _led2.red, _led2.green, _led2.blue,
           _led3.red, _led3.green, _led3.blue);
  return jsonBuffer;
}
void LEDRGB::MQTT_Message_Subscribe(const String& message){
  RgbLedCommand command = RgbLedCommand::Unknown;

  if(message.startsWith("SetColor"))
    command = RgbLedCommand::SetColor;

  Process_Command(command, message);
}

/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
void LEDRGB::SetColor(RGB_LED rgbled)
{
  Debugln("SetColor : " + String(rgbled.ledNumber) + " " + String(rgbled.red) + " " + String(rgbled.green) + " " + String(rgbled.blue));

  //error checking
  if (rgbled.ledNumber >= 4){
    Debugln("LEDRGB :: SetColor :: Wrong led number");
    return;
  }

  //overwrite previous value
  *_leds[rgbled.ledNumber] = rgbled;
  //changle color of led
  _rgbLights.setPixel(
    rgbled.ledNumber, 
    (((uint32_t)rgbled.red) << 16) | (((uint32_t)rgbled.green) << 8) | ((uint32_t)rgbled.blue),
    1);
}
void LEDRGB::Process_Command(RgbLedCommand command, const String& message){
  switch (command) {
    case RgbLedCommand::SetColor:
      SetColor(Parse_Color(message));
      break;
    case RgbLedCommand::Unknown:
      Debugln("LedSingle :: Unknown command");
      break;
  }
}
RGB_LED LEDRGB::Parse_Color(const String& message) {
  RGB_LED led;
  //SetColor-1-255-255-0
  int converted = std::sscanf(message.c_str(),
    "SetColor-%u-%u-%u-%u", 
    &led.ledNumber,
    &led.red,
    &led.green,
    &led.blue);

  if (converted != 4){
    Debugln(F("LEDRGB ::: Parse color error"));
    led.ledNumber = 0;
    led.red = 0;
    led.blue = 0;
    led.green = 0;
  }
  return led;
}