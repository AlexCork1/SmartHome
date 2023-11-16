#include "../inc/RFIDSensor.h"
#include "../inc/Debug.h"
#include <Wire.h>

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
RFIDSensor::RFIDSensor(
    String topic,
    void (*mqtt_publish)(String, String)
    ) :
    Device(topic, mqtt_publish), 
    _mfrc522(MY_I2C_ADDRESS_RFID)
{
    Wire.begin();        // initialize I2C
    _mfrc522.PCD_Init(); // initialize MFRC522
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
String RFIDSensor::Read()
{
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!_mfrc522.PICC_IsNewCardPresent()) return "";
    // Select one of the cards.
    if (!_mfrc522.PICC_ReadCardSerial()) return "";

    String password = "";
    // save UID
    Debug(F("Card UID:"));
    for (byte i = 0; i < _mfrc522.uid.size; i++)
    {
        Debug(_mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Debug(_mfrc522.uid.uidByte[i]);

        password = password + String(_mfrc522.uid.uidByte[i]);
    }
    Debugln(password);
    return password;
}
String RFIDSensor::Get_Current_State()
{
    // TODO
}
void RFIDSensor::MQTT_Message_Subscribe(String message)
{
    // Nothing to do here
}

void RFIDSensor::MQTT_Message_Publish()
{
    // TODO
    // MQTT_publish(MQTT_topic().c_str(), GetData().c_str());
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
