
#include "Device.h"

class SteamSensor : public Device
{
  public:
    SteamSensor(String topic);

    int32_t Get_Data();
    
    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);

  private:
    uint32_t _data;

    const int8_t STEAM_SENSOR_PIN = 34;
};