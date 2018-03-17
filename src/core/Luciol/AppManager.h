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
        String    currentRunnableId;
        Runnable* previousRunnable = NULL;
        bool      shouldWakeUpApp  = false;

        std::map<String, Runnable*> appsById;

    public:

        void      loop();
        void      setRunnable(String id);
        void      registerApp(String id, Runnable* runnable);
        String    getCurrentRunnableId();
        Runnable* getCurrentRunnable();

};

#endif