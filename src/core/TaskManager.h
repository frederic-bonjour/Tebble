#ifndef _TaskManager_H_
#define _TaskManager_H_

#include <map>

#include "core.h"
#include "Runnable.h"
#include "Singleton.h"

typedef std::map<String, Runnable*> IdRunnableMap;


class TaskManager : public Singleton<TaskManager> {

    friend class Singleton<TaskManager>;

    private:
        TaskManager();

        Runnable *currentRunnable;
        IdRunnableMap appsById;
        IdRunnableMap uiById;

    public:

        void loop();
        void setRunnable(String id);
        void registerApp(String id, Runnable* runnable);
        void registerUI(String id, Runnable* runnable);
        void showUI(String id);

};

#endif