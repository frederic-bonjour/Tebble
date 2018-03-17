#include "TimerApp.h"
#include "../../core/Luciol/GraphicContext.h"
#include "../../core/Luciol/PropertiesAnimator.h"

#include "../DigitsTransitions.h"


void TimerApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    if (remaining <= 0) {
        if (!stopped) {
            gc->drawImage(0, 0, "/bell.bmp");
            stopped = true;
        }
        return;
    }

    gc->setFillColor(RgbColor(0, 0, 50));
    gc->fill();

    uint16_t ellapsed = (millis() - startTime) / 1000;
    remaining = duration - ellapsed;
    uint16_t minutes = remaining / 60;
    uint16_t seconds = remaining % 60;

    nm1 = minutes / 10;
    if (nm1 != m1) {
        if (m1fi > 0) {
            m1fi--;
        } else {
            m1 = nm1;
            m1fi = DigitsTransitions::FRAMES - 1;
        }
    }
    
    nm2 = minutes % 10;
    if (nm2 != m2) {
        if (m2fi > 0) {
            m2fi--;
        } else {
            m2 = nm2;
            m2fi = DigitsTransitions::FRAMES - 1;
        }
    }


    ns1 = seconds / 10;
    if (ns1 != s1) {
        if (s1fi > 0) {
            s1fi--;
        } else {
            s1 = ns1;
            s1fi = DigitsTransitions::FRAMES - 1;
        }
    }

    ns2 = seconds % 10;
    if (ns2 != s2) {
        if (s2fi > 0) {
            s2fi--;
        } else {
            s2 = ns2;
            s2fi = DigitsTransitions::FRAMES - 1;
        }
    }

    if (remaining <= 30) {
        gc->setDrawColor(RgbColor::LinearBlend(RgbColor(255, 0, 0), ambience->getPrimaryColor(), remaining/30.0));
    } else {
        gc->setDrawColor(ambience->getPrimaryColor());
    }

    uint8_t* mask;
    uint8_t w;

    // M1
    mask = DigitsTransitions::digits[m1 > 0 ? m1 - 1 : 9][m1fi];
    gc->drawBitMask(2, 2, mask, 6, DigitsTransitions::LINES);

    // M2
    mask = DigitsTransitions::digits[m2 > 0 ? m2 - 1 : 9][m2fi];
    w = gc->getBitMaskMaxWidth(mask, DigitsTransitions::LINES);
    gc->drawBitMask(9 - (6-w), 2, mask, 6, DigitsTransitions::LINES);
    
    // S1
    mask = DigitsTransitions::digits[s1 > 0 ? s1 - 1 : 9][s1fi];
    gc->drawBitMask(2, 9, mask, 6, DigitsTransitions::LINES);

    // S2
    mask = DigitsTransitions::digits[s2 > 0 ? s2 - 1 : 9][s2fi];
    w = gc->getBitMaskMaxWidth(mask, 6);
    gc->drawBitMask(9 - (6-w), 9, mask, 6, DigitsTransitions::LINES);
}


void TimerApp::reset(uint16_t d) {
    startTime = millis();
    stopped = false;

    duration = d; 
    remaining = duration;

    uint8_t m = d / 60;
    m1 = m / 10;
    m2 = m % 10;
    uint8_t s = d % 60;
    s1 = s / 10;
    s2 = s % 10;

    m1fi = DigitsTransitions::FRAMES - 1;
    m2fi = DigitsTransitions::FRAMES - 1;
    s1fi = DigitsTransitions::FRAMES - 1;
    s2fi = DigitsTransitions::FRAMES - 1;
}


void TimerApp::reset() {
    reset(duration);
}


void TimerApp::willWakeUp(GraphicContext* gc, Ambience* ambience) {
    reset();
}


void TimerApp::handleMessage(String data) {
    if (data == "reset") {
        reset();
    } else if (data.startsWith("set ")) {
        reset(data.substring(4).toInt());
    }
}