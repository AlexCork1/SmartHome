#include "../inc/LEDRGB.h"
#include "../inc/Debug.h"

/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LEDRGB::LEDRGB() : _rgbLights(LED_TYPE, LED_TYPE_IS_RGBW){
  _led_state = 0;
  _red_channel = 0;
  _blue_channel = 0;
  _green_channel = 0;
  
  _rgbLights.begin(RGB_PIN, 4);
  _rgbLights.brightness(BRIGHTNESS);
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
String LEDRGB::Get_Current_State(){
  return String(_led_state) + "-" + String(_red_channel) + "-" + String(_green_channel) + "," + String(_blue_channel);
}
String LEDRGB::MQTT_Get_topic(){
  return String("ledRGB");
}
void LEDRGB::MQTT_Message_Subscribe(String message){
  if (message == "On"){
    On();
    return;
  }

  if (message == "Off"){
    Off();
    return;
  }
    
  if (message == "Toggle"){
    Toggle();
    return;
  }
  if (message.startsWith("SetColor")){
      //Input string: SetColor-LED-R-G-B
      int32_t led = 0, red = 0, green = 0, blue = 0;
      { //parse input message
        String input = message;
        String messageHeader = input.substring(0, input.indexOf('-'));
        input = input.substring(input.indexOf('-')+1);
        led = input.substring(0, input.indexOf('-')).toInt();
        Debugln(led);

        input = input.substring(input.indexOf('-')+1);
        red = input.substring(0, input.indexOf('-')).toInt();
        Debugln(red);

        input = input.substring(input.indexOf('-')+1);
        green = input.substring(0, input.indexOf('-')).toInt();
        Debugln(green);

        blue = input.substring(input.indexOf('-')+1).toInt();
        Debugln(blue);
      }
      SetColor(led, red, green, blue);
  }
}
void LEDRGB::MQTT_Message_Publish(){
  //MQTT_publish(MQTT_topic().c_str(), GetData().c_str());
  //TODO
}


/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
void LEDRGB::On(){
  _led_state = true;
  _rgbLights.brightness(BRIGHTNESS);
}

void LEDRGB::Off(){
  _led_state = false;
  _rgbLights.brightness(0);
}

void LEDRGB::Toggle(){
  if (_led_state == false)
    On();
  else
    Off();
}
void LEDRGB::SetColor(uint32_t led, uint32_t red, uint32_t green, uint32_t blue){
  uint32_t color_to_set = ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF);
  Debug("Barva: "); Debugln(color_to_set)

  _rgbLights.setPixel(led, color_to_set, 1);
  On();
}