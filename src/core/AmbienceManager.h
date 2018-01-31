#ifndef _AmbienceManager_H_
#define _AmbienceManager_H_

#include "core.h"
#include "Ambience.h"
#include <map>

#define AMBIENCE_LOAD_URL "/download/luciol/ambiences.txt"
#define HTTP_TIMEOUT_MS 10000

typedef std::map<String, Ambience*> AmbiencesById;


class AmbienceManager {

    static AmbienceManager instance;
    AmbienceManager();

    Ambience* currentAmbience;
    AmbiencesById ambiencesById;

    public:
        static AmbienceManager &get() noexcept {
            return instance;
        }

        void registerAmbience(String id, Ambience* ambience);
        void load();

        Ambience* getAmbience();
        void setAmbience(String id);
        unsigned int count();
};

#endif