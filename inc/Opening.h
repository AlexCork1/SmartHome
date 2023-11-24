#include "Device.h"

class Opening : public Device
{
  public:
    Opening(String topic, uint8_t pin_number, uint32_t channel_number);

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);

  private:
    bool _opening_state;
    uint8_t _pin_number;
    uint32_t _channel_number;

    const uint32_t FREQUENCY = 50;
    const uint32_t RESOLUTION = 10;
    const uint32_t CLOSED_STATE = (((1 << RESOLUTION) * 0.5) / ( 1000 / FREQUENCY));
    const uint32_t OPEN_STATE = (((1 << RESOLUTION) * 2.5) / ( 1000 / FREQUENCY));

    void Open();
    void Close();
};