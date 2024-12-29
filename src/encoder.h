#pragma once
#define ENC_PIN_DT PIN_PA6
#define ENC_PIN_SW PIN_PA5
#define ENC_PIN_BUTTON PIN_PA2

static long power_values[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

void isr_encoder();