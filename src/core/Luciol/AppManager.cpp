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
    GraphicContext* gc = display->getContext();

    static Ambience *prevAmbience = NULL;
    static bool ambienceInverted = false;
    Ambience *amb = AmbienceManager::get()->getAmbience();
    bool ambienceChanged = prevAmbience != amb || ambienceInverted != amb->isInverted();
    ambienceInverted = amb->isInverted();

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
        if (ambienceChanged) {
            currentRunnable->ambienceDidChange(gc, amb);
            prevAmbience = amb;
        }
        if (hasJustStarted || currentRunnable->shouldRepaint()) {
            gc->clear();
            currentRunnable->doPaint(gc, amb);
        } else if (ambienceChanged) {
            gc->clear();
            currentRunnable->paint(gc, amb);
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