
#include "Device.h"

class GasSensor : public Device
{
  public:
    GasSensor(String topic, void (*ISR_GASSensor)(), void (*mqtt_publish)(String, String));

    //reset
    void Reset_Alarm();
    void Set_Alarm();

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    bool gas_state;

    const int8_t GAS_SENSOR_PIN = 23;
};