#include "GradientApp.h"
#include "../../core/GraphicContext.h"


void GradientApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->verticalGradient(ambience->getPrimaryColor(), ambience->getSecondaryColor());
    //gc->setFillColor(RgbColor(20, 0, 40))->fill();
}