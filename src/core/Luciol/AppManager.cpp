#include "AppManager.h"
#include "Display.h"


extern Display* display;


AppManager::AppManager() {
    currentRunnable = NULL;
}


void AppManager::setRunnable(String id) {
    previousRunnable = currentRunnable;
    currentRunnable = appsById[id];
    shouldWakeUpApp = true;
}


void AppManager::loop() {

    GraphicContext* gc = display->getContext();
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


void AppManager::registerApp(String id, Runnable* runnable) {
    appsById[id] = runnable;
    if (appsById.size() == 1) {
        currentRunnable = runnable;
        shouldWakeUpApp = true;
    }
}
