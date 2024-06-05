#ifndef userint_h_
#define userint_h_
#include <RotaryEncoder.h>

void IRAM_ATTR encoder_BTN_ISR();
bool encoder_btn_pressed();

extern RotaryEncoder encoder;
void IRAM_ATTR encoder_checkPosition_ISR();
extern volatile bool left_btn_pressed;
void IRAM_ATTR left_btn_ISR();
extern volatile bool right_btn_pressed;
void IRAM_ATTR right_btn_ISR();
extern volatile bool vw_type_btn_pressed;
void IRAM_ATTR vw_type_btn_ISR();

#endif