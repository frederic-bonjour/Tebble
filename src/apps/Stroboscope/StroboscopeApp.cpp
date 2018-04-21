#include "StroboscopeApp.h"
#include "../../core/Luciol/GraphicContext.h"


void StroboscopeApp::run(unsigned long time) {
    if (on) {
        if (time > 15) {
            on = false;
            requestAnimationFrame();
        }
    } else {
        if (time > 150) {
            on = true;
            requestAnimationFrame();
        }
    }
}


void StroboscopeApp::paint(GraphicContext* gc) {
    if (on) {
        gc->setFillColor(RgbColor(255, 255, 255));
        gc->fill();
    } else {
        gc->clear();
    }
}
