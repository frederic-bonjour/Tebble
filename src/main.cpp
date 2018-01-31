#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FS.h>

#include "core/core.h"
#include "core/Display.h"
#include "core/TaskManager.h"
#include "core/AmbienceManager.h"

#include "apps/UI/UIProgress.h"

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
  clientID = String("Tebble-") + ipAddress.substring(p + 1);
  Serial.print("Device ID: "); Serial.println(clientID);
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
  Serial.begin(9600);
  while (!Serial);


  // Init LED display.
  Display::get().init();


  // Init TaskManager.
  TaskManager &tm = TaskManager::get();


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


  // Device identification
  SPIFFS.begin();
  File f = SPIFFS.open("/dev-id.txt", "r");
  if (!f) {
    Serial.println("No ID file found.");
    deviceNumber = 0;
    deviceName = "Tebble";
  } else {
    String s = f.readStringUntil('\n');
    char devname[50];
    sscanf(s.c_str(), "%d %s", &deviceNumber, devname);
    deviceName = String(devname);
    f.close();
  }
  Serial.print("Device name: "); Serial.println(deviceName);
  Serial.print("Device group: "); Serial.println(deviceNumber);
  initDeviceId(WiFi.localIP().toString());


  // Register apps in the TaskManager.
  tm.registerApp("Gradient", new GradientApp);

/*
  // Connect to MQTT Broker
  // setCallback sets the function to be called when a message is received.
  pubSubClient.setCallback(receivedMessage);
  Serial.print("Connecting to MQTT broker ");
  Serial.println(Settings::MQTTBroker);

  while (!mqttConnect()) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("Connected to MQTT broker.");

  sendAliveMessage();
*/
  // Load ambiences.
  AmbienceManager::get().load();

  Serial.println("Tebble is ready.");
}

unsigned long int t = 0;
unsigned int ambience = 0;

void loop() {
  TaskManager::get().loop();
  Display::get().render();

  if (millis() - t > 5000) {
    t = millis();
    ambience++;
    if (ambience >= AmbienceManager::get().count()) {
      ambience = 0;
    }
    AmbienceManager::get().setAmbience(String(ambience));
  }
}