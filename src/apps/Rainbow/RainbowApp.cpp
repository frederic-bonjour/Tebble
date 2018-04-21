#include "RainbowApp.h"
#include "../../core/Luciol/GraphicContext.h"
#include "../../core/Luciol/PropertiesAnimator.h"


void RainbowApp::run(unsigned long time) {
    if (time >= 60) {
        pos++;
        requestAnimationFrame();
    }
}


void RainbowApp::paint(GraphicContext* gc) {
    switch (mode) {
        case SIDES:
            paintSides(gc);
            break;
        case UNIQUE:
            paintUnique(gc);
            break;
        default:
            paintPlain(gc);
            break;
    }
}


void RainbowApp::paintSides(GraphicContext* gc) {
    float step = 255.0 / (gc->getWidth() * 2 + (gc->getHeight()-2) * 2);
    float p = 0.0;

    uint16_t x2 = gc->getWidth() - 1;
    uint16_t y2 = gc->getHeight() - 1;

    gc->clear();
    for (int8_t x = 0; x<gc->getWidth(); x++) {
        gc->setPixel(x, 0, gc->colorWheel(round(p) + pos));
        p += step;
    }
    for (int8_t y = 1; y<gc->getHeight()-1; y++) {
        gc->setPixel(x2, y, gc->colorWheel(round(p) + pos));
        p += step;
    }
    for (int8_t x = x2; x >= 0; x--) {
        gc->setPixel(x, y2, gc->colorWheel(round(p) + pos));
        p += step;
    }
    for (int8_t y = y2-1; y > 0; y--) {
        gc->setPixel(0, y, gc->colorWheel(round(p) + pos));
        p += step;
    }
}


void RainbowApp::paintPlain(GraphicContext* gc) {
    float step = 255.0 / (gc->getHeight() * 1.5);
    float p = 0.0;

    uint16_t x2 = gc->getWidth() - 1;
    uint16_t y2 = gc->getHeight() - 1;

    for (int8_t y = 0; y<gc->getHeight(); y++) {
        gc->setDrawColor(gc->colorWheel(round(p) + pos));
        gc->horizontalLine(y);
        p += step;
    }
}


void RainbowApp::paintUnique(GraphicContext* gc) {
    gc->setFillColor(gc->colorWheel(pos));
    gc->fill();
}


void RainbowApp::messageReceived(String data) {
    if (data == "plain") {
        mode = PLAIN;
    } else if (data == "sides") {
        mode = SIDES;
    } else if (data == "unique") {
        mode = UNIQUE;
    }
}