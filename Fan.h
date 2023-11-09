#ifndef FAN_DATA_H
#define FAN_DATA_H

#include "Device.h"

class Fan : public Device
{
  public:
    Fan();

    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    bool _running_state;
    
    const uint8_t FAN_DIR1_PIN = 18;
    const uint8_t FAN_DIR2_PIN = 19;

    const uint8_t CHANNEL_NUMBER = 5;
    const uint8_t FAN_OFF = 0;
    const uint8_t FAN_ON = 127; //max speed 255

    void Start();
    void Stop();
};
#endif