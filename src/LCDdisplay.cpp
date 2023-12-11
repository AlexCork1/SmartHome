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
LCDdisplay::LCDdisplay(const char* topic) :
  Device(topic),
  _display(MY_I2C_ADDRESS, NO_COLUMNS, NO_ROWS)
{
}

void LCDdisplay::Init()
{
  _display.init();
  _display.backlight();
  _display.clear();
  Clear_Display();
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
const char* LCDdisplay::Get_Current_State()
{
  StaticJsonDocument<200> doc;
  for(uint32_t i = 0; i < LCDdisplay::NO_ROWS; i++)
    doc[String(i)] = _dataOnDisplay[i];

  String output;
  serializeJson(doc, output);
  return output.c_str();
}

/// @param message : JSON format
/// {
///   '0': "text to be put in row 0",
///   '1': "text to be put in row 1"
/// }
void LCDdisplay::MQTT_Message_Subscribe(const String& message)
{
	//LCD display is composed of N rows and 16 columns
  Clear_Display();

  DynamicJsonDocument doc(512);
  deserializeJson(doc, message);
  
  for (int i = 0; i < NO_ROWS; i++){
    String temp = doc[String(i)].as<String>();
    if(temp != "null"){
      //get data from current row
      auto& currentRow = _dataOnDisplay[i];
      //write empty string to it ("delete it")
      Clear_Row(currentRow);
      //copy new data into its place
      strncpy(currentRow.data(), temp.c_str(), std::min(NO_COLUMNS, (uint8_t)temp.length()));
    }

    Write_Message(_dataOnDisplay[i], i, 0);
  }
}

/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
void LCDdisplay::Write_Message(const std::array<char, NO_COLUMNS>& message, uint32_t row, uint32_t column){
  if (row >= NO_ROWS) return;
  if (column >= NO_COLUMNS) return;

  _display.setCursor(column, row);
  _display.print(message.data());
}

void LCDdisplay::Clear_Display(){
  for (auto& row : _dataOnDisplay)
    Clear_Row(row);
}

void LCDdisplay::Clear_Row(std::array<char, NO_COLUMNS>& row){
  std::fill(row.begin(), row.end(), ' ');

  _display.setCursor(0, &row - &_dataOnDisplay[0]);
  _display.print(row.data());
}