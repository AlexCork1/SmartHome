#include "../inc/MovementSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
MovementSensor::MovementSensor(
    String topic,
    void (*ISR_MovementSensor)()) :
    Device(topic)
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

/* callback function that will be called when message with MQTT_Get_topic() is received */
void MovementSensor::MQTT_Message_Subscribe(String message)
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



