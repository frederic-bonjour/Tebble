#include "ClockApp.h"
#include "../../core/Luciol/GraphicContext.h"
#include "../../core/Luciol/PropertiesAnimator.h"

#include <vector>

#define DIGIT_TRANSITION_FRAMES 7

uint8_t digitsTransitions[10][DIGIT_TRANSITION_FRAMES][7] = {
    {   // 0 -> 1
        { 0x7F, 0x41, 0x41, 0x41, 0x41, 0x41, 0X7F }, // 0
        { 0x3F, 0x21, 0x21, 0x21, 0x21, 0x21, 0x3F },
        { 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F },
        { 0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F },
        { 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07 },
        { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07 },
        { 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }  // 1
    },
    {
        // 1 -> 2
        { 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, // 1
        { 0x03, 0x01, 0x01, 0x03, 0x02, 0x02, 0x03 },
        { 0x07, 0x01, 0x01, 0x07, 0x04, 0x04, 0x07 },
        { 0x0F, 0x01, 0x01, 0x0F, 0x08, 0x08, 0x0F },
        { 0x1F, 0x01, 0x01, 0x1F, 0x10, 0x10, 0x1F },
        { 0x3F, 0x01, 0x01, 0x3F, 0x20, 0x20, 0x3F },
        { 0x7F, 0x01, 0x01, 0x7F, 0x40, 0x40, 0x7F }  // 2
    },
    {
        // 2 -> 3
        { 0x7F, 0x01, 0x01, 0x7F, 0x40, 0x40, 0x7F }, // 2
        { 0x7F, 0x01, 0x01, 0x3F, 0x20, 0x20, 0x7F },
        { 0x7F, 0x01, 0x01, 0x1F, 0x10, 0x10, 0x7F },
        { 0x7F, 0x01, 0x01, 0x0F, 0x08, 0x08, 0x7F },
        { 0x7F, 0x01, 0x01, 0x0F, 0x04, 0x04, 0x7F },
        { 0x7F, 0x01, 0x01, 0x0F, 0x02, 0x02, 0x7F },
        { 0x7F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x7F }  // 3
    },
    {
        // 3 -> 4
        { 0x7F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x7F }, // 3
        { 0x03, 0x03, 0x03, 0x0F, 0x01, 0x01, 0x3F },
        { 0x05, 0x05, 0x05, 0x0F, 0x01, 0x01, 0x1F },
        { 0x09, 0x09, 0x09, 0x0F, 0x01, 0x01, 0x0F },
        { 0x11, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x07 },
        { 0x21, 0x21, 0x21, 0x3F, 0x01, 0x01, 0x03 },
        { 0x41, 0x41, 0x41, 0x7F, 0x01, 0x01, 0x01 }  // 4
    },
    {
        // 4 -> 5
        { 0x41, 0x41, 0x41, 0x7F, 0x01, 0x01, 0x01 }, // 4
        { 0x43, 0x42, 0x42, 0x7F, 0x01, 0x01, 0x03 },
        { 0x47, 0x44, 0x44, 0x7F, 0x01, 0x01, 0x07 },
        { 0x4F, 0x48, 0x48, 0x7F, 0x01, 0x01, 0x0F },
        { 0x5F, 0x50, 0x50, 0x7F, 0x01, 0x01, 0x1F },
        { 0x6F, 0x60, 0x60, 0x7F, 0x01, 0x01, 0x3F },
        { 0x7F, 0x40, 0x40, 0x7F, 0x01, 0x01, 0x7F }  // 5
    },
    {
        // 5 -> 6
        { 0x7F, 0x40, 0x40, 0x7F, 0x01, 0x01, 0x7F }, // 5
        { 0x7F, 0x40, 0x40, 0x7F, 0x03, 0x03, 0x7F },
        { 0x7F, 0x40, 0x40, 0x7F, 0x05, 0x05, 0x7F },
        { 0x7F, 0x40, 0x40, 0x7F, 0x09, 0x09, 0x7F },
        { 0x7F, 0x40, 0x40, 0x7F, 0x11, 0x11, 0x7F },
        { 0x7F, 0x40, 0x40, 0x7F, 0x21, 0x21, 0x7F },
        { 0x7F, 0x40, 0x40, 0x7F, 0x41, 0x41, 0x7F }  // 6
    },

    {
        // 6 -> 7
        { 0x7F, 0x40, 0x40, 0x7F, 0x41, 0x41, 0x7F }, // 6
        { 0x7F, 0x20, 0x20, 0x3F, 0x21, 0x21, 0x3F },
        { 0x7F, 0x10, 0x10, 0x1F, 0x11, 0x11, 0x1F },
        { 0x7F, 0x08, 0x08, 0x0F, 0x09, 0x09, 0x0F },
        { 0x7F, 0x04, 0x04, 0x07, 0x05, 0x05, 0x07 },
        { 0x7F, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03 },
        { 0x7F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }  // 7
    },
    {
        // 7 -> 8
        { 0x7F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, // 7
        { 0x7F, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 },
        { 0x7F, 0x05, 0x05, 0x07, 0x05, 0x05, 0x07 },
        { 0x7F, 0x09, 0x09, 0x0F, 0x09, 0x09, 0x0F },
        { 0x7F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F },
        { 0x7F, 0x21, 0x21, 0x3F, 0x21, 0x21, 0x3F },
        { 0x7F, 0x41, 0x41, 0x7F, 0x41, 0x41, 0x7F }  // 8
    },
    {
        // 8 -> 9
        { 0x7F, 0x41, 0x41, 0x7F, 0x41, 0x41, 0x7F }, // 8
        { 0x7F, 0x41, 0x41, 0x7F, 0x21, 0x21, 0x7F },
        { 0x7F, 0x41, 0x41, 0x7F, 0x11, 0x11, 0x7F },
        { 0x7F, 0x41, 0x41, 0x7F, 0x09, 0x09, 0x7F },
        { 0x7F, 0x41, 0x41, 0x7F, 0x05, 0x05, 0x7F },
        { 0x7F, 0x41, 0x41, 0x7F, 0x03, 0x03, 0x7F },
        { 0x7F, 0x41, 0x41, 0x7F, 0x01, 0x01, 0x7F }  // 9
    },
    {
        // 9 -> 0
        { 0x7F, 0x41, 0x41, 0x7F, 0x01, 0x01, 0x7F }, // 9
        { 0x7F, 0x41, 0x41, 0x7F, 0x03, 0x03, 0x7F },
        { 0x7F, 0x41, 0x41, 0x7D, 0x05, 0x05, 0x7F },
        { 0x7F, 0x41, 0x41, 0x79, 0x09, 0x09, 0x7F },
        { 0x7F, 0x41, 0x41, 0x71, 0x11, 0x11, 0x7F },
        { 0x7F, 0x41, 0x41, 0x61, 0x21, 0x21, 0x7F },
        { 0x7F, 0x41, 0x41, 0x41, 0x41, 0x41, 0X7F }  // 0
    }
};


ClockApp::ClockApp() {
    pa1in.add("x", new Property<int>(1000, -9, 1));
    pa1in.add("y", new Property<int>(1));

    pa1out.add("y", new Property<int>(1000, 1, -9));
    pa1out.add("x", new Property<int>(1));
    
    hours = 0;
    minutes = 0;
    updateStrings();
}


void ClockApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->verticalGradient(RgbColor(0, 0, 0), RgbColor(80, 60, 0));
    //gc->setColor(RgbColor(255, 200, 0)); orange cool
    //gc->clear();
    //int y = pa1.getInt("y");
    //Serial.print("y="); Serial.println(y);
    
    static uint8_t digit = 0;
    static uint8_t frame = 0;

    gc->drawBitMask(9, 9, digitsTransitions[digit][frame], 7, 7);
    
    byte d = tick();
    if (d) {
        if (digit == 9) {
            digit = 0;
        } else {
            digit++;
        }
        frame = 0;
    } else {
        if (frame < (DIGIT_TRANSITION_FRAMES-1)) {
            frame++;
        }
    }

    //if (d) Serial.println(d);
    //gc->text(1, 1, strHours);
    //gc->text(1, 9, strMinutes);
}


void ClockApp::wakeUp(GraphicContext* gc, Ambience* ambience) {
    //pa1.start();
    gc->setFont("bigdigits");
    gc->setDrawColor(RgbColor(0, 128, 200));
    wakeUpTime = millis();
}


void ClockApp::updateStrings() {
    if (hours < 10) {
        strHours = String("0") + hours;
    } else {
        strHours = String(hours);
    }
    if (minutes < 10) {
        strMinutes = String("0") + minutes;
    } else {
        strMinutes = String(minutes);
    }
}


byte ClockApp::tick() {
    byte result = 0;
    unsigned long now = millis();
    
    if ((now - wakeUpTime) >= 1000 * 1) { // TODO
        result += 1;
        wakeUpTime = now;
        minutes++;
        if (minutes % 10 == 0) {
            result += 2;
        }
        if (minutes == 20) { // TODO
            minutes = 0;
            hours++;
            result += 4;
            if (hours == 24) {
                hours = 0;
            }
            if (hours % 10 == 0) {
                result += 8;
            }
        }
        updateStrings();
    }

    return result;
}