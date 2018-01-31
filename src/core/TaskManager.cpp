#include <Arduino.h>
#include "TaskManager.h"


TaskManager TaskManager::instance;


TaskManager::TaskManager() {
    currentRunnable = NULL;
}


void TaskManager::setRunnable(String id) {
    currentRunnable = appsById[id];
}


void TaskManager::loop() {
    if (currentRunnable != NULL) {
        currentRunnable->loop();
    }
}


void TaskManager::registerApp(String id, Runnable* runnable) {
    appsById[id] = runnable;
    if (appsById.size() == 1) {
        currentRunnable = runnable;
    }
}