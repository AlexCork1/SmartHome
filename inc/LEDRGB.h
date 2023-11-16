#include "LED.h"
//library:
//    https://reference.arduino.cc/reference/en/libraries/liteled/
//    https://github.com/Xylopyrographer/LiteLED/tree/main
#include <LiteLED.h>

class LEDRGB : public LED {
  public:
    LEDRGB(String topic, void (*mqtt_publish)(String, String));
    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish(); 

  private:
    LiteLED _rgbLights;
    uint16_t _red_channel;
    uint16_t _blue_channel;
    uint16_t _green_channel;
    const uint8_t BRIGHTNESS = 20;
    const uint8_t LED_TYPE_IS_RGBW = 0;
    const uint8_t RGB_PIN = 26;
    #define LED_TYPE        LED_STRIP_SK6812

    void On();
    void Off();
    void Toggle();
    void SetColor(uint32_t led, uint32_t red, uint32_t green, uint32_t blue);

};