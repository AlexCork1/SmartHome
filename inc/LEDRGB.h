#include "LED.h"
//library:
//    https://reference.arduino.cc/reference/en/libraries/liteled/
//    https://github.com/Xylopyrographer/LiteLED/tree/main
#include <LiteLED.h>


struct RGB_LED {
  public:
    uint8_t ledNumber;  //LED ID
    rgb_t color;        //LED color

    // Konstruktor strukture
    RGB_LED(uint8_t number, rgb_t ledColor) : ledNumber(number), color(ledColor) {}
};

class LEDRGB : public LED {
  public:
    LEDRGB(String topic);
    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);

  private:
    LiteLED _rgbLights;

    RGB_LED _led0, _led1, _led2, _led3;

    const uint8_t BRIGHTNESS = 20;
    const uint8_t LED_TYPE_IS_RGBW = 0;
    const uint8_t RGB_PIN = 26;
    #define LED_TYPE        LED_STRIP_SK6812

    void On();
    void Off();
    void Toggle();
    void SetColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue);

};