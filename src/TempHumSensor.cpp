#include "../inc/TempHumSensor.h"
#include "../inc/Debug.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
TempHumSensor::TempHumSensor(const char* topic) : 
    Device(topic),
    _dht(TEMP_SENZOR_PIN, DHTTYPE)
{
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/

void TempHumSensor::Init(){
    _dht.begin();
    Read_All();
}

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

const char* TempHumSensor::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _temperature, _humidity);
    return jsonBuffer;
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
