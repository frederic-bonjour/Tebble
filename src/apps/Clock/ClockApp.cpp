#include "ClockApp.h"
#include "../../core/GraphicContext.h"


void ClockApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->verticalGradient(RgbColor(0, 0, 0), RgbColor(0, 100, 255));
    gc->setColor(RgbColor(255, 255, 0));
    gc->text(10, 10, "F");
}