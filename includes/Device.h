#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H
#include <Arduino.h>

class Device
{
  public:
    virtual String Get_Current_State() = 0; //used to send current state of all devices to MQTT server
    virtual String MQTT_Get_topic() = 0;      //MQTT topic used for publishing/subscribing to MQTT server
    virtual void MQTT_Message_Subscribe(String message) = 0;  //function that will be triggered when message for current topic is recevied
    virtual void MQTT_Message_Publish() = 0;  //function that will be publishing data to MQTT server
};

#endif