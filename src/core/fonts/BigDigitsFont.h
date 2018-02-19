#ifndef _BigDigitsFont_H_
#define _BigDigitsFont_H_

#include <Arduino.h>

#include "Font.h"
#include "../Singleton.h"

class BigDigitsFont : public Font, public Singleton<BigDigitsFont>
{
  friend class Singleton<BigDigitsFont>;

  private:

    static uint8_t chars[10][7];
    BigDigitsFont();

  public:

    uint8_t  getHeight();
    bool     handlesDiacritics();
    uint8_t  getCharWidth(char c);
    uint8_t  getCharIndex(char c);
    uint8_t* getChar(char c);
};

#endif