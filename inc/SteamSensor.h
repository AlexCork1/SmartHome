
#include "Device.h"

class SteamSensor : public Device
{
  public:
    SteamSensor(const char* topic);

    bool Get_Data();
    
    const char* Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override { /* NOTHING - it is only sending data. Check ino file */ }

  private:
    uint32_t _data;

    const int8_t STEAM_SENSOR_PIN = 34;

    static constexpr uint8_t JSON_BUFFER_SIZE = 25;
    static constexpr const char* JSON_FORMAT = "{\"state\":%05d}\0";
    char jsonBuffer[JSON_BUFFER_SIZE];
};