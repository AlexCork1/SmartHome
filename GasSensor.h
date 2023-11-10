
#include "Device.h"

class GasSensor : public Device
{
  public:
    GasSensor(void (*ISR_GASSensor)());

    //reset
    void Reset_Alarm();
    void Set_Alarm();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    bool gas_state;

    const int8_t GAS_SENSOR_PIN = 23;
};