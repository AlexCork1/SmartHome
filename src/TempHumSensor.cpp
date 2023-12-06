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
    _dht(TEMP_SENZOR_PIN, DHTTYPE)
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

bool TempHumSensor::Read_All()
{
    bool success_temp = Read_Temperature();
    bool success_hum = Read_Humidity();

    return success_temp || success_hum;
}
bool TempHumSensor::Read_Temperature()
{
    float temp = _dht.readTemperature();
    if (isnan(temp)) return false;
    if (temp == _temperature) return false;
    
    _temperature = temp;
    return true;
}
bool TempHumSensor::Read_Humidity(){
    float hum = _dht.readHumidity();
    if (isnan(hum)) return false;
    if (hum == _humidity) return false;

    _humidity = hum;
    return true;
}

String TempHumSensor::Get_Current_State()
{
    String response("{\"temp\" : \"");
    response += String(_temperature);
    response += "\",\"hum\" : \"";
    response += String(_humidity);
    response +=  "\" }";

    Debug(response); Debug(" "); Debugln(response.length());

    return response;
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
