#include "MovementSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
MovementSensor::MovementSensor(void (*ISR_MovementSensor)())
{
    pinMode(PIR_SENSOR_PIN, INPUT);

    Reset();

    // we will use isr approach
    attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN), ISR_MovementSensor, RISING);
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/

void MovementSensor::Reset()
{
    _move_detected = false;
}
void MovementSensor::Detected(){
    _move_detected = true;
}

/* return single LED state as String */
String MovementSensor::Get_Current_State()
{
    return String(_move_detected);
}
/* return single LED MQTT topic as String */
String MovementSensor::MQTT_Get_topic()
{
    return "movement";
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void MovementSensor::MQTT_Message_Subscribe(String message)
{
    // NOTHING - it is only send data
}
void MovementSensor::MQTT_Message_Publish()
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



