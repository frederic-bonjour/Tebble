#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FS.h>

#include "Settings.h"
#include "LuciolDevice.h"
#include "Display.h"
#include "GraphicContext.h"

#include "AmbienceManager.h"
#include "Clock.h"


#include "AmbienceManager.h"
AmbienceManager* _ambienceManager = AmbienceManager::get();


#include "AppManager.h"
AppManager*      _appManager      = AppManager::get();


void LuciolDevice::bootSequenceStep() {
    #ifdef DEVICE_TEBBLE
        gc->setPixel(5 + bootStep, gc->getCenterY(), RgbColor(255, 0, 0));
    #endif

    display->render();
}

void LuciolDevice::bootSequenceStepOK() {
    #ifdef DEVICE_TEBBLE
        gc->setPixel(5 + bootStep, gc->getCenterY(), RgbColor(0, 255, 0));
    #endif

    display->render();
    bootStep++;
}


void LuciolDevice::init(Display* d) {
    display = d;
    gc = display->getContext();
    gc->clear();
    display->render();

    bootSequenceStep();
    connectWiFi();
    bootSequenceStepOK();

    bootSequenceStep();
    do {
        initDeviceIdentity();
        if (!deviceId) {
            delay(5000);
        }
    } while (!deviceId);
    bootSequenceStepOK();

    bootSequenceStep();
    Clock::init();
    bootSequenceStepOK();

    bootSequenceStep();
    initMQTT();
    bootSequenceStepOK();

    bootSequenceStep();
    _ambienceManager->load();
    bootSequenceStepOK();

    bootSequenceStep();
    deviceStarted();
    bootSequenceStepOK();
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
        _appManager->getCurrentRunnable()->messageReceived(cmdData);
    }
}


String mac2String(byte ar[]){
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    sprintf(buf, "%2X", ar[i]);
    s += buf;
    if (i < 5) s += ':';
  }
  return s;
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
    
    byte mac[6];
    WiFi.macAddress(mac);
    macAddress = mac2String(mac);

    #ifdef DEBUG
        Serial.println();
        Serial.println("Connexion WiFi : OK");
        Serial.print  ("Addresse IP    : ");
        Serial.println(ipAddress);
        Serial.print  ("Addresse MAC   : ");
        Serial.println(macAddress);
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
        //pubSubClient->subscribe((String("B2D/N/") + deviceNumber).c_str());
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

    Serial.println("Requesting device ID...");
    WiFiClient client;
    if (!client.connect(Settings::BridgeHost, Settings::BridgePort)) {
        Serial.println("initDeviceIdentity: connection to Bridge failed.");
        Serial.println("Host: " + Settings::BridgeHost + ":" + Settings::BridgePort);
        return;
    }

    // This will send the request to the server
    client.print(String("GET /system/deviceRequestId/") + macAddress + "/" + DEVICE_TYPE + " HTTP/1.1\r\n" +
                "Host: " + Settings::BridgeHost + "\r\n" +
                "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > HTTP_TIMEOUT_MS) {
            Serial.println("initDeviceIdentity: client Timeout!");
            client.stop();
            return;
        }
    }

    String line;
    bool body = false;
    bool firstLine = true;
    while (client.available()) {
        line = client.readStringUntil('\n');
        line.trim();
        Serial.println(line);
        if (firstLine && !line.startsWith("HTTP/1.1 200")) {
            break;
        }
        firstLine = false;
        if (line.length() == 0) {
            body = true;
            continue;
        }
        if (body) {
            sscanf(line.c_str(), "%d %d", &deviceId, &deviceNumber);
            break;
        }
    }

    client.stop();

    #ifdef DEBUG
        Serial.print("Device ID      : "); Serial.println(deviceId);
        Serial.print("Device Group   : "); Serial.println(deviceNumber);
        //Serial.print("Name           : "); Serial.println(deviceName);
    #endif
}


/**
 * Tells the Bridge that this device is ready.
 */
void LuciolDevice::deviceStarted() {
    Serial.println("deviceStarted...");
    WiFiClient client;
    if (!client.connect(Settings::BridgeHost, Settings::BridgePort)) {
        Serial.println("deviceStarted: connection to Bridge failed.");
        Serial.println("Host: " + Settings::BridgeHost + ":" + Settings::BridgePort);
        return;
    }

    // This will send the request to the server
    client.print(String("GET /system/deviceStarted/") + deviceId + " HTTP/1.1\r\n" +
                "Host: " + Settings::BridgeHost + "\r\n" +
                "Connection: close\r\n\r\n");

    Serial.println("deviceStarted done.");
    client.stop();
}


/**
 * Saves device's identity to the filesystem.
 */
void LuciolDevice::setIdentity(int number) {
    deviceNumber = number;
}


void LuciolDevice::loop() {
    if (!pubSubClient->loop()) {
        connectMQTT();
    }
}