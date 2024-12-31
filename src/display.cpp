#include "common.h"

const char* waves[4] = { "Sine", "Sqr1", "Sqr2", "Triang"};
extern char freq_val[12];
extern char freq_unit[6];
extern uint8_t wave_type;
extern char wave_type_str[10];
bool flip_st = false;
uint8_t flip_digit;
uint32_t flip_prev = 0;
extern State state;
extern bool refresh_display;

void format_freq( int32_t freq, uint8_t digit)
{
    if (freq < 1000) {
        snprintf( freq_val, 12, "%ld", freq);
        strncpy( freq_unit, "Hz", 4);
        flip_digit = digit;
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
            flip_digit = strlen(freq_val) - digit - 1;
        } else {
            flip_digit = strlen(freq_val) - digit - 2;
        }
    } else {
        if( digit < 6) {
            flip_digit = strlen(freq_val) - digit + 2;
        } else {
            flip_digit = strlen(freq_val) - digit + 1;
        }
    }
    snprintf( wave_type_str, sizeof( wave_type_str), " %s", waves[wave_type-1]);

    if( state != IDLE){
        if( flip_st) {
            if( state == EDIT_FREQ){
                freq_val[ flip_digit] = ' ';
            } else if( state == EDIT_WV_TYPE){
                wave_type_str[0] = 0;
            }
        } 

        if( (millis() - flip_prev) > 500 || refresh_display) {
            flip_st = !flip_st;
            flip_prev = millis();
            refresh_display = true;
        } 
    }
}
