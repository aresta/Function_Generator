#include <Arduino.h>
#include <U8g2lib.h>
#include <MD_AD9833.h>
#include <SPI.h>
#include "encoder.h"
#include "buttons.h"
#include "display.h"

#define BAUDS 115200
#define PIN_FSYNC PIN_PB3

// 128x64
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2( U8G2_R0, DISPLAY_CS, DISPLAY_DC);
MD_AD9833	AD( PIN_FSYNC);

void setup() {
  _PROTECTED_WRITE( CLKCTRL.MCLKCTRLB, 0);	// no prescaler => clk = 20MHz

  pinMode( ENC_PIN_DT, INPUT_PULLUP);
  pinMode( ENC_PIN_SW, INPUT_PULLUP);
  pinMode( LEFT_BUTTON, INPUT_PULLUP);
  pinMode( RIGHT_BUTTON, INPUT_PULLUP);
  pinMode( ENC_BUTTON, INPUT_PULLUP);
  attachInterrupt( ENC_PIN_DT, isr_encoder, CHANGE);
  attachInterrupt( ENC_PIN_SW, isr_encoder, CHANGE);

  delay(100);
  u8g2.begin();
  AD.begin();
  delay(100);
}

uint8_t wave_type = AD.MODE_SINE;
extern bool enc_button_pressed;
long freq = 1000;
extern int8_t enc_cnt;
extern uint8_t digit_inc;
bool flip = false;
long flip_prev = 0;

extern char freq_val[12]; 
extern char freq_unit[6];
extern uint8_t flip_char;
bool refresh_display = false;

void handle_freq()
{
  if( power_values[digit_inc] > freq){
    freq += power_values[digit_inc];
  }
  
  freq += enc_cnt * power_values[digit_inc];
  enc_cnt = 0;
  if( freq < 1) freq = 1;
  if( freq > 10000000) freq = 10000000;
  
  if( freq < 1000 && digit_inc > 2) digit_inc = 2;
  else if( freq < 10000 && digit_inc > 3) digit_inc = 3;
  else if( freq < 100000 && digit_inc > 4) digit_inc = 4;
  else if( freq < 1000000 && digit_inc > 5) digit_inc = 5;
  
  if( freq > 1000000 && digit_inc < 3) digit_inc = 3;
}

void loop () 
{
  static long prev_freq = 0;
  refresh_display = handle_buttons(); // true is some button was pressed
  handle_freq();
  if( enc_button_pressed) {
    wave_type++;
    if( wave_type > AD.MODE_TRIANGLE) wave_type = AD.MODE_SINE;
    enc_button_pressed = false;
    AD.setMode(( MD_AD9833::mode_t )wave_type);
    refresh_display = true;
  }

  if( freq != prev_freq) {
    AD.setFrequency( MD_AD9833::CHAN_0, freq);
    prev_freq = freq;
    refresh_display = true;
  }

  format_freq( freq, digit_inc);
  if( refresh_display || (millis() - flip_prev > 500)) {
    flip = !flip;
    flip_prev = millis();
    refresh_display = true;
  } 
  if( flip) {
    freq_val[ flip_char] = ' ';
  } 

  if( refresh_display) {
    u8g2.clearBuffer();
    // u8g2.setFont( u8g2_font_spleen16x32_mu);
    u8g2.setFont( u8g2_font_profont29_mn);
    u8g2.drawStr( 7, 25, freq_val);
    u8g2.setFont( u8g2_font_helvB14_tr);
    u8g2.drawStr( 80, 54, freq_unit);

    char msg[12];
    snprintf( msg, sizeof( msg), " %s", wave_type_str[wave_type-1]);
    u8g2.drawStr(0,54, msg);
    u8g2.sendBuffer();
    refresh_display = false;
  }
}






