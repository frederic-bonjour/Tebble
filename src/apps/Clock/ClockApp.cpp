#include "ClockApp.h"
#include "../../core/Luciol/GraphicContext.h"
#include "../../core/Luciol/PropertiesAnimator.h"
#include "../../core/Luciol/Clock.h"

#include "../DigitsTransitions.h"

void drawSeconds(GraphicContext* gc, uint8_t s, RgbColor color, bool dim) {
    if (dim) {
        color.Darken(170);
    }

    if (s <= 15) {
        gc->setPixel(s, 0, color);
    }
    else if (s <= 30) {
        if (dim && s == 16) {
            gc->setPixel(16, 0, color);
        }
        gc->setPixel(16, s - 15, color);
    }
    else if (s <= 45) {
        if (dim && s == 31) {
            gc->setPixel(16, 16, color);
        }
        gc->setPixel(16 - (s - 30), 16, color);
    } else {
        if (dim && s == 46) {
            gc->setPixel(0, 16, color);
        }
        gc->setPixel(0, 16 - (s - 45), color);
    }
}

void ClockApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->setFillColor(RgbColor(0, 0, 50));
    gc->fill();

    //int hours = Clock::getMinutes();
    //int minutes = Clock::getSeconds();
    int hours = Clock::getHours();
    int minutes = Clock::getMinutes();
    int seconds = Clock::getSeconds();

    nh1 = hours / 10;
    if (nh1 != h1) {
        if (h1fi < (DigitsTransitions::FRAMES-1)) {
            h1fi++;
        } else {
            h1 = nh1;
            h1fi = 0;
        }
    }

    nh2 = hours % 10;
    if (nh2 != h2) {
        if (h2fi < (DigitsTransitions::FRAMES-1)) {
            h2fi++;
        } else {
            h2 = nh2;
            h2fi = 0;
        }
    }

    nm1 = minutes / 10;
    if (nm1 != m1) {
        if (m1fi < (DigitsTransitions::FRAMES-1)) {
            m1fi++;
        } else {
            m1 = nm1;
            m1fi = 0;
        }
    }
    
    nm2 = minutes % 10;
    if (nm2 != m2) {
        if (m2fi < (DigitsTransitions::FRAMES-1)) {
            m2fi++;
        } else {
            m2 = nm2;
            m2fi = 0;
        }
    }

    gc->setDrawColor(RgbColor(0, 100, 255));

    uint8_t* mask;
    uint8_t w;
    
    // H1
    mask = DigitsTransitions::digits[h1][h1fi];
    gc->drawBitMask(2, 2, mask, 6, DigitsTransitions::LINES);

    // H2
    mask = DigitsTransitions::digits[h2][h2fi];
    w = gc->getBitMaskMaxWidth(mask, 6);
    gc->drawBitMask(9 - (6-w), 2, mask, 6, DigitsTransitions::LINES);

    // M1
    mask = DigitsTransitions::digits[m1][m1fi];
    gc->drawBitMask(2, 9, mask, 6, DigitsTransitions::LINES);

    // M2
    mask = DigitsTransitions::digits[m2][m2fi];
    w = gc->getBitMaskMaxWidth(mask, DigitsTransitions::LINES);
    gc->drawBitMask(9 - (6-w), 9, mask, 6, DigitsTransitions::LINES);

    RgbColor c(255, 0, 100);
    for (uint8_t s = 0; s < seconds; s++) {
        drawSeconds(gc, s, c, true);
    }
    drawSeconds(gc, seconds, RgbColor(255, 0, 100), false);
    
}


void ClockApp::willWakeUp(GraphicContext* gc, Ambience* ambience) {
    Clock::sync();

    //int hours = Clock::getMinutes();
    //int minutes = Clock::getSeconds();
    int hours = Clock::getHours();
    int minutes = Clock::getMinutes();
    h1 = hours / 10;
    h2 = hours % 10;
    m1 = minutes / 10;
    m2 = minutes % 10;

    h1fi = 0;
    h2fi = 0;
    m1fi = 0;
    m2fi = 0;
}
