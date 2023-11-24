#include "../inc/LCDdisplay.h"
#include "../inc/Debug.h"

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
String LCDdisplay::Get_Current_State(){
  String temp = String("");
  for(uint32_t i = 0; i < LCDdisplay::NO_ROWS; i++){
    temp += _data_on_display[i];
    if (i != LCDdisplay::NO_ROWS-1)
      temp += '\n';
  }
  return temp;
}
void LCDdisplay::MQTT_Message_Subscribe(String message){
	//LCD display is composed of N rows and 16 columns
  Clear_Display();

  String temp = message;
  uint32_t row_to_write = 0;
  Debugln(temp);
  while(true)
  {
    int32_t index_of_first = temp.indexOf('\n');
    if (index_of_first == -1) break;

    String subTemp = temp.substring(0, index_of_first > 16 ? 15 : index_of_first);
    Debugln(subTemp);
    
    if (subTemp.length() != 0){
        Write_Message(subTemp, row_to_write++, 0);
    }
    temp = temp.substring(index_of_first+1, temp.length());

    if (row_to_write >= NO_ROWS)
      break;
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

  //update the local copy for message
  for (int32_t i = 0, j = column; i < message.length() && j < NO_COLUMNS; i++, j++)
    _data_on_display[row][j] = message[i];
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