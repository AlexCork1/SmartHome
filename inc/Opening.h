#include "Device.h"

class Opening : public Device
{
  public:
    enum class OpeningState { Open, Closed };
    enum class OpeningCommand { Open, Close, Unknown };

    Opening(const char* topic, uint8_t pin_number, uint32_t channel_number);

    String Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override;

  private:
    OpeningState _openingState;
    uint8_t _pinNumber;
    uint32_t _channelNumber;

    static constexpr  uint32_t FREQUENCY = 50;
    static constexpr  uint32_t RESOLUTION = 10;
    static constexpr  uint32_t CLOSED_STATE = (((1 << RESOLUTION) * 0.5) / ( 1000 / FREQUENCY));
    static constexpr  uint32_t OPEN_STATE = (((1 << RESOLUTION) * 2.5) / ( 1000 / FREQUENCY));

    static constexpr uint8_t JSON_BUFFER_SIZE = 20;
    static constexpr const char* JSON_FORMAT = "{\"state\":%c}";
    char jsonBuffer[JSON_BUFFER_SIZE];
    
    static constexpr char OPEN_COMMAND[] = "open";
    static constexpr char CLOSE_COMMAND[] = "close";

    void Open();
    void Close();
    void Process_Command(OpeningCommand command);
};