#include "LED.h"
//library:
//    https://reference.arduino.cc/reference/en/libraries/liteled/
//    https://github.com/Xylopyrographer/LiteLED/tree/main
#include <LiteLED.h>


struct RGB_LED {
  uint8_t ledNumber;  //LED ID
  uint8_t red;        //LED red channel
  uint8_t green;      //LED green channel
  uint8_t blue;       //LED blue channel
};

class LEDRGB : public LED {
  public:
    enum class RgbLedCommand { On, Off, Toggle, SetColor, Unknown };
    LEDRGB(const char* topic);

    String Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override;

  private:
    LiteLED _rgbLights;
    RGB_LED _led0, _led1, _led2, _led3;

    RGB_LED* _leds[4] = { &_led0, &_led1, &_led2, &_led3 };

    const uint8_t BRIGHTNESS = 20;
    const uint8_t LED_TYPE_IS_RGBW = 0;
    const uint8_t RGB_PIN = 26;
    #define LED_TYPE        LED_STRIP_SK6812

    static constexpr uint8_t JSON_BUFFER_SIZE = 100;
    /// @brief 
    static constexpr const char* JSON_FORMAT = 
          "{ \"state\":%c,"
          "\"0\": [%03d,%03d,%03d],"
          "\"1\": [%03d,%03d,%03d],"
          "\"2\": [%03d,%03d,%03d],"
          "\"3\": [%03d,%03d,%03d] }";
    char jsonBuffer[JSON_BUFFER_SIZE];

    void On() override;
    void Off() override;
    void Toggle() override;
    void SetColor(RGB_LED rgbled);
    void Process_Command(RgbLedCommand command, const String& message);
    RGB_LED Parse_Color(const String& message);
};