#include "TextApp.h"
#include "../../core/Luciol/GraphicContext.h"


TextApp::TextApp() {
    text = "Bonne soiree!";
    fontName = "condensed";
}


void TextApp::willStart(GraphicContext* gc, Ambience* ambience) {
    Runnable::willStart(gc, ambience);
    gc->setFont(fontName);
}


void TextApp::run(unsigned long time) {
    if (time >= 80) {
        x++;
        requestAnimationFrame();
    }
    if (fontChanged || textChanged) {
        requestAnimationFrame();
    }
}


void TextApp::paint(GraphicContext* gc, Ambience* ambience) {
    if (fontChanged) {
        gc->setFont(fontName);
        fontChanged = false;
    }
    if (textChanged) {
        x = -(gc->getWidth() - 1);
        textChanged = false;
    }

    if (x > gc->getTextWidth(text)) {
        x = -(gc->getWidth() - 1);
    }

    gc->setFillColor(ambience->getSecondaryColor());
    gc->setDrawColor(ambience->getPrimaryColor());

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


void TextApp::messageReceived(String data) {
    if (data.startsWith("font:")) {
        fontName = data.substring(5);
        fontName.trim();
        fontChanged = true;
    } else if (data.startsWith("text:")) {
        text = data.substring(5);
        text.trim();
        textChanged = true;
    }
}