#include "ClockApp.h"
#include "../../core/GraphicContext.h"


void ClockApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->verticalGradient(RgbColor(0, 0, 0), RgbColor(0, 100, 100));
    //gc->setColor(RgbColor(255, 200, 0)); orange cool
    //gc->clear();
    gc->setDrawColor(RgbColor(255, 255, 255));
    gc->setFont("condensed");
    gc->text(0, 9, "Fred");
}