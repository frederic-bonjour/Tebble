#include "AppManager.h"
#include "Display.h"


extern Display* display;


AppManager::AppManager() {
    currentRunnable = NULL;
}


void AppManager::setRunnable(String id) {
    previousRunnable = currentRunnable;
    currentRunnableId = id;
    currentRunnable = appsById[id];
    shouldWakeUpApp = true;
}


void AppManager::loop() {
    static Ambience *prevAmbience = NULL;
    GraphicContext* gc = display->getContext();
    Ambience *amb = AmbienceManager::get()->getAmbience();

    if (previousRunnable != NULL) {
        previousRunnable->willStop();
        previousRunnable = NULL;
    }

    bool hasJustStarted = shouldWakeUpApp;
    if (currentRunnable != NULL) {
        if (shouldWakeUpApp) {
            currentRunnable->willStart(gc, amb);
            shouldWakeUpApp = false;
        }
        currentRunnable->loop();
        if (hasJustStarted || currentRunnable->shouldRepaint()) {
            if (prevAmbience != amb) {
                currentRunnable->ambienceDidChange(gc, amb);
                prevAmbience = amb;
            }
            gc->clear();
            currentRunnable->doPaint(gc, amb);
        }
    }
}


void AppManager::registerApp(String id, Runnable* runnable) {
    appsById[id] = runnable;
    if (appsById.size() == 1) {
        currentRunnable = runnable;
        currentRunnableId = id;
        shouldWakeUpApp = true;
    }
}


String AppManager::getCurrentRunnableId() {
    return currentRunnableId;
}


Runnable* AppManager::getCurrentRunnable() {
    return currentRunnable;
}