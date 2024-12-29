#pragma once
#define DISPLAY_CS PIN_PA4
#define DISPLAY_DC PIN_PA7

const char* wave_type_str[4] = {"Sine", "Sqr1", "Sqr2", "Triang"};

void format_freq(long freq, uint8_t digit);
