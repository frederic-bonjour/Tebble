#include <Arduino.h>
#include "CondensedFont.h"


CondensedFont::CondensedFont() {}


uint8_t CondensedFont::getCharWidth(char c) {
    if (c == ' ') return 3;
    uint8_t ci = getCharIndex(c);
    if (ci >= 59) {
        return 3;
    }
    uint8_t* ch = chars[ci];
    if (! ch) {
        return 3;
    }
    return ch[5];
}


uint8_t CondensedFont::getCharIndex(char c) {
    // Special chars
    switch (c) {
        case 95:
            return 59;
        case 176:
            return 58;
    }
    
    // lowercase -> UPPERCASE
    if (c >= 97 && c <= 122) {
        c -= 32;
    }
    
    c -= 33; // Skip non-printable chars		
    
    return c;
}


uint8_t* CondensedFont::getChar(char c) {
    uint8_t index = getCharIndex(c);
    if (index < CondensedFontCharCount) {
        return chars[index];
    }
    return NULL;
}


uint8_t CondensedFont::getHeight() {
    return 5;
}


bool CondensedFont::handlesDiacritics() {
    return false;
}


uint8_t CondensedFont::chars[CondensedFontCharCount][6] = {
    // 33 (0)
    
    { 0x01, 0x01, 0x01, 0x00, 0x01, 1 }, // !
    { 0x05, 0x05, 0x00, 0x00, 0x00, 3 }, // "
    { 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 5 }, // #
    { 0x00, 0x00, 0x00, 0x00, 0x00, 5 }, // $ TODO
    { 0x04, 0x01, 0x02, 0x04, 0x01, 3 }, // %
    { 0x00, 0x00, 0x00, 0x00, 0x00, 5 }, // & TODO
    { 0x01, 0x01, 0x00, 0x00, 0x00, 1 }, // '
    { 0x01, 0x02, 0x02, 0x02, 0x01, 2 }, // (
    { 0x02, 0x01, 0x01, 0x01, 0x02, 2 }, // )
    { 0x00, 0x00, 0x00, 0x00, 0x00, 5 }, // * TODO
    { 0x00, 0x02, 0x07, 0x02, 0x00, 3 }, // +
    { 0x00, 0x00, 0x00, 0x01, 0x02, 2 }, // ,
    { 0x00, 0x00, 0x07, 0x00, 0x00, 3 }, // -
    { 0x00, 0x00, 0x00, 0x00, 0x01, 1 }, // .
    { 0x01, 0x02, 0x04, 0x08, 0x10, 5 }, // /
    
    // 48 (15)
    
    // Digits
    { 0x07, 0x05, 0x05, 0x05, 0x07, 3 }, // 0
    { 0x02, 0x06, 0x02, 0x02, 0x07, 3 }, // 1
    { 0x07, 0x01, 0x07, 0x04, 0x07, 3 }, // 2
    { 0x07, 0x01, 0x07, 0x01, 0x07, 3 }, // 3
    { 0x05, 0x05, 0x07, 0x01, 0x01, 3 }, // 4
    { 0x07, 0x04, 0x07, 0x01, 0x07, 3 }, // 5
    { 0x07, 0x04, 0x07, 0x05, 0x07, 3 }, // 6
    { 0x07, 0x01, 0x01, 0x01, 0x01, 3 }, // 7
    { 0x07, 0x05, 0x07, 0x05, 0x07, 3 }, // 8
    { 0x07, 0x05, 0x07, 0x01, 0x07, 3 }, // 9

    { 0x00, 0x02, 0x00, 0x02, 0x00, 3 }, // :
    { 0x00, 0x02, 0x00, 0x02, 0x04, 4 }, // ;
    { 0x00, 0x00, 0x00, 0x00, 0x00, 5 }, // < TODO
    { 0x00, 0x07, 0x00, 0x07, 0x00, 3 }, // =
    { 0x00, 0x00, 0x00, 0x00, 0x00, 5 }, // > TODO
    { 0x07, 0x01, 0x03, 0x00, 0x02, 3 }, // ?
    { 0x0E, 0x15, 0x17, 0x10, 0x0E, 5 }, // @

    // Capital letters A-Z
    // 65 (32)
    { 0x07, 0x05, 0x07, 0x05, 0x05, 3 }, // A
    { 0x0E,	0x09, 0x0E, 0x09, 0x0E, 4 }, // B
    { 0x07,	0x04, 0x04,	0x04, 0x07, 3 }, // C
    { 0x0E, 0x09, 0x09, 0x09, 0x0E, 4 }, // D
    { 0x07, 0x04, 0x06, 0x04, 0x07, 3 }, // E
    { 0x07, 0x04, 0x06, 0x04, 0x04, 3 }, // F
    { 0x0F, 0x08, 0x0B, 0x09, 0x0F, 4 }, // G
    { 0x05, 0x05, 0x07, 0x05, 0x05, 3 }, // H
    { 0x07, 0x02, 0x02, 0x02, 0x07, 3 }, // I
    { 0x07, 0x02, 0x02, 0x02, 0x06, 3 }, // J
    { 0x09, 0x0A, 0x0C, 0x0A, 0x09, 4 }, // K
    { 0x04, 0x04, 0x04, 0x04, 0x07, 3 }, // L
    { 0x11, 0x1B, 0x15, 0x11, 0x11, 5 }, // M
    { 0x11, 0x19, 0x15, 0x13, 0x11, 5 }, // N
    { 0x06, 0x09, 0x09, 0x09, 0x06, 4 }, // O
    { 0x0E, 0x09, 0x0E, 0x08, 0x08, 4 }, // P
    { 0x06, 0x09, 0x09, 0x0A, 0x05, 4 }, // Q
    { 0x0E, 0x09, 0x0E, 0x09, 0x09, 4 }, // R
    { 0x07, 0x04, 0x07, 0x01, 0x07, 3 }, // S
    { 0x07, 0x02, 0x02, 0x02, 0x02, 3 }, // T
    { 0x05, 0x05, 0x05, 0x05, 0x07, 3 }, // U
    { 0x11, 0x11, 0x0A, 0x0A, 0x04, 5 }, // V
    { 0x11, 0x11, 0x15, 0x15, 0x1B, 5 }, // W
    { 0x11, 0x0A, 0x04, 0x0A, 0x11, 5 }, // X
    { 0x05, 0x05, 0x02, 0x02, 0x02, 3 }, // Y
    { 0x07, 0x01, 0x02, 0x04, 0x07, 3 }, // Z

    // Special chars
    // (58)
    { 0x07, 0x05, 0x07, 0x00, 0x00, 3 }, // °
    { 0x00, 0x00, 0x00, 0x00, 0x0F, 4 }  // _
    
    // l1    l2    l3    l4    l5   ^ width
};