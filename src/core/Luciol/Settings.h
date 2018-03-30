#ifndef _Settings_H_
#define _Settings_H_

#include <Arduino.h>


class Settings {
    public:
        static String BridgeHost;
        static uint16_t BridgePort;

        static String WifiSSID;
        static String WifiPassword;

        static String MQTTBroker;
        static uint16_t MQTTPort;
        static String MQTTUsername;
        static String MQTTPassword;

        static String NTPServer;

        static String AmbiencesURL;
};

#endif