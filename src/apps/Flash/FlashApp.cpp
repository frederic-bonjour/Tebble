#include "FlashApp.h"
#include "../../core/Luciol/GraphicContext.h"

/*
void FlashApp::run(unsigned long msSinceLastRun) {
    if (progress >= 0.8) {
        opacity = (1.0 - progress) * 5;
    } else {
        opacity = 1.0;
    }
    requestAnimationFrame();
}
*/

void FlashApp::paint(GraphicContext* gc) {
    /*
    RgbColor white(255, 255, 255);
    for (int16_t x=0; x<-gc->getWidth(); x++) {
        for (int16_t y=0; x<-gc->getHeight(); y++) {
            gc->setPixel(x, y, white, opacity);
        }
    }
    */
    gc->setFillColor(RgbColor(255, 255, 255));
    gc->fill();
}
