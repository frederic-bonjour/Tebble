#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "AmbienceManager.h"
#include "Settings.h"


AmbienceManager::AmbienceManager() {
    currentAmbience = NULL;
}


void AmbienceManager::load() {
    // Free memory of previously loaded ambiences.
    AmbiencesById::iterator itr;
    for (itr = ambiencesById.begin(); itr != ambiencesById.end(); ++itr) {
        delete itr->second;
    }

    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(Settings::BridgeHost, Settings::BridgePort)) {
        Serial.println("connection failed");
        return;
    }

    Serial.print("Requesting URL: ");
    Serial.println(AMBIENCE_LOAD_URL);

    // This will send the request to the server
    client.print(String("GET ") + AMBIENCE_LOAD_URL + " HTTP/1.1\r\n" +
                "Host: " + Settings::BridgeHost + "\r\n" +
                "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > HTTP_TIMEOUT_MS) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
        }
    }

    String line;
    bool body = false;
    uint8_t ambienceCount = 0;
    while (client.available()) {
        line = client.readStringUntil('\r');
        line.trim();
        if (line.length() == 0) {
            body = true;
            continue;
        }
        if (body) {
            registerAmbience(String(ambienceCount), Ambience::createFromString(line));
            ambienceCount++;
        }
    }

    Serial.printf("Loaded ambiences: %d\r\n", ambiencesById.size());
}


void AmbienceManager::registerAmbience(String id, Ambience* ambience) {
    ambiencesById[id] = ambience;
    if (ambiencesById.size() == 1) {
        currentAmbience = ambience;
        Serial.println(currentAmbience->getName());
    }
}


Ambience* AmbienceManager::getAmbience() {
    return currentAmbience;
}


void AmbienceManager::setAmbience(String id) {
    AmbiencesById::iterator iter = ambiencesById.find(id);
    if (iter != ambiencesById.end()) {
        currentAmbience = ambiencesById[id];
    }
}


unsigned int AmbienceManager::count() {
    return ambiencesById.size();
}