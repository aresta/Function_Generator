#include <Arduino.h>
#include <U8g2lib.h>
#include <MD_AD9833.h>
#include <SPI.h>
#include "common.h"
#include "encoder.h"
#include "buttons.h"
#include "display.h"

// 128x64
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2( U8G2_R0, DISPLAY_CS, DISPLAY_DC);
MD_AD9833	AD( PIN_FSYNC);
State state = IDLE;

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
bool enc_btn_pressed = false;
bool left_btn_pressed = false;
bool rigth_btn_pressed = false;
int32_t freq = 1000;
extern int8_t enc_cnt;
uint8_t digit_inc = 3;
char freq_val[12]; 
char freq_unit[6];
char wave_type_str[10];
bool refresh_display = true;

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
  if( freq >= 1000000 && digit_inc < 3) digit_inc = 3;
}

void loop () 
{
  static int32_t prev_freq = 0;
  handle_buttons();
  switch( state){
    case IDLE:
      if( enc_btn_pressed){
        state = EDIT_FREQ;
        enc_btn_pressed = false;
        left_btn_pressed = false;
        rigth_btn_pressed = false;
        enc_cnt = 0;
      }
      break;

    case EDIT_FREQ:
      if( enc_btn_pressed){
        state = IDLE;
        enc_btn_pressed = false;
        refresh_display = true;
      }
      if( left_btn_pressed){
        if (digit_inc < 6) digit_inc++;
        left_btn_pressed = false;
        refresh_display = true;
      }
      if( rigth_btn_pressed){
        if( freq >= 1000000 && digit_inc == 3) state = EDIT_WV_TYPE;
        else if( digit_inc == 0) state = EDIT_WV_TYPE;      
        else digit_inc--;
        rigth_btn_pressed = false;
        refresh_display = true;
      }    
      handle_freq();
      if( freq != prev_freq) {
        AD.setFrequency( MD_AD9833::CHAN_0, freq);
        prev_freq = freq;
        refresh_display = true;
      }
      break;

    case EDIT_WV_TYPE:
      if( enc_cnt != 0){
        wave_type += enc_cnt;
        if( wave_type > AD.MODE_TRIANGLE) wave_type = AD.MODE_SINE;
        if( wave_type < AD.MODE_SINE) wave_type = AD.MODE_TRIANGLE;
        AD.setMode((MD_AD9833::mode_t )wave_type);
        enc_cnt = 0;
        refresh_display = true;
      }
      if( enc_btn_pressed){
        state = IDLE;
        enc_btn_pressed = false;
        refresh_display = true;
      }
      if( left_btn_pressed){
        state = EDIT_FREQ; 
        left_btn_pressed = false;
        rigth_btn_pressed = false;
        refresh_display = true;
      }
  }
  
  format_freq( freq, digit_inc);
  if( refresh_display){
    u8g2.clearBuffer();      
    // u8g2.setFont( u8g2_font_spleen16x32_mu);
    u8g2.setFont( u8g2_font_profont29_mn);
    u8g2.drawStr( 7, 25, freq_val);
    u8g2.setFont( u8g2_font_helvB14_tr);
    u8g2.drawStr( 80, 54, freq_unit);
    u8g2.drawStr(0,54, wave_type_str);
    u8g2.sendBuffer();
    refresh_display = false;
  }
}






