#include "common.h"

volatile int8_t enc_cnt;
void isr_encoder(){
  static uint8_t state_ = 0;
  bool sw_state = digitalRead( ENC_PIN_DT);
  bool dt_state = digitalRead( ENC_PIN_SW);
      switch (state_) {
        case 0:
            if (!sw_state){
                state_ = 1;
            } else if (!dt_state) {
                state_ = 4;
            }
            break;
        case 1:                     
            if (!dt_state) {
                state_ = 2;
            } 
            break;
        case 2:
            if (sw_state) {
                state_ = 3;
            }
            break;
        case 3:
            if (sw_state && dt_state) {
                state_ = 0;
                ++enc_cnt;
            }
            break;
        case 4:
            if (!sw_state) {
                state_ = 5;
            }
            break;
        case 5:
            if (dt_state) {
                state_ = 6;
            }
            break;
        case 6:
            if (sw_state && dt_state) {
                state_ = 0;
                --enc_cnt;
            }
            break; 
    }
}