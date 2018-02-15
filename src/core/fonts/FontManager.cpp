#include <Arduino.h>
#include "FontManager.h"

#include "SquareFont.h"

FontManager FontManager::instance;


FontManager::FontManager() {
    fonts["square"] = &SquareFont::get();
    Serial.print("Loaded fonts: "); Serial.println(fonts.size());
}


Font* FontManager::getFont(String name) {
    return fonts[name];
}

