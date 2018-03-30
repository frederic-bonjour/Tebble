#include "SpectrumAnalyzerApp.h"
#include "../../core/Luciol/GraphicContext.h"


void SpectrumAnalyzerApp::run(unsigned long time) {
    static unsigned long last = millis();
    if (millis() - last >= 120) {
        last = millis();
        for (uint8_t f = 0; f < 7; f++) {
            values[f] = random(2, 16);
        }
        newValues = true;
    }
    
    requestAnimationFrame();
    if (newValues) {
        newValues = false;
    } else {
        for (uint8_t f = 0; f < 7; f++) {
            if (values[f]) values[f]--;
        }
    }
}


void SpectrumAnalyzerApp::paint(GraphicContext* gc, Ambience* ambience) {
    uint16_t y2 = gc->getHeight() - 1;
    for (uint8_t f = 0; f < 7; f++) {
        for (uint8_t y = 0; y < values[f]; y++) {
            gc->setPixel(2 + f*2, y2-y, gc->colorWheel((50 + y*16)%255));
            gc->setPixel(3 + f*2, y2-y, gc->colorWheel((50 + y*16)%255));
        }
    }
}


void SpectrumAnalyzerApp::handleMessage(String data) {
    sscanf(data.c_str(), "%u %u %u %u %u %u %u", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5], &values[6]);
    for (uint8_t f = 0; f < 7; f++) {
        values[f] = map(values[f], 0, 255, 0, 16);
    }
    newValues = true;
}