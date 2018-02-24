#include <Arduino.h>
#include "FontManager.h"

#include "SquareFont.h"
#include "BigDigitsFont.h"
#include "CondensedFont.h"


FontManager::FontManager() {
    fonts["condensed"] = CondensedFont::get();
    fonts["square"] = SquareFont::get();
    fonts["bigdigits"] = BigDigitsFont::get();
    //Serial.print("Loaded fonts: "); Serial.println(fonts.size());
}


bool FontManager::isFontAvailable(String fontName) {
    fontName.toLowerCase();
    FontByName::iterator it = fonts.find(fontName);
    return it != fonts.end();    
}


Font* FontManager::getFont(String fontName) {
    if (isFontAvailable(fontName)) {
        return fonts[fontName];
    }
    return fonts["condensed"];
}

