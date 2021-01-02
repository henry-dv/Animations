/*
    Animations.h - Fancy animations for an Adafruit_NeoPixel strip.
    Created by Henry Lehmann, December 30, 2020.
    Released into the public domain.
*/

#ifndef Animations_h
#define Animations_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "Colors.h"

class Animations {
    public:
        enum E_Animations {
            e_breathe,
            e_christmasTime,
            e_plainColor,
            e_strobo,
            ANIMATION_COUNT
        };

        Animations(Adafruit_NeoPixel* strip);

        void nextFrame(unsigned long ticks);
        void cycleAnimation();
        E_Animations getAnimation();
        void setAnimation(E_Animations animation);

        uint32_t getColor();
        void setColor(uint32_t color);
    protected:
        Adafruit_NeoPixel* strip;

        Colors colors;
        uint32_t myColor;
        E_Animations e_MyAnimation; // redundantly keeping track for ease of cycling through

        void breathe(unsigned long ticks);
        void christmasTime(unsigned long ticks);
        void plainColor(unsigned long ticks);
        void strobo(unsigned long ticks);
        
        typedef void (*p_MyAnimation)(unsigned long);
        p_MyAnimation myAnimation;
};

#endif