#include "LED.h"

class LEDSingle : public LED {
  public:
    LEDSingle();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:

    const uint8_t SINGLE_LED_PIN = 12; //YELLOW LED

    void On();
    void Off();
    void Toggle();
};