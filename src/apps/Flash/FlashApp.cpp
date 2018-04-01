#include "FlashApp.h"
#include "../../core/Luciol/GraphicContext.h"
#include "../../core/Luciol/Clock.h"


void FlashApp::paint(GraphicContext* gc, Ambience* ambience) {
    gc->setFillColor(RgbColor(255, 255, 255));
    gc->fill();
}
