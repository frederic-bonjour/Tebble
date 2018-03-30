#ifndef _LuciolDevice_H_
#define _LuciolDevice_H_

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Display.h"
#include "GraphicContext.h"

#ifdef DEVICE_LUCIOL
    #define DEVICE_TYPE "luciol"
#endif
#ifdef DEVICE_TEBBLE
    #define DEVICE_TYPE "tebble"
#endif


class LuciolDevice {

    protected:

        IPAddress ipAddress;
        String    macAddress;

        int       deviceId = 0;
        int       deviceNumber = 0;

        uint8_t   bootStep = 0;

        WiFiClient wifiClient;
        PubSubClient* pubSubClient;
        Display* display;
        GraphicContext* gc;

        void connectWiFi();
        void initDeviceIdentity();
        void initMQTT();
        bool connectMQTT();
        void deviceStarted();
        void bootSequenceStep();
        void bootSequenceStepOK();

    public:

        void init(Display* display);
        void setIdentity(int number);
        void loop();
};


#endif