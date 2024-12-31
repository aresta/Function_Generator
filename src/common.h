#pragma once
#include <Arduino.h>

#define PIN_FSYNC   PIN_PB3
#define LEFT_BUTTON PIN_PB0
#define RIGHT_BUTTON PIN_PB1
#define ENC_BUTTON  PIN_PA2
#define DISPLAY_CS  PIN_PA4
#define DISPLAY_DC  PIN_PA7
#define ENC_PIN_DT  PIN_PA6
#define ENC_PIN_SW  PIN_PA5
#define ENC_PIN_BUTTON PIN_PA2

static uint32_t power_values[10]    = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
enum State { IDLE, EDIT_FREQ, EDIT_WV_TYPE };