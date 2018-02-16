#ifndef _FontManager_H_
#define _FontManager_H_

#include <Arduino.h>
#include <map>

#include "../Singleton.h"
#include "Font.h"

typedef std::map<String, Font*> FontByName;


class FontManager : public Singleton<FontManager>
{
  friend class Singleton<FontManager>;

  private:

    FontManager();

    FontByName fonts;

  public:

    Font* getFont(String name);
};

#endif