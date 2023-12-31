#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H
#include <Arduino.h>
#include "MQTTtopics.h"

class Device
{
  public:
    Device(const char topic[]) : _mqttTopic(topic) {}
    
    const char* Get_MQTT_topic() const { return _mqttTopic; }

    virtual void Init() = 0;
    virtual const char* Get_Current_State() = 0; //used to send current state of all devices to MQTT server
    virtual void MQTT_Message_Subscribe(const String& message) = 0;  //function that will be triggered when message for current topic is recevied

  private:
    const char* _mqttTopic;
};

#endif