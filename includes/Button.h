#include "Device.h"

class Button : public Device
{
  public:
    Button(String opening_description, uint8_t pin_number, void (*ISR_Button)());

    void Pressed();
    void Reset();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    bool _button_state;
    String _opening_desc;
    uint8_t _pin_number;
};