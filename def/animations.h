#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#include <Adafruit_NeoPixel.h>
#include "../conf/config.h"
#include "../os/sys/os.led_ctrl.hpp"

#define ANIMATION_WHITE					1
#define ANIMATION_SOFT_WHITE			2
#define ANIMATION_RED					3
#define ANIMATION_ORANGE				4
#define ANIMATION_YELLOW				5
#define ANIMATION_GREEN					6
#define ANIMATION_BLUE					7
#define ANIMATION_PURPLE				8
#define ANIMATION_PINK					9

#define ANIMATION_WHITE_FADE			10
#define ANIMATION_SOFT_WHITE_FADE		11
#define ANIMATION_RED_FADE				12
#define ANIMATION_ORANGE_FADE			13
#define ANIMATION_YELLOW_FADE			14
#define ANIMATION_GREEN_FADE			15
#define ANIMATION_BLUE_FADE				16
#define ANIMATION_PURPLE_FADE			17
#define ANIMATION_PINK_FADE				18

#define ANIMATION_WHITE_RIPPLE			19
#define ANIMATION_WHITE_SYM_RIPPLE		20
#define ANIMATION_SOFT_WHITE_RIPPLE		21
#define ANIMATION_SOFT_WHITE_SYM_RIPPLE	22
#define ANIMATION_RED_RIPPLE			23
#define ANIMATION_RED_SYM_RIPPLE		24
#define ANIMATION_ORANGE_RIPPLE			25
#define ANIMATION_ORANGE_SYM_RIPPLE		26
#define ANIMATION_YELLOW_RIPPLE			27
#define ANIMATION_YELLOW_SYM_RIPPLE		28
#define ANIMATION_GREEN_RIPPLE			29
#define ANIMATION_GREEN_SYM_RIPPLE		30
#define ANIMATION_BLUE_RIPPLE			31
#define ANIMATION_BLUE_SYM_RIPPLE		32
#define ANIMATION_PURPLE_RIPPLE			33
#define ANIMATION_PURPLE_SYM_RIPPLE		34
#define ANIMATION_PINK_RIPPLE			35
#define ANIMATION_PINK_SYM_RIPPLE		36

#define ANIMATION_WHITE_SPARKLE			37
#define ANIMATION_SOFT_WHITE_SPARKLE	38
#define ANIMATION_RED_SPARKLE			39
#define ANIMATION_ORANGE_SPARKLE		40
#define ANIMATION_YELLOW_SPARKLE		41
#define ANIMATION_GREEN_SPARKLE			42
#define ANIMATION_BLUE_SPARKLE			43
#define ANIMATION_PURPLE_SPARKLE		44
#define ANIMATION_PINK_SPARKLE			45

#define ANIMATION_RAINBOW				46
#define ANIMATION_RAINBOW_FLOW			47

using os::led_ctrl::AnimationData;

void anim__white(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__soft_white(Adafruit_NeoPixel* strip, AnimationData* data);

void anim__red(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__orn(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__ylw(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__grn(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__blu(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__prp(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__pnk(Adafruit_NeoPixel* strip, AnimationData* data);

void _anim__color(Adafruit_NeoPixel* strip, AnimationData* data, uint32_t color);

void anim__white_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__soft_white_fade(Adafruit_NeoPixel* strip, AnimationData* data);

void anim__red_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__orn_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__ylw_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__grn_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__blu_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__prp_fade(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__pnk_fade(Adafruit_NeoPixel* strip, AnimationData* data);

void _anim__fade(Adafruit_NeoPixel* strip, AnimationData* data, uint32_t color);

void anim__white_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__soft_white_ripple(Adafruit_NeoPixel* strip, AnimationData* data);

void anim__red_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__orn_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__ylw_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__grn_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__blu_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__prp_ripple(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__pnk_ripple(Adafruit_NeoPixel* strip, AnimationData* data);

void _anim__ripple(Adafruit_NeoPixel* strip, AnimationData* data, uint32_t color);

void anim__white_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__soft_white_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);

void anim__red_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__orn_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__ylw_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__grn_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__blu_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__prp_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__pnk_sparkle(Adafruit_NeoPixel* strip, AnimationData* data);

void _anim__sparkle(Adafruit_NeoPixel* strip, AnimationData* data, uint32_t color);

void anim__rainbow(Adafruit_NeoPixel* strip, AnimationData* data);
void anim__rainbow_wipe(Adafruit_NeoPixel* strip, AnimationData* data);

uint32_t _anim__clr_cycle(uint8_t state);
uint32_t color(uint8_t r, uint8_t g, uint8_t b);

uint8_t redFromColor(uint32_t color);
uint8_t greenFromColor(uint32_t color);
uint8_t blueFromColor(uint32_t color);

#endif
