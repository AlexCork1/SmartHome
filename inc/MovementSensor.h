
#include "Device.h"

class MovementSensor : public Device
{
  public:
    MovementSensor(String topic, void (*ISR_MovementSensor)(), void (*mqtt_publish)(String, String));

    //reset
    void Reset();
    void Detected();

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    bool _move_detected;

    const int8_t PIR_SENSOR_PIN = 14;
};