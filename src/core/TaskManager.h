#ifndef _TaskManager_H_
#define _TaskManager_H_

#include "core.h"
#include <map>

typedef std::map<String, Runnable*> AppsById;


class TaskManager {

    static TaskManager instance;
    TaskManager();

    Runnable *currentRunnable;
    AppsById appsById;

    public:
        static TaskManager &get() noexcept {
            return instance;
        }

        void loop();
        void setRunnable(String id);
        void registerApp(String id, Runnable* runnable);

};

#endif