#include "../inc/SteamSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
SteamSensor::SteamSensor(String topic) :
    Device(topic)
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
String SteamSensor::Get_Current_State()
{
    String respond("{\"steam\": \"");
    respond += String(_data);
    respond += "\"}";
    return std::move(respond);
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void SteamSensor::MQTT_Message_Subscribe(String message)
{
    // NOTHING - it is only send data
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/



