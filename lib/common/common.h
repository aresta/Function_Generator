#ifndef common_h_
#define common_h_
// #define DEBUG_

#define AD9833_DAT 17
#define AD9833_CLK 21
#define AD9833_FNC 1
#define ROTARY_ENCODER_A_PIN 35
#define ROTARY_ENCODER_B_PIN 33
#define ROTARY_ENCODER_BTN_PIN 18
#define LEFT_BTN 39
#define RIGHT_BTN 38
#define WV_TYPE_BTN 5
#define LED_BRD 4

#ifdef DEBUG_
#define PRINTD( s) Serial.println( s)
#define PRINTD2( s1, s2) Serial.print( s1); Serial.println( s2)
#else
#define PRINTD( s)
#define PRINTD2( s1, s2)
#endif

#endif

