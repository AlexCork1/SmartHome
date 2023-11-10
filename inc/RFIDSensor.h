#include "Device.h"

//RFID library: 
//https://www.arduino.cc/reference/en/libraries/mfrc522/
//https://github.com/OSSLibraries/Arduino_MFRC522v2
#include "MFRC522_I2C.h"

class RFIDSensor : public Device
{
  public:
    RFIDSensor();
    String Read();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish(); 
  private:
    const uint16_t MY_I2C_ADDRESS_RFID = 0x28;
    MFRC522 _mfrc522;   // create MFRC522.
};