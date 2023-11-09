#include "LED.h"
//library:
//    https://reference.arduino.cc/reference/en/libraries/liteled/
//    https://github.com/Xylopyrographer/LiteLED/tree/main
#include <LiteLED.h>

class LEDRGB : public LED {
  public:
    LEDRGB();
    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish(); 

  private:
    LiteLED _rgbLights;
    int _red_channel;
    int _blue_channel;
    int _green_channel;
    const int BRIGHTNESS = 20;

    void On();
    void Off();
    void Toggle();
    void SetColor(int led, int red, int green, int blue);

};