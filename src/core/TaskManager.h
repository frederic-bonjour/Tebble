#ifndef _TaskManager_H_
#define _TaskManager_H_

#include "core.h"
#include "Runnable.h"
#include <map>

typedef std::map<String, Runnable*> IdRunnableMap;


class TaskManager {

    static TaskManager instance;
    TaskManager();

    Runnable *currentRunnable;
    IdRunnableMap appsById;
    IdRunnableMap uiById;

    public:
        static TaskManager &get() noexcept {
            return instance;
        }

        void loop();
        void setRunnable(String id);
        void registerApp(String id, Runnable* runnable);
        void registerUI(String id, Runnable* runnable);
        void showUI(String id);

};

#endif