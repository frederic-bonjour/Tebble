#ifndef _FontManager_H_
#define _FontManager_H_

#include <Arduino.h>
#include <map>

#include "Font.h"

typedef std::map<String, Font*> FontByName;


class FontManager
{
  private:

    static FontManager instance;
    FontManager();

    FontByName fonts;

  public:

    static FontManager &get() noexcept {
        return instance;
    }

    Font* getFont(String name);
};

#endif