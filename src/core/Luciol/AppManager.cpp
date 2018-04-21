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
        transientStart = millis();
        transientEnd = transientStart + duration;
    } else {
        transientRunnable = NULL;
    }
}


void AppManager::loop() {
    GraphicContext* gc = display->getContext();

    if (transientRunnable && transientEnd > millis()) {

        //float transientProgress = (millis() - transientStart) / (transientEnd - transientStart);
        transientRunnable->loop();
        if (transientRunnable->shouldRepaint()) {
            transientRunnable->paint(gc);
        }

    } else {
        transientRunnable = NULL;

        if (previousRunnable != NULL) {
            previousRunnable->willStop();
            previousRunnable = NULL;
        }

        bool hasJustStarted = shouldWakeUpApp;
        if (currentRunnable != NULL) {
            if (shouldWakeUpApp) {
                currentRunnable->willStart(gc);
                shouldWakeUpApp = false;
            }
            currentRunnable->loop();
            if (hasJustStarted || currentRunnable->shouldRepaint()) {
                gc->clear();
                currentRunnable->doPaint(gc);
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