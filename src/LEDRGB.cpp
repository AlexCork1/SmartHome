#include "../inc/LEDRGB.h"
#include "../inc/Debug.h"

/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LEDRGB::LEDRGB(String topic) : 
  LED(topic),
   _rgbLights(LED_TYPE, LED_TYPE_IS_RGBW),
   _led0(0, {0,0,0}),
   _led1(1, {0,0,0}),
   _led2(2, {0,0,0}),
   _led3(3, {0,0,0})
{
  _led_state = 0;
  
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
  return  "{ \"state\":" + String(_led_state) + ","
    "\"0\": ["  + String(_led0.color.red) + "," + String(_led0.color.green) + "," + String(_led0.color.blue) +"]," +
    "\"1\": ["  + String(_led1.color.red) + "," + String(_led1.color.green) + "," + String(_led1.color.blue) +"]," + 
    "\"2\": ["  + String(_led2.color.red) + "," + String(_led2.color.green) + "," + String(_led2.color.blue) +"]," + 
    "\"3\": ["  + String(_led3.color.red) + "," + String(_led3.color.green) + "," + String(_led3.color.blue) +"] }";
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
      uint8_t led = 0, red = 0, green = 0, blue = 0;
      { //parse input message
        String input = message;
        String messageHeader = input.substring(0, input.indexOf('-'));
        input = input.substring(input.indexOf('-')+1);
        led = input.substring(0, input.indexOf('-')).toInt() & 0xFF;
        Debugln(led);

        input = input.substring(input.indexOf('-')+1);
        red = input.substring(0, input.indexOf('-')).toInt() & 0xFF;
        Debugln(red);

        input = input.substring(input.indexOf('-')+1);
        green = input.substring(0, input.indexOf('-')).toInt() & 0xFF;
        Debugln(green);

        blue = input.substring(input.indexOf('-')+1).toInt() & 0xFF;
        Debugln(blue);
      }
      SetColor(led, red, green, blue);
  }
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
  _rgbLights.brightness(BRIGHTNESS, 1);
}

void LEDRGB::Off(){
  _led_state = false;
  _rgbLights.brightness(0, 1);
}

void LEDRGB::Toggle(){
  if (_led_state == false)
    On();
  else
    Off();
}
void LEDRGB::SetColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue)
{
  //error checking
  if (led >= 4) return;

  rgb_t colorToSet = { .red = red, .green = green, .blue = blue };

  if (led == 0) _led0.color = colorToSet;
  else if (led == 1) _led1.color = colorToSet;
  else if (led == 2) _led2.color = colorToSet;
  else if (led == 3) _led3.color = colorToSet;
  
  uint32_t color_to_set = (red << 16) | (green << 8) | (blue);
  Debug("Color: "); Debugln(color_to_set);

  //set color for RGB LED
  _rgbLights.setPixel(led, color_to_set, 1);
  On();
}