#include "../inc/Debug.h"
#include "../inc/Sound.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Sound::Sound()
{
    melody_playing = String();
    melody_playing_state = -1;
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
/* return single LED state as String */
String Sound::Get_Current_State()
{
    return melody_playing;
}
/* return single LED MQTT topic as String */
String Sound::MQTT_Get_topic()
{
    return String("sound");
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Sound::MQTT_Message_Subscribe(String message)
{
    // find melody to play
    for (uint32_t i = 0; i < sizeof(melody_mappings) / sizeof(melody_mappings[0]); i++)
    {
        if (message == melody_mappings[i].name)
        {
            melody_playing_state = i;
            melody_playing = melody_mappings[i].name;

            Play_Melody(melody_mappings[i]);

            melody_playing_state = -1;
            melody_playing = String();
            break;
        }
    }
}
void Sound::MQTT_Message_Publish()
{
    // TODO
    // MQTT_publish(MQTT_Get_topic().c_str(), GetData().c_str());
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
void Sound::Play_Melody(MelodyMapping melody_to_play)
{
    const int32_t *melody = melody_to_play.melody;
    uint32_t length = melody_to_play.melody_length;
    uint32_t tempo = melody_to_play.tempo;

    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    uint32_t notes = length / 2;

    // this calculates the duration of a whole note in ms
    uint32_t wholenote = (60000 * 4) / tempo;

    int32_t divider = 0, noteDuration = 0;

    for (uint32_t thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
    {
        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0)
        {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0)
        {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(BUZZER_PIN);
    }
}