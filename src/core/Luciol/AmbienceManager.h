#ifndef _AmbienceManager_H_
#define _AmbienceManager_H_

#include <map>

#include "Settings.h"
#include "Ambience.h"
#include "Singleton.h"

#define AMBIENCE_LOAD_URL "/download/luciol/ambiences.txt"
#define HTTP_TIMEOUT_MS 10000

typedef std::map<String, Ambience*> AmbiencesById;


class AmbienceManager : public Singleton<AmbienceManager> {

    friend class Singleton<AmbienceManager>;

    AmbienceManager();

    Ambience* currentAmbience;
    AmbiencesById ambiencesById;

    public:

        void registerAmbience(String id, Ambience* ambience);
        void load();

        Ambience* getAmbience();
        void setAmbience(String id);
        unsigned int count();
};

#endif