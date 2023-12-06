
#include "Device.h"

class GasSensor : public Device
{
  public:
    GasSensor(String topic, void (*ISR_GASSensor)());

    //reset
    void Reset_Alarm();
    void Set_Alarm();

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);
    int32_t ReadState();

  private:
    bool gas_state;

    const int8_t GAS_SENSOR_PIN = 23;
};