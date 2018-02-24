#ifndef _Font_H_
#define _Font_H_

#include <Arduino.h>

class Font
{
  private:

  public:

    virtual uint8_t  getHeight();
    virtual bool     handlesDiacritics();
    virtual uint8_t  getCharWidth(char c);
    virtual uint8_t  getCharIndex(char c);
    virtual uint8_t* getChar(char c);
};

#endif