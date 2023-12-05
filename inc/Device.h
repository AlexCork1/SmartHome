#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H
#include <Arduino.h>
#include "MQTTtopics.h"

class Device
{
  public:
    Device(String topic) : _mqttTopic(topic) {}
    
    String Get_MQTT_topic() { return _mqttTopic; }

    virtual String Get_Current_State() = 0; //used to send current state of all devices to MQTT server
    virtual void MQTT_Message_Subscribe(String message) = 0;  //function that will be triggered when message for current topic is recevied

  private:
    String _mqttTopic;
};

#endif