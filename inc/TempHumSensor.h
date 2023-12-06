#include "Device.h"

//Library: "DHT sensor library" by Adafruit (https://github.com/adafruit/DHT-sensor-library/tree/master)
#include "DHT.h"

class TempHumSensor : public Device
{
  public:
    TempHumSensor(String topic);
    
    bool Read_All();
    bool Read_Temperature();
    bool Read_Humidity();

    float Get_Temperature() const { return _temperature; }
    float Get_Humidity() const { return _humidity; }

    //functions dervied from Device class
    String Get_Current_State();
    void MQTT_Message_Subscribe(String message);

  private:
    float _temperature = 0.0f;
    float _humidity = 0.0f;
    DHT _dht;

    const uint8_t TEMP_SENZOR_PIN = 17;

    //connected sensor:
    #define DHTTYPE DHT11   // DHT 11
    //#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
    //#define DHTTYPE DHT21   // DHT 21 (AM2301)
};