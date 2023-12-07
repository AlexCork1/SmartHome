#pragma once

#include "Device.h"
#include "Songs.h"

struct MelodyMapping {
    const char name[20];
    const int32_t* melody;
    uint32_t melody_length;
    uint32_t tempo;
};

class Sound : public Device
{
  public:
    Sound(const char* topic, void (*mqtt_publish)(String, String));
    
    String Get_Current_State() override;
    void MQTT_Message_Subscribe(const String& message) override;

  private:
    void (*_mqtt_publish)(String, String);
    int8_t melody_playing_state;
    char melody_playing[20];

    static constexpr int8_t BUZZER_PIN = 25;

    MelodyMapping melody_mappings[3] = {
      {"starwars\0", starwars_melody, sizeof(starwars_melody) / sizeof(starwars_melody[0]), 108},
      {"got\0", game_of_thrones_melody, sizeof(game_of_thrones_melody) / sizeof(game_of_thrones_melody[0]), 85},
      {"scale\0", musical_scale, sizeof(musical_scale) / sizeof(musical_scale[0]), 50}
    };

    void Play_Melody(MelodyMapping melody);
    
    static constexpr uint8_t JSON_BUFFER_SIZE = 50;
    static constexpr const char* JSON_FORMAT = "{\"state\":%d, \"music\":\"%s\"}";
    char jsonBuffer[JSON_BUFFER_SIZE];
};