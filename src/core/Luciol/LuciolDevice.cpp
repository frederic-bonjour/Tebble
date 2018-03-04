#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FS.h>

#include "Settings.h"
#include "LuciolDevice.h"

#include "AmbienceManager.h"
#include "Clock.h"


void LuciolDevice::init() {
    connectWiFi();
    initDeviceIdentity();
    Clock::init();
    initMQTT();

    AmbienceManager::get()->load();
}


/**
 * Connects to the WiFi network.
 */
void LuciolDevice::connectWiFi() {
    // Connect to the WiFi
    WiFi.begin(Settings::WifiSSID.c_str(), Settings::WifiPassword.c_str());

    // Wait until the connection has been confirmed before continuing
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        #ifdef DEVELOPMENT
            Serial.print(".");
        #endif
    }

    ipAddress = WiFi.localIP();

    #ifdef DEVELOPMENT
        Serial.println();
        Serial.println("Connexion WiFi : OK");
        Serial.print  ("Addresse IP    : ");
        Serial.println(ipAddress);
    #endif
}


/**
 * Initializes the connection to the MQTT Broker.
 */
void LuciolDevice::initMQTT() {
    pubSubClient = new PubSubClient(Settings::MQTTBroker.c_str(), 1883, wifiClient);

    while (!connectMQTT()) {
        delay(500);
        Serial.print(".");
    }
}


/**
 * Connects to the MQTT Broker.
 */
bool LuciolDevice::connectMQTT() {
    if (pubSubClient->connect(DEVICE_TYPE + deviceId)) {
        pubSubClient->subscribe("B2D/all");
        pubSubClient->subscribe((String("B2D/N/") + deviceNumber).c_str());
        pubSubClient->subscribe((String("B2D/I/") + deviceId).c_str());
        // TODO pubSubClient->setCallback(ReceivedMessage);

        #ifdef DEVELOPMENT
            Serial.println("MQTT          : OK");
        #endif
        return true;
    }
    return false;
}


/**
 * Initializes the device's identity.
 */
void LuciolDevice::initDeviceIdentity() {
    // Device ID
    String ip = ipAddress.toString();
    int p = ip.lastIndexOf('.');
    deviceId = ip.substring(p + 1).toInt();
    #ifdef DEVELOPMENT
        Serial.print("Device ID      : "); Serial.println(deviceId);
    #endif

    // Device Number and Group
    SPIFFS.begin();
    File f = SPIFFS.open("/dev-id.txt", "r");
    if (!f) {
        #ifdef DEVELOPMENT
            Serial.println("Identification file NOT found.");
        #endif
        deviceNumber = 0;
        deviceName = "no-name";
    } else {
        #ifdef DEVELOPMENT
            Serial.println("Identification file found.");
        #endif
        String s = f.readStringUntil('\n');
        f.close();
        
        int p = s.indexOf(' ');
        deviceNumber = s.substring(0, p).toInt();
        deviceName = s.substring(p + 1);
    }
    #ifdef DEVELOPMENT
        Serial.print("Number         : "); Serial.println(deviceNumber);
        Serial.print("Name           : "); Serial.println(deviceName);
    #endif
}


/**
 * Saves device's identity to the filesystem.
 */
bool LuciolDevice::saveIdentity() {
    File f = SPIFFS.open("/dev-id.txt", "w");
    if (!f) {
        Serial.println("Unable to write identification file.");
        return false;
    }
    f.print(deviceNumber);
    f.print(' ');
    f.println(deviceName);
    f.close();

    Serial.printf("ID changed! number=%d, name=%s", deviceNumber, deviceName.c_str());
    Serial.println();

    return true;
}


bool LuciolDevice::setIdentity(uint8_t number, String name) {
    deviceNumber = number;
    deviceName = name;
    return saveIdentity();
}


void LuciolDevice::loop() {
    if (!pubSubClient->loop()) {
        connectMQTT();
    }
}