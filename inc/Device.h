#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H
#include <Arduino.h>

class Device
{
  public:
    Device(String topic, void (*mqtt_publish)(String, String)) : _mqttTopic(topic), _mqtt_publish(mqtt_publish){}
    String Get_MQTT_topic() { return _mqttTopic; }

    virtual String Get_Current_State() = 0; //used to send current state of all devices to MQTT server
    virtual void MQTT_Message_Subscribe(String message) = 0;  //function that will be triggered when message for current topic is recevied
    virtual void MQTT_Message_Publish() = 0;  //function that will be publishing data to MQTT server

  private:
    String _mqttTopic;
    void (*_mqtt_publish)(String, String);
};

#endif