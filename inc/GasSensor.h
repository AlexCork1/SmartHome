#include "Device.h"

class GasSensor : public Device{
public:
    GasSensor(const char* topic, void (*ISR_GASSensor)());

    String Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override { /* NOTHING - it is only sending data. Check ino file */ }

    void Reset_Alarm();
    void Set_Alarm();

    int32_t Read_State() const { return digitalRead(GAS_SENSOR_PIN); }

 private:
    bool _gasState;

    static constexpr uint8_t GAS_SENSOR_PIN = 23;

    static constexpr uint8_t JSON_BUFFER_SIZE = 20;
    static constexpr const char* JSON_FORMAT = "{\"state\":%c}";  // JSON format for gas state
    char jsonBuffer[JSON_BUFFER_SIZE];
};