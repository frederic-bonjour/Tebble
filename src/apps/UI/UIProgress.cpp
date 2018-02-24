#include "UIProgress.h"
#include "../../core/Luciol/GraphicContext.h"


void UIProgress::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->setDrawColor(RgbColor(255, 255, 255))->rectangle(0, 13, gc->getWidth(), 3);
    gc->setDrawColor(RgbColor(0, 0, 255))->horizontalLine(1, round(1 + progress * (gc->getWidth() - 2)), 14);
    //gc->verticalGradient(ambience->getPrimaryColor(), ambience->getSecondaryColor());
    //gc->setFillColor(RgbColor(20, 0, 40))->fill();
}