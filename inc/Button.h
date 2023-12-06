#include "Device.h"

class Button : public Device
{
  public:
    Button(String topic, uint8_t pin_number, void (*ISR_Button)());

    void Pressed();
    void Reset();

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);
    int32_t ReadState();

  private:
    bool _button_state;
    uint8_t _pin_number;
};