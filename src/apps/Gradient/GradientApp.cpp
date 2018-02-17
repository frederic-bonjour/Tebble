#include "GradientApp.h"
#include "../../core/GraphicContext.h"


void GradientApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->verticalGradient(ambience->getPrimaryColor(), ambience->getSecondaryColor());
}