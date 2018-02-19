#include "TextApp.h"
#include "../../core/GraphicContext.h"


TextApp::TextApp() {
    text = "Bienvenue sur Tebble!";
    fontName = "condensed";
}


void TextApp::wakeUp(GraphicContext* gc, Ambience* ambience) {
    gc->setFillColor(ambience->getSecondaryColor());
    gc->setFont(fontName);
    gc->setDrawColor(ambience->getPrimaryColor());
}


void TextApp::run(GraphicContext* gc, Ambience* ambience, unsigned long time) {
    gc->setFillColor(ambience->getSecondaryColor());
    gc->setDrawColor(ambience->getPrimaryColor());

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