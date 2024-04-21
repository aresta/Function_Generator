#ifndef userint_h_
#define userint_h_
#include <RotaryEncoder.h>

void IRAM_ATTR encoder_BTN_ISR();
bool encoder_btn_pressed();

extern RotaryEncoder encoder;
void IRAM_ATTR encoder_checkPosition_ISR();
extern volatile bool freq_range_btn_pressed;
void IRAM_ATTR freq_range_btn_ISR();
extern volatile bool wave_type_btn_pressed;
void IRAM_ATTR wave_type_btn_ISR();

#endif