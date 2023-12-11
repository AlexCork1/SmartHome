#include "Device.h"

class Button : public Device{
public:
    Button(const char* topic, uint8_t pinNumber, void (*ISR_Button)());

    void Init() override;
    const char* Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override { /* NOTHING - it is only sending data. Check ino file */ }

    int32_t Read_State() const { return digitalRead(_pinNumber); }
    void Pressed();
    void Reset();

private:
    const uint8_t _pinNumber;
    bool _buttonState;
    void (*_ISR_Button)();
    
    static constexpr uint8_t JSON_BUFFER_SIZE = 20;
    static constexpr const char* JSON_FORMAT = "{\"state\":%c}\0";
    char jsonBuffer[JSON_BUFFER_SIZE];
};