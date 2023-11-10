#include "../inc/SteamSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
SteamSensor::SteamSensor()
{

}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
int32_t SteamSensor::Get_Data(){
    _data = analogRead(STEAM_SENSOR_PIN);
    return _data;
}
/* return single LED state as String */
String SteamSensor::Get_Current_State()
{
    return String(_data);
}
/* return single LED MQTT topic as String */
String SteamSensor::MQTT_Get_topic()
{
    return "steam";
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void SteamSensor::MQTT_Message_Subscribe(String message)
{
    // NOTHING - it is only send data
}
void SteamSensor::MQTT_Message_Publish()
{
    // TODO
    // MQTT_publish(MQTT_Get_topic().c_str(), GetData().c_str());
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/



