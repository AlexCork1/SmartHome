#include "Device.h"

//RFID library: 
//https://www.arduino.cc/reference/en/libraries/mfrc522/
//https://github.com/OSSLibraries/Arduino_MFRC522v2
#include "MFRC522_I2C.h"

class RFIDSensor : public Device
{
  public:
    RFIDSensor(const char* topic);

    String ReadRFIDCard();

    void Init() override;
    const char* Get_Current_State() override { return "";/* NOTHING - it is only sending data. Check ino file */ }
    void MQTT_Message_Subscribe(const String& message) override { /* NOTHING - it is only sending data. Check ino file */ }
    
  private:
    static constexpr uint16_t MY_I2C_ADDRESS_RFID = 0x28;
    MFRC522 _mfrc522;   // create MFRC522.
    String _oldPassword;
};