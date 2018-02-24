#ifndef _CondensedFont_H_
#define _CondensedFont_H_

#include <Arduino.h>

#include "Font.h"
#include "../Singleton.h"

#define CondensedFontCharCount 60

class CondensedFont : public Font, public Singleton<CondensedFont>
{
  friend class Singleton<CondensedFont>;

  private:

    static uint8_t chars[CondensedFontCharCount][6];
    CondensedFont();

  public:

    uint8_t  getHeight();
    bool     handlesDiacritics();
    uint8_t  getCharWidth(char c);
    uint8_t  getCharIndex(char c);
    uint8_t* getChar(char c);
};

#endif