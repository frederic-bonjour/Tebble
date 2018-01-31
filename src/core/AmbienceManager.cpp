#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "AmbienceManager.h"
#include "core.h"


AmbienceManager AmbienceManager::instance;


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
    while (client.available()) {
        line = client.readStringUntil('\r');
        line.trim();
        if (line.length() == 0) {
        body = true;
        continue;
        }
        if (body) {
        //ambiencesById[ambienceCount] = Ambience::createFromString(line);
        }
    }

  //Serial.printf("Loaded ambiences: %d\r\n", ambiencesById.size());
}


void AmbienceManager::registerAmbience(String id, Ambience* ambience) {
    ambiencesById[id] = ambience;
    if (ambiencesById.size() == 1) {
        currentAmbience = ambience;
    }
}