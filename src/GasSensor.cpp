#include "../inc/GasSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
GasSensor::GasSensor(String topic, void (*ISR_GASSensor)(), void (*mqtt_publish)(String, String)) :
    Device(topic, mqtt_publish)
{
    pinMode(GAS_SENSOR_PIN, INPUT);

    Reset_Alarm();

    // we will use isr approach
    attachInterrupt(digitalPinToInterrupt(GAS_SENSOR_PIN), ISR_GASSensor, FALLING);
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/

void GasSensor::Reset_Alarm()
{
    gas_state = false;
}
void GasSensor::Set_Alarm(){
    gas_state = true;
}

/* return single LED state as String */
String GasSensor::Get_Current_State()
{
    return String(gas_state);
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void GasSensor::MQTT_Message_Subscribe(String message)
{
    // NOTHING - it is only send data
}
void GasSensor::MQTT_Message_Publish()
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


