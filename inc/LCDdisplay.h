#include "Device.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <array> 

class LCDdisplay : public Device{
public:
    LCDdisplay(const char* topic);

    void Init() override;
    const char* Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override;
    

private:
    static constexpr uint8_t MY_I2C_ADDRESS = 0x27;
    static constexpr uint8_t NO_ROWS = 2;
    static constexpr uint8_t NO_COLUMNS = 16;

    LiquidCrystal_I2C _display;
    std::array<std::array<char, NO_COLUMNS>, NO_ROWS> _dataOnDisplay;
    
    void Write_Message(const std::array<char, NO_COLUMNS>& message, uint32_t row, uint32_t column);
    void Clear_Display();
    void Clear_Row(std::array<char, NO_COLUMNS>& row);
};
