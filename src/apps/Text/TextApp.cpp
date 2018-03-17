#include "TextApp.h"
#include "../../core/Luciol/GraphicContext.h"


TextApp::TextApp() {
    text = "Bonne soiree!";
    fontName = "condensed";
}


void TextApp::willStart(GraphicContext* gc, Ambience* ambience) {
}


void TextApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->setFillColor(ambience->getPrimaryColor());
    gc->setDrawColor(ambience->getSecondaryColor());
    gc->setFont(fontName);

    x++;
    if (x > gc->getTextWidth(text)) {
        x = -(gc->getWidth() - 1);
    }
    gc->fill();
    gc->text(-x, 9, text);
}


void TextApp::setText(String t) {
    text = t;
}


void TextApp::setText(String t, String f) {
    text = t;
    fontName = f;
}