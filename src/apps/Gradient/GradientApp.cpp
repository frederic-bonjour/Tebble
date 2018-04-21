#include "GradientApp.h"
#include "../../core/Luciol/GraphicContext.h"


void GradientApp::paint(GraphicContext* gc) {
    gc->verticalGradient(Ambience::getPrimaryColor(), Ambience::getSecondaryColor());
}