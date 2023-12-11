#include "Device.h"

class Fan : public Device{
public:
    Fan(const char* topic);

    void Init() override;
    const char* Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override;

private:
    bool _runningState;
    
    static constexpr uint8_t FAN_DIR1_PIN = 18;
    static constexpr uint8_t FAN_DIR2_PIN = 19;
    static constexpr uint8_t CHANNEL_NUMBER = 5;
    static constexpr uint8_t FAN_OFF = 0;
    static constexpr uint8_t FAN_ON = 127; //max speed 255

    static constexpr uint8_t JSON_BUFFER_SIZE = 20;
    static constexpr const char* JSON_FORMAT = "{\"state\":%c}\0";
    char jsonBuffer[JSON_BUFFER_SIZE];

    static constexpr char START_COMMAND[] = "start";
    static constexpr char STOP_COMMAND[] = "stop";

    void Start();
    void Stop();
};