#ifndef SOUND_DATA_H
#define SOUND_DATA_H

#include "Device.h"
#include "Songs.h"

struct MelodyMapping {
    String name;
    const int32_t* melody;
    uint32_t melody_length;
    uint32_t tempo;
};

class Sound : public Device
{
  public:
    Sound();
    //functions dervied from Device class
    String Get_Current_State();
    String MQTT_Get_topic();
    void MQTT_Message_Subscribe(String message);
    void MQTT_Message_Publish();

  private:
    int8_t melody_playing_state;
    String melody_playing;

    const int8_t BUZZER_PIN = 25;

    const MelodyMapping melody_mappings[3] = {
        {"starwars", starwars_melody, sizeof(starwars_melody) / sizeof(starwars_melody[0]), 108},
        {"got", game_of_thrones_melody, sizeof(game_of_thrones_melody) / sizeof(game_of_thrones_melody[0]), 85},
        {"scale", musical_scale, sizeof(musical_scale) / sizeof(musical_scale[0]), 50}
    };

    void Play_Melody(MelodyMapping melody);
};
#endif