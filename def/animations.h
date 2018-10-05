#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#include <Adafruit_NeoPixel.h>
#include "../conf/config.h"

void anim__white(Adafruit_NeoPixel* strip);
void anim__soft_white(Adafruit_NeoPixel* strip);

void anim__red(Adafruit_NeoPixel* strip);
void anim__orn(Adafruit_NeoPixel* strip);
void anim__ylw(Adafruit_NeoPixel* strip);
void anim__grn(Adafruit_NeoPixel* strip);
void anim__blu(Adafruit_NeoPixel* strip);
void anim__prp(Adafruit_NeoPixel* strip);
void anim__pnk(Adafruit_NeoPixel* strip);

void _anim__color(Adafruit_NeoPixel* strip, uint32_t color);

void anim__white_fade(Adafruit_NeoPixel* strip);
void anim__soft_white_fade(Adafruit_NeoPixel* strip);

void anim__red_fade(Adafruit_NeoPixel* strip);
void anim__orn_fade(Adafruit_NeoPixel* strip);
void anim__ylw_fade(Adafruit_NeoPixel* strip);
void anim__grn_fade(Adafruit_NeoPixel* strip);
void anim__blu_fade(Adafruit_NeoPixel* strip);
void anim__prp_fade(Adafruit_NeoPixel* strip);
void anim__pnk_fade(Adafruit_NeoPixel* strip);

void _anim__fade(Adafruit_NeoPixel* strip, uint32_t color);

void anim__white_ripple(Adafruit_NeoPixel* strip);
void anim__soft_white_ripple(Adafruit_NeoPixel* strip);

void anim__red_ripple(Adafruit_NeoPixel* strip);
void anim__orn_ripple(Adafruit_NeoPixel* strip);
void anim__ylw_ripple(Adafruit_NeoPixel* strip);
void anim__grn_ripple(Adafruit_NeoPixel* strip);
void anim__blu_ripple(Adafruit_NeoPixel* strip);
void anim__prp_ripple(Adafruit_NeoPixel* strip);
void anim__pnk_ripple(Adafruit_NeoPixel* strip);

void _anim__ripple(Adafruit_NeoPixel* strip, uint32_t color);

void anim__white_sparkle(Adafruit_NeoPixel* strip);
void anim__soft_white_sparkle(Adafruit_NeoPixel* strip);

void anim__red_sparkle(Adafruit_NeoPixel* strip);
void anim__orn_sparkle(Adafruit_NeoPixel* strip);
void anim__ylw_sparkle(Adafruit_NeoPixel* strip);
void anim__grn_sparkle(Adafruit_NeoPixel* strip);
void anim__blu_sparkle(Adafruit_NeoPixel* strip);
void anim__prp_sparkle(Adafruit_NeoPixel* strip);
void anim__pnk_sparkle(Adafruit_NeoPixel* strip);

void _anim__sparkle(Adafruit_NeoPixel* strip, uint32_t color);

void anim__rainbow(Adafruit_NeoPixel* strip);
void anim__rainbow_wipe(Adafruit_NeoPixel* strip);

uint32_t _anim__clr_cycle(uint8_t state);

#endif
