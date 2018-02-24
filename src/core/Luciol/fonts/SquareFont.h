#ifndef _SquareFont_H_
#define _SquareFont_H_

#include <Arduino.h>

#include "Font.h"
#include "../Singleton.h"

#define SquareFontCharCount 40

class SquareFont : public Font, public Singleton<SquareFont>
{
  friend class Singleton<SquareFont>;

  private:

    static uint8_t chars[SquareFontCharCount][5];
    SquareFont();

  public:

    uint8_t  getHeight();
    bool     handlesDiacritics();
    uint8_t  getCharWidth(char c);
    uint8_t  getCharIndex(char c);
    uint8_t* getChar(char c);
};

#endif