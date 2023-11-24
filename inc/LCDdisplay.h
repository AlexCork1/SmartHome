
#include "Device.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

class LCDdisplay : public Device
{
  public:
    LCDdisplay(String topic);
    static const int MY_I2C_ADDRESS = 0x27;
    static const int NO_ROWS = 2;
    static const int NO_COLUMNS = 16;

    void Init();

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);

  private:
    String EMPTY_LINE;

    LiquidCrystal_I2C _display;
    String _data_on_display[NO_ROWS];

    void Write_Message(String message, uint32_t row, uint32_t column);
    void Clear_Display();
    void Clear_Row(uint32_t row);

    String Get_Empty_Row() {
        String result;
        for (int i = 0; i < NO_COLUMNS; i++)
          result += " ";
        return result;
    }
};
