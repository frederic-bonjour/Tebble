#include <Arduino.h>
#include "TaskManager.h"
#include "Display.h"
#include "AmbienceManager.h"


TaskManager::TaskManager() {
    currentRunnable = NULL;
}


void TaskManager::setRunnable(String id) {
    currentRunnable = appsById[id];
}


void TaskManager::loop() {
    if (currentRunnable != NULL) {
        currentRunnable->loop(Display::get().getContext(), AmbienceManager::get().getAmbience());
    }
}


void TaskManager::registerApp(String id, Runnable* runnable) {
    appsById[id] = runnable;
    if (appsById.size() == 1) {
        currentRunnable = runnable;
    }
}


void TaskManager::registerUI(String id, Runnable* runnable) {
    uiById[id] = runnable;
}


void TaskManager::showUI(String id) {
    currentRunnable = uiById[id];
}