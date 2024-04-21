#ifndef display_h_
#define display_h_
#include <TFT_eSPI.h>

#define GFXFF 1
const uint16_t WHITE        =   0xFFFF;
const uint16_t BLACK        =   0x0000;
const uint16_t RED          =   0xFA45;
const uint16_t GREEN        =   0x76EE;
const uint16_t GREENCLEAR   =   0x9F93;
const uint16_t GREENCLEAR2  =   0xCF6E;
const uint16_t BLUE         =   0x227E;
const uint16_t BLUECLEAR    =   0x6D3E;
const uint16_t CYAN         =   0xB7FF;
const uint16_t VIOLET       =   0xAA1F;
const uint16_t ORANGE       =   0xFCC2;
const uint16_t GRAY         =   0x94B2;
const uint16_t GRAYCLEAR    =   0xAD55;
const uint16_t GRAYCLEAR2   =   0xD69A;
const uint16_t BROWN        =   0xAB00;
const uint16_t YELLOW       =   0xFFF1;
const uint16_t YELLOWCLEAR  =   0xFFF5;
const uint16_t BACKGROUND_COLOR = 0xEF5D;

extern TFT_eSPI tft;
extern TFT_eSprite spr;


void display_freq( uint32_t freq, uint8_t sweep_digit);
void display_wave_type( uint8_t wave);
void display_ampl( float ampl);

// LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
// LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
// LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
// LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
// LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
// LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
// //LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
// LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#endif