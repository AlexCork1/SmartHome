#include "../inc/TempHumSensor.h"
#include "../inc/Debug.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
TempHumSensor::TempHumSensor(String topic) : 
    Device(topic),
    _dht(TEMP_SENZOR_PIN, DHTTYPE), _temperature(0), _humidity(0)
{
    _dht.begin();
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/

bool TempHumSensor::Read_All(float* temperature, float* humidity)
{
    bool success_temp = Read_Temperature();
    bool success_hum = Read_Humidity();

    *temperature = _temperature;
    *humidity = _humidity;
    return success_temp && success_hum;
}
bool TempHumSensor::Read_Temperature(){
    float temp = _dht.readTemperature();
    if(isnan(temp)) return false;

    _temperature = temp;
    return true;
}
bool TempHumSensor::Read_Humidity(){
    float hum = _dht.readHumidity();
    if(isnan(hum)) return false;

    _humidity = hum;
    return true;
}

String TempHumSensor::Get_Current_State()
{
    return String("temp:") + String(_temperature) + String(";") + String("hum:") + String(_humidity);
}
void TempHumSensor::MQTT_Message_Subscribe(String message)
{
    // Nothing to do here
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
