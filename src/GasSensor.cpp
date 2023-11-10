#include "../includes/GasSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
GasSensor::GasSensor(void (*ISR_GASSensor)())
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
/* return single LED MQTT topic as String */
String GasSensor::MQTT_Get_topic()
{
    return "gas";
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



