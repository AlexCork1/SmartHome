#include "../inc/SteamSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
SteamSensor::SteamSensor(const char* topic) : Device(topic)
{

}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
bool SteamSensor::Get_Data(){
    int32_t temp = analogRead(STEAM_SENSOR_PIN);
    if (temp != _data){
        _data = temp;
        return true;
    }
    
    return false;
}
/* return single LED state as String */
const char* SteamSensor::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _data);
    return jsonBuffer;
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/



