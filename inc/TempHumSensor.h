#include "Device.h"

//Library: "DHT sensor library" by Adafruit (https://github.com/adafruit/DHT-sensor-library/tree/master)
#include "DHT.h"

class TempHumSensor : public Device
{
  public:
    TempHumSensor(String topic, void (*mqtt_publish)(String, String));
    bool Read_All(float* temperature, float* humidity);
    bool Read_Temperature();
    bool Read_Humidity();

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish(); 

  private:
    float _temperature;
    float _humidity;
    DHT _dht;

    const uint8_t TEMP_SENZOR_PIN = 17;

    //connected sensor:
    #define DHTTYPE DHT11   // DHT 11
    //#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
    //#define DHTTYPE DHT21   // DHT 21 (AM2301)
};