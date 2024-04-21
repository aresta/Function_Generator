#include <math.h>
#include "display.h"

void display_freq( uint32_t freq, uint8_t sweep_digit){
    char freqstr[20];
    String units;
    uint8_t digits = floor(log10( freq)) + 1;
    spr.setTextSize(1);
    spr.fillSprite( GRAYCLEAR2);
    spr.setTextColor( TFT_RED);
    if( freq >= 1000*1000){
        snprintf( freqstr, sizeof( freqstr), "%.3f", freq / 1000000.0);
        digits -= 3;
        sweep_digit -= 3;
        units = "MHz";
    } else if( freq >= 1000){
        snprintf( freqstr, sizeof( freqstr), "%.3f", freq / 1000.0);
        units = "KHz";
    } else {
        snprintf( freqstr, sizeof( freqstr), "%i", freq );
        units = "Hz";
    }

    spr.drawString( freqstr, 200 - 32*digits, 8, 7);
    spr.setFreeFont( &FreeSansBold18pt7b);
    spr.drawString( units, 225, 28, GFXFF);
    uint16_t pos = 201 - sweep_digit*32;
    if( freq >= 1000 && sweep_digit <= 3) pos += 13;
    spr.fillRect( pos, 56, 28, 5, TFT_MAGENTA);
    spr.pushSprite( 10, 10);
}

void display_wave_type( uint8_t wave){
    spr.setTextSize(1);
    spr.fillSprite( GRAYCLEAR2);
    spr.setTextColor( TFT_RED);
    spr.setFreeFont( &FreeSansBold24pt7b);
    switch ( wave) {
        case 1:
            spr.drawString( "Sine", 290 - 24*4, 15, GFXFF);
            break;    
        case 2:
            spr.drawString( "Square 1", 285 - 24*8, 15, GFXFF);
            break;    
        case 3:
            spr.drawString( "Square 2", 285 - 24*8, 15, GFXFF);
            break;    
        case 4:
            spr.drawString( "Triangle", 300 - 24*8, 15, GFXFF);
            break;    
        default:
            break;
    }
    spr.pushSprite( 10, 90);
}