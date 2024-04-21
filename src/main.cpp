#include <Arduino.h>
#include <math.h>
#include <RotaryEncoder.h>
#include "common.h"
#include "AD9833.h"
#include "display.h"
#include "userint.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

// AD9833_OFF            0
// AD9833_SINE           1
// AD9833_SQUARE1        2
// AD9833_SQUARE2        3
// AD9833_TRIANGLE       4
uint8_t wave_type = AD9833_SINE;

uint32_t freq = 1000;
uint8_t sweep_digit = 2; // from right

AD9833 AD( AD9833_FNC, AD9833_DAT, AD9833_CLK);
RotaryEncoder encoder( ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, RotaryEncoder::LatchMode::TWO03);

void setup(){
  #ifdef DEBUG_
    Serial.begin(115200);
  #endif
  PRINTD("Olakease!");

	pinMode( ROTARY_ENCODER_BTN_PIN, INPUT_PULLUP);
	pinMode( WAVE_TYPE_BTN, INPUT_PULLUP);
	pinMode( FREQ_RANGE_BTN, INPUT_PULLUP);
	attachInterrupt( ROTARY_ENCODER_BTN_PIN, encoder_BTN_ISR, FALLING);
	attachInterrupt( ROTARY_ENCODER_A_PIN, encoder_checkPosition_ISR, FALLING);
	attachInterrupt( ROTARY_ENCODER_B_PIN, encoder_checkPosition_ISR, FALLING);
	attachInterrupt( WAVE_TYPE_BTN, wave_type_btn_ISR, FALLING);
	attachInterrupt( FREQ_RANGE_BTN, freq_range_btn_ISR, FALLING);

  AD.begin();
  AD.setFrequency( freq);
  AD.setWave( wave_type);

  tft.init();
  tft.setRotation(1);  // portrait
  tft.invertDisplay( true);
  tft.fillScreen( GRAYCLEAR);
  spr.fillSprite( GRAYCLEAR);
  // 320x170
  // 10 + 300 + 10 = 320 wide
  // 10 + 70 + 10 + 70 + 10 = 170 high
  spr.createSprite( 300, 70);

  display_freq( freq, sweep_digit);
  display_wave_type( wave_type);
}

void adjust_sweep_digit(){
  uint8_t digits = floor(log10( freq)) + 1;
  if( (freq >= 1000*1000 && sweep_digit < 4) || 
    sweep_digit < 1 || sweep_digit > digits){
    sweep_digit = digits;
  }
}

int s = 0;
int encoder_pos = 0;
void loop(){
  static uint32_t wave_type_btn_last_time_pressed = 0;
  static uint32_t freq_range_btn_last_time_pressed = 0;
  int encoder_direction = 0;
  
  int newPos = encoder.getPosition();
  if ( encoder_pos != newPos) {
    encoder_direction = (int )encoder.getDirection();
    encoder_pos = newPos;
  }

  static uint32_t last_encoder_direction = 0;
  if( encoder_direction &&
      millis() - last_encoder_direction > 100 && 
      (freq < 50*1000*1000 || encoder_direction < 0))
  {
    PRINTD2("encoder_direction:", encoder_direction);
    last_encoder_direction = millis();
    freq += (( pow( 10, ( sweep_digit - 1))) * encoder_direction);
    if( freq < 1){
      freq = 1;
      sweep_digit = 1;
    }
    adjust_sweep_digit();
    display_freq( freq, sweep_digit);
    AD.setFrequency( freq);
    // PRINTD2( "freq:", freq);
  }

  if( encoder_btn_pressed()){
    PRINTD("encoder_btn_pressed!");
    sweep_digit--;
    adjust_sweep_digit();
    display_freq( freq, sweep_digit);
    PRINTD2( "sweep_digit:", sweep_digit);
  }

  if( freq_range_btn_pressed){
    PRINTD("freq_range_btn_pressed!");
    freq_range_btn_pressed = false;
    if( millis() - freq_range_btn_last_time_pressed > 300){
      freq_range_btn_last_time_pressed = millis();
      if( freq < 1000000) freq *= 10;
      else freq = 10;
      adjust_sweep_digit();
      display_freq( freq, sweep_digit);
      AD.setFrequency( freq);
      PRINTD2( "freq:", freq);
    }
  }

  if( wave_type_btn_pressed){
    PRINTD("wave_type_btn_pressed!");
    wave_type_btn_pressed = false;
    if( millis() - wave_type_btn_last_time_pressed > 300){
      wave_type_btn_last_time_pressed = millis();
      wave_type += 1;
      if( wave_type > 4) wave_type = 1;
      display_wave_type( wave_type);
      AD.setWave( wave_type);
      PRINTD2( "wave_type:", wave_type);
    }
  }

}

