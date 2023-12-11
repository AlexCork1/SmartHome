#include "../inc/MovementSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
MovementSensor::MovementSensor(
    const char* topic,
    void (*ISR_MovementSensor)()) :
    Device(topic),
    _moveDetected(false)
{
    _ISR_MovementSensor = ISR_MovementSensor;
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void MovementSensor::Init(){
    pinMode(PIR_SENSOR_PIN, INPUT);

    // we will use isr approach
    attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN), _ISR_MovementSensor, CHANGE);
}
void MovementSensor::Reset()
{
    _moveDetected = false;
}
void MovementSensor::Detected(){
    _moveDetected = true;
}

const char* MovementSensor::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _moveDetected ? '1' : '0');
    return jsonBuffer;
}

int32_t MovementSensor::Read_State() const{
    return digitalRead(PIR_SENSOR_PIN);
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/



