#ifndef _SquareFont_H_
#define _SquareFont_H_

#include <Arduino.h>

#include "Font.h"

class SquareFont : public Font
{
  private:

    static uint8_t chars[40][5];
    static SquareFont instance;
    SquareFont();

  public:

    static SquareFont &get() noexcept {
        return instance;
    }

    uint8_t  getHeight();
    bool     handlesDiacritics();
    uint8_t  getCharWidth(char c);
    uint8_t  getCharIndex(char c);
    uint8_t* getChar(char c);
};

#endif