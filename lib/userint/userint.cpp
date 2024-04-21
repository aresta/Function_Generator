#include <Arduino.h>
#include "userint.h"
#include "common.h"

volatile bool encoder_pressed = false;

void IRAM_ATTR encoder_BTN_ISR(){
    encoder_pressed = true;
}

bool encoder_btn_pressed(){
    static uint32_t last_press = 0;
    if( millis() - last_press < 250){
        encoder_pressed = false;
        return false;
    }
    if( encoder_pressed){
        last_press = millis();
        encoder_pressed = false;
        return true;
    }
    return false;
}

void IRAM_ATTR encoder_checkPosition_ISR()
{
  encoder.tick();
}

volatile bool freq_range_btn_pressed = false;
void IRAM_ATTR freq_range_btn_ISR() {
  freq_range_btn_pressed = true;
}

volatile bool wave_type_btn_pressed = false;
void IRAM_ATTR wave_type_btn_ISR() {
  wave_type_btn_pressed = true;
}




