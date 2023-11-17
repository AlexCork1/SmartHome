#ifndef LED_DATA_H
#define LED_DATA_H

#include "Device.h"

class LED : public Device
{
  public:
    LED(String topic, void (*mqtt_publish)(String, String)) : Device(topic, mqtt_publish){}
    virtual void On() = 0;
    virtual void Off() = 0;
    virtual void Toggle() = 0;

  protected:
    bool _led_state;
};
#endif