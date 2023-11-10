#include "../inc/LCDdisplay.h"
#include <Wire.h>

/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LCDdisplay::LCDdisplay() : 
  _display(MY_I2C_ADDRESS, LCDdisplay::NO_COLUMNS,LCDdisplay::NO_ROWS),
  EMPTY_STRING(Get_Empty_Row())
{
  for(uint32_t i = 0; i < NO_ROWS; i++)
    _data_on_display[i] = EMPTY_STRING;
    
  _display.init();
  _display.backlight();
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
String LCDdisplay::Get_Current_State(){
  String temp = String("");
  for(uint32_t i = 0; i < LCDdisplay::NO_ROWS; i++){
    temp += _data_on_display[i];
    if (i != LCDdisplay::NO_ROWS-1)
      temp += '\n';
  }
  return temp;
}
String LCDdisplay::MQTT_Get_topic(){
  return String("lcd");
}
void LCDdisplay::MQTT_Message_Subscribe(String message){
	//LCD display is composed of N rows and 16 columns
  Clear_Display();

  String temp = message;
  uint32_t row_to_write = 0;

  while(true)
  {
    int32_t index_of_first = temp.indexOf('\n');
    if (index_of_first == -1) break;

    String subTemp = temp.substring(0, index_of_first > 16 ? 15 : index_of_first);
    if (subTemp.length() != 0){
        Write_Message(subTemp, row_to_write++, 0);
    }
    temp = temp.substring(index_of_first+1, temp.length());

    if (row_to_write >= NO_ROWS)
      break;
  }
}

void LCDdisplay::MQTT_Message_Publish(){
  //MQTT_publish(MQTT_topic().c_str(), GetData().c_str());
  //TODO
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

  _display.setCursor(column, row);
  _display.print(message);

  //update the local copy for message
  for (int32_t i = 0, j = column; i < message.length() && j < NO_COLUMNS; i++, j++)
    _data_on_display[row][j] = message[i];
}
void LCDdisplay::Clear_Display(){
  for (int i = 0; i < NO_ROWS; i++) 
    Clear_Row(i);
}
void LCDdisplay::Clear_Row(uint32_t row){
  if (row >= NO_ROWS) return;

  _display.setCursor(0, row);

  //simple way of "clearing" row is to write empty char
  _display.print(EMPTY_STRING);
}