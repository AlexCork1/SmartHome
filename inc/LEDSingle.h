#include "LED.h"

class LEDSingle : public LED {
  public:
    enum class LedCommand { On, Off, Toggle, Unknown };
    LEDSingle(const char* topic);

    void Init() override;
    const char* Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override;

  private:
    LedState _ledState;

    const uint8_t SINGLE_LED_PIN = 12; //YELLOW LED
    
    static constexpr uint8_t JSON_BUFFER_SIZE = 20;
    static constexpr const char* JSON_FORMAT = "{\"state\":%c}\0";
    char jsonBuffer[JSON_BUFFER_SIZE];
    
    static constexpr char ON_COMMAND[] = "On";
    static constexpr char OFF_COMMAND[] = "Off";
    static constexpr char TOGGLE_COMMAND[] = "Toggle";

    void On();
    void Off();
    void Toggle();
    void Process_Command(LedCommand command);
};