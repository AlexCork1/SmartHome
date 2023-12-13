#ifndef LED_DATA_H
#define LED_DATA_H

#include "Device.h"


class LED : public Device
{
  public:
    enum class LedState { Off, On };
    LED(const char* topic) : Device(topic){}
};
#endif