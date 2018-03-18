#include "TextApp.h"
#include "../../core/Luciol/GraphicContext.h"


TextApp::TextApp() {
    text = "Bonne soiree!";
    fontName = "condensed";
}


void TextApp::willStart(GraphicContext* gc, Ambience* ambience) {
}


void TextApp::run(unsigned long time) {
    x++;
    requestAnimationFrame();
}


void TextApp::paint(GraphicContext* gc, Ambience* ambience) {
    if (x > gc->getTextWidth(text)) {
        x = -(gc->getWidth() - 1);
    }
    gc->setFillColor(ambience->getPrimaryColor());
    gc->setDrawColor(ambience->getSecondaryColor());
    gc->setFont(fontName);
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