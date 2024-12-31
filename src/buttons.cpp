#include "common.h"

extern uint8_t digit_inc; // from right to left
extern bool enc_btn_pressed;
extern bool left_btn_pressed;
extern bool rigth_btn_pressed;

void handle_buttons() 
{
    static uint32_t lastDebounceTimeLeft = 0;
    static uint32_t lastDebounceTimeRight = 0;
    const uint32_t debounceDelay = 200;

    int8_t left_button_state = digitalRead( LEFT_BUTTON);
    int8_t right_button_state = digitalRead( RIGHT_BUTTON);
    int8_t enc_button_state = digitalRead( ENC_BUTTON);

    if ( left_button_state == LOW) {
        if ((millis() - lastDebounceTimeLeft) > debounceDelay) {
            lastDebounceTimeLeft = millis();
            left_btn_pressed = true;
        }
    }

    if ( right_button_state == LOW) {
        if ((millis() - lastDebounceTimeRight) > debounceDelay) {
            lastDebounceTimeRight = millis();
            rigth_btn_pressed = true;
        }
    }

    if ( enc_button_state == LOW) {
        if ((millis() - lastDebounceTimeRight) > debounceDelay) {
            enc_btn_pressed = true;
            lastDebounceTimeRight = millis();
        }
    }
}