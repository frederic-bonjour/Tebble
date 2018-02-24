#ifndef _LuciolDevice_H_
#define _LuciolDevice_H_

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DEVICE_TYPE "Luciol"


class LuciolDevice {

    protected:

        IPAddress ipAddress;
        uint8_t deviceId;
        uint8_t deviceNumber;
        String  deviceName;

        WiFiClient wifiClient;
        PubSubClient* pubSubClient;

        void connectWiFi();
        void initDeviceIdentity();
        void initMQTT();
        bool connectMQTT();

        bool saveIdentity();

    public:

        void init();
        bool setIdentity(uint8_t number, String name);
        void loop();
};


#endif