
#include "Device.h"

class MovementSensor : public Device
{
  public:
    MovementSensor(const char* topic, void (*ISR_MovementSensor)());

    String Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override { /* NOTHING - it is only sending data. Check ino file */ }

    int32_t Read_State() const;
    void Reset();
    void Detected();

  private:
    bool _moveDetected;

    const int8_t PIR_SENSOR_PIN = 14;

    static constexpr uint8_t JSON_BUFFER_SIZE = 20;
    static constexpr const char* JSON_FORMAT = "{\"state\":%c}";
    char jsonBuffer[JSON_BUFFER_SIZE];
};