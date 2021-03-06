#include <Arduino.h>
#include "SquareFont.h"


SquareFont::SquareFont() {}


uint8_t SquareFont::getCharWidth(char c) {
    return 5;
}


uint8_t SquareFont::getCharIndex(char ch) {
    if (ch >= 48 && ch <= 57) {
        ch -= 48;
    } else if (ch >= 97 && ch <= 122) {
        ch = ch - 97 + 10;
    } else if (ch >= 65 && ch <= 90) {
        ch = ch - 65 + 10;
    } else if (ch == 45) {
        ch = 36;
    } else if (ch == 33) {
        ch = 37;
    } else if (ch == 63) {
        ch = 38;
    } else if (ch == 39) {
        ch = 39;
    } else {
        ch = -1;
    }
    return ch;
}


uint8_t* SquareFont::getChar(char c) {
    uint8_t index = getCharIndex(c);
    if (index < SquareFontCharCount) {
        return chars[index];
    }
    return NULL;
}


uint8_t SquareFont::getHeight() {
    return 5;
}


bool SquareFont::handlesDiacritics() {
    return false;
}


uint8_t SquareFont::chars[40][5] = {
    { 0x1F, 0x11, 0x11, 0x11, 0x1F }, // 0
    { 0x06, 0x02, 0x02, 0x02, 0x02 }, // 1
    { 0x1F, 0x01, 0x1F, 0x10, 0x1F }, // 2
    { 0x1F, 0x01, 0x0F, 0x01, 0x1F }, // 3
    { 0x11, 0x11, 0x1F, 0x01, 0x01 }, // 4
    { 0x1F, 0x10, 0x1F, 0x01, 0x1F }, // 5
    { 0x1F, 0x10, 0x1F, 0x11, 0x1F }, // 6
    { 0x1F, 0x01, 0x01, 0x01, 0x01 }, // 7
    { 0x1F, 0x11, 0x1F, 0x11, 0x1F }, // 8
    { 0x1F, 0x11, 0x1F, 0x01, 0x1F }, // 9

    { 0x1F, 0x11, 0x1F, 0x11, 0x11 }, // A
    { 0x1E, 0x11, 0x1E, 0x11, 0x1E }, // B
    { 0x1F, 0x10, 0x10, 0x10, 0x1F }, // C
    { 0x1E, 0x11, 0x11, 0x11, 0x1E }, // D
    { 0x1F, 0x10, 0x1E, 0x10, 0x1F }, // E
    { 0x1F, 0x10, 0x1E, 0x10, 0x10 }, // F
    { 0x1F, 0x10, 0x13, 0x11, 0x1F }, // G
    { 0x11, 0x11, 0x1F, 0x11, 0x11 }, // H
    { 0x07, 0x02, 0x02, 0x02, 0x07 }, // I
    { 0x1F, 0x04, 0x04, 0x04, 0x1C }, // J
    { 0x12, 0x14, 0x18, 0x14, 0x12 }, // K
    { 0x10, 0x10, 0x10, 0x10, 0x1F }, // L
    { 0x11, 0x1B, 0x15, 0x11, 0x11 }, // M
    { 0x11, 0x19, 0x15, 0x13, 0x11 }, // N
    { 0x0E, 0x11, 0x11, 0x11, 0x0E }, // O
    { 0x1E, 0x11, 0x1E, 0x10, 0x10 }, // P
    { 0x0E, 0x11, 0x15, 0x13, 0x0F }, // Q
    { 0x1E, 0x11, 0x1E, 0x14, 0x13 }, // R
    { 0x1F, 0x10, 0x1F, 0x01, 0x1F }, // S
    { 0x1F, 0x04, 0x04, 0x04, 0x04 }, // T
    { 0x11, 0x11, 0x11, 0x11, 0x1F }, // U
    { 0x11, 0x11, 0x11, 0x0A, 0x04 }, // V
    { 0x11, 0x11, 0x15, 0x15, 0x1B }, // W
    { 0x11, 0x0A, 0x04, 0x0A, 0x11 }, // X
    { 0x11, 0x11, 0x0A, 0x04, 0x04 }, // Y
    { 0x1F, 0x02, 0x04, 0x08, 0x1F }, // Z
    
    { 0x00, 0x00, 0x0F, 0x00, 0x00 }, // - (minus)
    { 0x04, 0x04, 0x04, 0x00, 0x04 }, // !
    { 0x0F, 0x01, 0x07, 0x00, 0x04 }, // ?
    { 0x04, 0x08, 0x00, 0x00, 0x00 }  // ' (single quote)
};