#ifndef CONFIG_H_
#define CONFIG_H_

// version and boot config
#define LIGHTOS_VERSION "lightOS v1.0a"
// #define FASTBOOT

// pin configuration (avoid pins 0 and 1)
#define PIN_STRIP_1 6
#define PIN_STRIP_2 7

#define PIN_ESC_KEY 18
#define PIN_BACK_KEY 19
#define PIN_SEL_KEY 20
#define PIN_NEXT_KEY 21

#define PIN_LCD_RS 30
#define PIN_LCD_EN 31
#define PIN_LCD_D4 32
#define PIN_LCD_D5 33
#define PIN_LCD_D6 34
#define PIN_LCD_D7 35

#define RAND_SEED_ANALOG_NOISE_PORT A0

// strip type
#define STRIP_TYPE_RGB NEO_GRB + NEO_KHZ800

// dimensions
#define STRIP_LENGTH 19
#define STRIP_1_LENGTH STRIP_LENGTH
#define STRIP_2_LENGTH STRIP_LENGTH

// strips
#define NUM_STRIPS 2
#define ID_STRIP_1 0x1
#define ID_STRIP_2 0x2

#endif
