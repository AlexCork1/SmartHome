#include "../inc/GasSensor.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
GasSensor::GasSensor(const char* topic, void (*ISR_GASSensor)()) 
    : Device(topic), _gasState(false)
{
    _ISR_GASSensor = ISR_GASSensor;
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void GasSensor::Init(){
    pinMode(GAS_SENSOR_PIN, INPUT);

    // we will use isr approach
    attachInterrupt(digitalPinToInterrupt(GAS_SENSOR_PIN), _ISR_GASSensor, CHANGE);
    
    Reset_Alarm();
}
void GasSensor::Reset_Alarm()
{
    _gasState = false;
}
void GasSensor::Set_Alarm(){
    _gasState = true;
}

const char* GasSensor::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _gasState ? '1' : '0');
    return jsonBuffer;
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/



