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

        Runnable* transientRunnable = NULL;
        unsigned long int transientStart;
        unsigned long int transientEnd;

        std::map<String, Runnable*> appsById;

    public:

        void      loop();
        bool      setRunnable(String id);
        void      registerApp(String id, Runnable* runnable);
        String    getCurrentRunnableId();
        Runnable* getCurrentRunnable();

        void      setTransientRunnable(String id, unsigned long duration);

};

#endif