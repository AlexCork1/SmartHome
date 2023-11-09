
#include "Device.h"

class GasSenzor : public Device
{
  public:
    GasSenzor();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
};