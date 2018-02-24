#ifndef _TaskManager_H_
#define _TaskManager_H_

#include <map>

#include "Runnable.h"
#include "Singleton.h"

#include "AmbienceManager.h"


class AppManager : public Singleton<AppManager> {

    friend class Singleton<AppManager>;

    private:
        AppManager();

        Runnable* currentRunnable  = NULL;
        Runnable* previousRunnable = NULL;
        std::map<String, Runnable*> appsById;
        bool shouldWakeUpApp = false;

    public:

        void loop();
        void setRunnable(String id);
        void registerApp(String id, Runnable* runnable);

};

#endif