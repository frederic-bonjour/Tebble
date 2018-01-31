#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FS.h>

#include "core/core.h"
#include "core/Display.h"
#include "core/TaskManager.h"
#include "core/AmbienceManager.h"

#include "apps/Gradient/GradientApp.h"


WiFiClient wifiClient;
PubSubClient pubSubClient(Settings::MQTTBroker.c_str(), Settings::MQTTPort, wifiClient);


// ----------------------------------------------------------------------------
// Device identification
// ----------------------------------------------------------------------------


String clientID;
unsigned short deviceNumber;
String deviceName;


void initDeviceId(String ipAddress) {
    int p = ipAddress.lastIndexOf('.');
    clientID = ipAddress.substring(p + 1);
    Serial.print("Device ID      : "); Serial.println(clientID);
}


bool saveIdentity() {
  File f = SPIFFS.open("/dev-id.txt", "w");
  if (!f) {
    Serial.println("Impossible d'écrire le fichier d'identification.");
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


// ----------------------------------------------------------------------------
// MQTT
// ----------------------------------------------------------------------------


bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topics
  if (pubSubClient.connect(clientID.c_str())) {

    pubSubClient.subscribe("luciol/all");
    pubSubClient.subscribe((String("luciol/nb-") + deviceNumber).c_str());
    pubSubClient.subscribe((String("luciol/id-") + clientID).c_str());

    return true;
  } else {
    return false;
  }
}


void sendAliveMessage() {
  pubSubClient.publish("luciol/alive", (clientID + '@' + deviceNumber + ' ' + deviceName).c_str());
}


void receivedMessage(char* topic, byte* payload, unsigned int length) {
}


// ----------------------------------------------------------------------------
// Setup
// ----------------------------------------------------------------------------


void setup() {
    // Init Serial object.
    Serial.begin(115200);

    // Init LED display.
    Display::get().init();

    // Register apps in the TaskManager.
    TaskManager::get().registerApp("Gradient", new GradientApp);

    // Connect to WiFi
    Serial.print("Connecting to WiFi network ");
    Serial.println(Settings::WifiSSID);
    WiFi.begin(Settings::WifiSSID.c_str(), Settings::WifiPassword.c_str());

    // Wait until the connection has been confirmed before continuing
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Connect to MQTT Broker
    // setCallback sets the function to be called when a message is received.
    pubSubClient.setCallback(receivedMessage);

    Serial.print("Connecting to MQTT broker ");
    Serial.println(Settings::MQTTBroker);

    while (!mqttConnect()) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to MQTT broker.");

    sendAliveMessage();
    
    // Load ambiences.
    AmbienceManager::get().load();
}


void loop() {
    TaskManager::get().loop();
}