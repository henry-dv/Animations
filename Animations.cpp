/*
    Animations.cpp - Fancy animations for an Adafruit_NeoPixel strip.
    Created by Henry Lehmann, December 30, 2020.
    Released into the public domain.
*/

#include "Arduino.h"
#include "Colors.h"
#include "Animations.h"

Animations::Animations(Adafruit_NeoPixel* strip) {
  this->strip = strip;
  e_MyAnimation = e_breathe;
  myAnimation = breathe;
  myColor = colors.RED;
}

void Animations::nextFrame(unsigned long ticks) {
  myAnimation(ticks);
}

void Animations::cycleAnimation() {
  setAnimation((E_Animations)((this->e_MyAnimation + 1) % ANIMATION_COUNT));
}

E_Animations Animations::getAnimation() {
  return this->e_MyAnimation;
}

void Animations::setAnimation(E_Animations newAnimation) {
  this->e_MyAnimation = newAnimation;
  switch (this->e_MyAnimation)
  {
  case e_breathe:
    myAnimation = breathe;
    break;
  case e_christmasTime:
    myAnimation = christmasTime;
    break;
  case e_plainColor:
    myAnimation = plainColor;
    break;
  case e_strobo:
    myAnimation = strobo;
    break;
  default:
    break;
  }
}

uint32_t Animations::getColor() {
  return this->myColor;
}

void Animations::setColor(uint32_t newColor) {
  this->myColor = newColor;
}

//-------Actual Animations-------

void Animations::breathe(unsigned long ticks) {
  unsigned int myticks = ticks >> 4;
  if ((myticks / 256) % 2 == 0)
    strip.fill(colors.hsbToRgb(195, 255, myticks % 256));
  else
    strip.fill(colors.hsbToRgb(195, 255, 255 - (myticks % 256)));
}

void Animations::christmasTime(unsigned long ticks) {
  unsigned short myticks = ticks >> 10;
  for (int i = 0; i < LED_COUNT; i++) {
    if ((i + myticks) % 2 == 0) {
      strip.setPixelColor(i, colors.RED);
    }
    else {
      strip.setPixelColor(i, colors.GREEN);
    }
  }
}

void Animations::plainColor(unsigned long ticks) {
  strip.fill(myColor);
}

void Animations::strobo(unsigned long ticks) {
  unsigned short myticks = ticks >> 6;
  if (myticks % 2 == 0)
    strip.fill(colors.WHITE);
  else
    strip.clear();
}
