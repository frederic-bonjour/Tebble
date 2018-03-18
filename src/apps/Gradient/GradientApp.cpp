#include "GradientApp.h"
#include "../../core/Luciol/GraphicContext.h"


void GradientApp::paint(GraphicContext* gc, Ambience* ambience) {
    gc->verticalGradient(ambience->getPrimaryColor(), ambience->getSecondaryColor());
}