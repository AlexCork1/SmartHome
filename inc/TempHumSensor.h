#include "Device.h"

//Library: "DHT sensor library" by Adafruit (https://github.com/adafruit/DHT-sensor-library/tree/master)
#include "DHT.h"

class TempHumSensor : public Device
{
  public:
    TempHumSensor(const char* topic);
    
    bool Read_All();
    bool Read_Temperature();
    bool Read_Humidity();

    float Get_Temperature() const { return _temperature; }
    float Get_Humidity() const { return _humidity; }

    const char* Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override { /* NOTHING - it is only sending data. Check ino file */ }

  private:
    float _temperature = 0.0f;
    float _humidity = 0.0f;
    DHT _dht;

    static constexpr uint8_t TEMP_SENZOR_PIN = 17;

    //connected sensor:
    #define DHTTYPE DHT11   // DHT 11
    //#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
    //#define DHTTYPE DHT21   // DHT 21 (AM2301)
    
    static constexpr uint8_t JSON_BUFFER_SIZE = 50;
    static constexpr const char* JSON_FORMAT = "{\"temp\":\"%.2f\",\"hum\":\"%.2f\"}\0";
    char jsonBuffer[JSON_BUFFER_SIZE];
};