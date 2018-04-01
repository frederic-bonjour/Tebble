#include "AppManager.h"
#include "Display.h"


extern Display* display;


AppManager::AppManager() {
    currentRunnable = NULL;
}


bool AppManager::setRunnable(String id) {
    std::map<String, Runnable*>::iterator iter = appsById.find(id);
    if (iter != appsById.end()) {
        previousRunnable = currentRunnable;
        currentRunnableId = id;
        currentRunnable = appsById[id];
        shouldWakeUpApp = true;
        return true;
    }

    Serial.print("Unknown app: ");
    Serial.println(id);
    return false;
}


void AppManager::setTransientRunnable(String id, unsigned long duration) {
    std::map<String, Runnable*>::iterator iter = appsById.find(id);
    if (iter != appsById.end()) {
        transientRunnable = appsById[id];
        transientEnd = millis() + duration;
    } else {
        transientRunnable = NULL;
    }
}


void AppManager::loop() {
    GraphicContext* gc = display->getContext();

    static Ambience *prevAmbience = NULL;
    static bool ambienceInverted = false;
    Ambience *amb = AmbienceManager::get()->getAmbience();
    bool ambienceChanged = prevAmbience != amb || ambienceInverted != amb->isInverted();
    ambienceInverted = amb->isInverted();

    if (transientRunnable && transientEnd > millis()) {

        transientRunnable->loop();
        transientRunnable->paint(gc, amb);

    } else {
        transientRunnable = NULL;

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