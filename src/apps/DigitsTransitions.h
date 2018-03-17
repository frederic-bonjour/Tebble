#ifndef _DigitsTransitions_H_
#define _DigitsTransitions_H_

#include <Arduino.h>

class DigitsTransitions {
    public:
        static uint8_t digits[10][6][6];
        const static uint8_t FRAMES = 6;
        const static uint8_t LINES = 6;
};

#endif