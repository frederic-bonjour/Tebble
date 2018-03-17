#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FS.h>

#include "Settings.h"
#include "LuciolDevice.h"

#include "AmbienceManager.h"
#include "Clock.h"


#include "AmbienceManager.h"
AmbienceManager* _ambienceManager = AmbienceManager::get();


#include "AppManager.h"
AppManager*      _appManager      = AppManager::get();


void LuciolDevice::init() {
    connectWiFi();
    initDeviceIdentity();
    Clock::init();
    initMQTT();

    _ambienceManager->load();
}


void mqttMessageReceived(char* topic, byte* payload, unsigned int length) {
    String msg = "";
    for (uint16_t i=0; i<length; i++) {
        msg += (char)payload[i];
    }
    int p = msg.indexOf(' ');
    String cmd = msg.substring(0, p);
    String cmdData = msg.substring(p + 1);

    Serial.print("Message received: "); Serial.println(cmd);
    Serial.print("Topic: "); Serial.println(topic);

    if (cmd == "app") {
        _appManager->setRunnable(cmdData);
    } else if (cmd == "ambience") {
        _ambienceManager->setAmbience(cmdData);
    } else if (cmd == "resume") {
        
    } else if (cmd == "locate") {
        
    } else if (cmd == _appManager->getCurrentRunnableId()) {
        _appManager->getCurrentRunnable()->handleMessage(cmdData);
    }
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
        #ifdef DEBUG
            Serial.print(".");
        #endif
    }

    ipAddress = WiFi.localIP();

    #ifdef DEBUG
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
        pubSubClient->setCallback(mqttMessageReceived);

        #ifdef DEBUG
            Serial.println("MQTT           : OK");
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
    #ifdef DEBUG
        Serial.print("Device ID      : "); Serial.println(deviceId);
    #endif

    // Device Number and Group
    SPIFFS.begin();
    File f = SPIFFS.open("/dev-id.txt", "r");
    if (!f) {
        #ifdef DEBUG
            Serial.println("Identification file NOT found.");
        #endif
        deviceNumber = 0;
        deviceName = "no-name";
    } else {
        #ifdef DEBUG
            Serial.println("Identification file found.");
        #endif
        String s = f.readStringUntil('\n');
        f.close();
        
        int p = s.indexOf(' ');
        deviceNumber = s.substring(0, p).toInt();
        deviceName = s.substring(p + 1);
    }
    #ifdef DEBUG
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