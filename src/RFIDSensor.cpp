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
RFIDSensor::RFIDSensor(const char* topic) :
    Device(topic), 
    _mfrc522(MY_I2C_ADDRESS_RFID)
{
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void RFIDSensor::Init(){
    Wire.begin();        // initialize I2C
    _mfrc522.PCD_Init(); // initialize MFRC522
}
String RFIDSensor::ReadRFIDCard()
{
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    // Select one of the cards.
    if (_mfrc522.PICC_IsNewCardPresent() == false || _mfrc522.PICC_ReadCardSerial() == false){
        _oldPassword = "";
        return "";
    }    

    String password("{ \"rfid\" : \"");
    // save UID
    Debug(F("Card UID:"));
    for (byte i = 0; i < _mfrc522.uid.size; i++)
    {
        Debug(_mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Debug(_mfrc522.uid.uidByte[i]);

        password += String(_mfrc522.uid.uidByte[i]);
    }
    Debugln(password);
    password += "\"}";

    if (_oldPassword == password) return "";
    
    _oldPassword = password;
    return std::move(password);
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
