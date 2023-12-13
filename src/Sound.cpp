#include "../inc/Debug.h"
#include "../inc/Sound.h"
#include <ArduinoJson.h>


/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Sound::Sound(const char* topic, void (*mqtt_publish)(const char*, const char*)) : 
    Device(topic),
    _mqtt_publish(mqtt_publish)
{
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void Sound::Init()
{
    melody_playing[0] = '\0'; // Initialize the array with an empty string
    melody_playing_state = false;
}
/* return single LED state as String */
const char* Sound::Get_Current_State()
{ // Calculate the capacity based on constants
    const size_t capacity = JSON_ARRAY_SIZE(NUM_MELODIES) + NUM_MELODIES * JSON_OBJECT_SIZE(1) +
                            NUM_MELODIES * (MAX_NAME_LENGTH + JSON_OBJECT_SIZE(1)) + 100;
    
    DynamicJsonDocument doc(capacity);

    // Create an array for melody names
    JsonArray melodies = doc.createNestedArray("melodies");

    // Add each melody name to the array
    for (int i = 0; i < NUM_MELODIES; ++i) 
        melodies.add(melody_mappings[i].name);

    // Add state and musicPlaying
    doc["state"] = melody_playing_state;
    doc["musicPlaying"] = melody_playing;

    // Serialize the JSON document to a char array
    static char buffer[capacity];
    serializeJson(doc, buffer, sizeof(buffer));

    // Return the serialized JSON
    return buffer;

    //old code
    //snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, melody_playing_state, melody_playing);
    //return jsonBuffer;
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Sound::MQTT_Message_Subscribe(const String& message)
{
    // find melody to play
    for (uint32_t i = 0; i < sizeof(melody_mappings) / sizeof(melody_mappings[0]); i++)
    {
        if (message == melody_mappings[i].name)
        {
            melody_playing_state = true;
            strncpy(melody_playing, melody_mappings[i].name, sizeof(melody_playing) - 1);
            melody_playing[sizeof(melody_playing) - 1] = '\0'; // Ensure null-termination

            //notify that we are playing music
            _mqtt_publish(Get_MQTT_topic(), Get_Current_State());

            Play_Melody(melody_mappings[i]);

            melody_playing_state = false;
            melody_playing[0] = '\0'; // Reset the array

            //notify that we stoped playing music
            _mqtt_publish(Get_MQTT_topic(), Get_Current_State());
            break;
        }
    }
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