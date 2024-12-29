#include <Arduino.h>
#include "encoder.h"

volatile int8_t enc_cnt;
uint8_t state = 0;
void isr_encoder(){
  bool sw_state = digitalRead( ENC_PIN_DT);
  bool dt_state = digitalRead( ENC_PIN_SW);
      switch (state) {
        case 0:
            if (!sw_state){
                state = 1;
            } else if (!dt_state) {
                state = 4;
            }
            break;
        case 1:                     
            if (!dt_state) {
                state = 2;
            } 
            break;
        case 2:
            if (sw_state) {
                state = 3;
            }
            break;
        case 3:
            if (sw_state && dt_state) {
                state = 0;
                ++enc_cnt;
            }
            break;
        case 4:
            if (!sw_state) {
                state = 5;
            }
            break;
        case 5:
            if (dt_state) {
                state = 6;
            }
            break;
        case 6:
            if (sw_state && dt_state) {
                state = 0;
                --enc_cnt;
            }
            break; 
    }
}