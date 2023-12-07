#ifndef LED_DATA_H
#define LED_DATA_H

#include "Device.h"


class LED : public Device
{
  public:
    enum class LedState { Off, On };
    LED(const char* topic) : Device(topic), _ledState(LedState::Off){}
    virtual void On() = 0;
    virtual void Off() = 0;
    virtual void Toggle() = 0;

  protected:
    LedState _ledState;
};
#endif