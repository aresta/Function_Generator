#include <Arduino.h>
#include "buttons.h"

uint8_t digit_inc = 3; // from right to left
bool enc_button_pressed = false;

bool handle_buttons() 
{
    static unsigned long lastDebounceTimeLeft = 0;
    static unsigned long lastDebounceTimeRight = 0;
    const unsigned long debounceDelay = 200;
    bool pressed = false;

    int8_t left_button_state = digitalRead( LEFT_BUTTON);
    int8_t right_button_state = digitalRead( RIGHT_BUTTON);
    int8_t enc_button_state = digitalRead( ENC_BUTTON);

    if ( left_button_state == LOW) {
        if ((millis() - lastDebounceTimeLeft) > debounceDelay) {
            if (digit_inc < 6) digit_inc++;
            lastDebounceTimeLeft = millis();
            pressed = true;
        }
    }

    if ( right_button_state == LOW) {
        if ((millis() - lastDebounceTimeRight) > debounceDelay) {
            if (digit_inc > 0) digit_inc--;
            lastDebounceTimeRight = millis();
            pressed = true;
        }
    }

    if ( enc_button_state == LOW) {
        if ((millis() - lastDebounceTimeRight) > debounceDelay) {
            enc_button_pressed = true;
            lastDebounceTimeRight = millis();
            pressed = true;
        }
    }
    return pressed;
}