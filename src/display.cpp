#include <Arduino.h>

char freq_val[12]; 
char freq_unit[6];
uint8_t flip_char;

void format_freq(long freq, uint8_t digit)
{
    if (freq < 1000) {
        snprintf( freq_val, 12, "%ld", freq);
        strncpy( freq_unit, "Hz", 4);
        flip_char = digit;
    } else if (freq < 1000000) {
        float kHz = freq / 1000.0;
        dtostrf( kHz, 1, 3, freq_val);
        strncpy( freq_unit, "KHz", 4);
    } else {
        float MHz = freq / 1000000.0;
        dtostrf( MHz, 1, 3, freq_val);
        strncpy( freq_unit, "MHz", 4);
    }

    if( freq < 1000000){
        if( digit < 3) {
            flip_char = strlen(freq_val) - digit - 1;
        } else {
            flip_char = strlen(freq_val) - digit - 2;
        }
    } else {
        if( digit < 6) {
            flip_char = strlen(freq_val) - digit + 2;
        } else {
            flip_char = strlen(freq_val) - digit + 1;
        }
    }
}
