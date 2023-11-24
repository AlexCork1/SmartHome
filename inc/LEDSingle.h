#include "LED.h"

class LEDSingle : public LED {
  public:
    LEDSingle(String topic);

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);

  private:
    const uint8_t SINGLE_LED_PIN = 12; //YELLOW LED

    void On();
    void Off();
    void Toggle();
};