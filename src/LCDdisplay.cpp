#include "../inc/LCDdisplay.h"
#include "../inc/Debug.h"
#include <ArduinoJson.h>

/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LCDdisplay::LCDdisplay(String topic) :
  Device(topic),
  _display(MY_I2C_ADDRESS, LCDdisplay::NO_COLUMNS, LCDdisplay::NO_ROWS)
{
  EMPTY_LINE = Get_Empty_Row();
  for(uint32_t i = 0; i < NO_ROWS; i++)
    _data_on_display[i] = EMPTY_LINE;  
}

void LCDdisplay::Init()
{
  _display.init();
  _display.backlight();
  _display.clear();
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
String LCDdisplay::Get_Current_State()
{
  StaticJsonDocument<200> doc;
  for(uint32_t i = 0; i < LCDdisplay::NO_ROWS; i++)
    doc[String(i)] = _data_on_display[i];

  String output;
  serializeJson(doc, output);
  return output;
}

/// @param message : JSON format
/// {
///   '0': "text to be put in row 0",
///   '1': "text to be put in row 1"
/// }
void LCDdisplay::MQTT_Message_Subscribe(String message)
{
	//LCD display is composed of N rows and 16 columns
  Clear_Display();

  DynamicJsonDocument doc(512);
  deserializeJson(doc, message);
  
  for (int i = 0; i < NO_ROWS; i++){
    String temp = doc[String(i)].as<String>();
    if(temp != "null")
      _data_on_display[i] = temp;

    Write_Message(_data_on_display[i], i, 0);
  }
}

/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
void LCDdisplay::Write_Message(String message, uint32_t row, uint32_t column){
  if (row >= NO_ROWS) return;
  if (column >= NO_COLUMNS) return;

  Debug(row); Debug(" "); Debug(column); Debug(" "); Debugln(message);

  _display.setCursor(column, row);
  _display.print(message);
}
void LCDdisplay::Clear_Display(){
  _display.clear();
}
void LCDdisplay::Clear_Row(uint32_t row){
  if (row >= NO_ROWS) return;

  _display.setCursor(0, row);

  //simple way of "clearing" row is to write empty char
  _display.print(EMPTY_LINE);
}