
#include "Device.h"

class MovementSensor : public Device
{
  public:
    MovementSensor(void (*ISR_MovementSensor)());

    //reset
    void Reset();
    void Detected();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    bool _move_detected;

    const int8_t PIR_SENSOR_PIN = 14;
};