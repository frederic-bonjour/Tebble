#include <Arduino.h>
#include "TaskManager.h"
#include "Display.h"
#include "AmbienceManager.h"


TaskManager::TaskManager() {
    currentRunnable = NULL;
}


void TaskManager::setRunnable(String id) {
    previousRunnable = currentRunnable;
    currentRunnable = appsById[id];
    shouldWakeUpApp = true;
}


void TaskManager::loop() {

    GraphicContext* gc = Display::get()->getContext();
    Ambience *amb = AmbienceManager::get()->getAmbience();

    if (previousRunnable != NULL) {
        previousRunnable->sleep();
        previousRunnable = NULL;
    }

    if (currentRunnable != NULL) {
        if (shouldWakeUpApp) {
            currentRunnable->wakeUp(gc, amb);
            shouldWakeUpApp = false;
        }
        currentRunnable->loop(gc, amb);
    }
}


void TaskManager::registerApp(String id, Runnable* runnable) {
    appsById[id] = runnable;
    if (appsById.size() == 1) {
        currentRunnable = runnable;
        shouldWakeUpApp = true;
    }
}


void TaskManager::registerUI(String id, Runnable* runnable) {
    uiById[id] = runnable;
}


void TaskManager::showUI(String id) {
    currentRunnable = uiById[id];
}