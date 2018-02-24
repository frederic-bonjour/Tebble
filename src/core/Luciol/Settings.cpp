#include "Settings.h"

#ifdef DEVELOPMENT

    String Settings::BridgeHost = "www.fruityfred.com";
    uint8_t Settings::BridgePort = 80;

    String Settings::WifiSSID = "BOUH";
    String Settings::WifiPassword = "yoshi8079";

    String Settings::MQTTBroker = "broker.hivemq.com";
    uint16_t Settings::MQTTPort = 1883;

#else

    String Settings::BridgeHost = "10.141.3.1"; // TODO Check
    uint8_t Settings::BridgePort = 80;

    String Settings::WifiSSID = "Luciol";
    String Settings::WifiPassword = "Luciol1234";

    String Settings::MQTTBroker = "10.141.3.1"; // TODO Check
    uint16_t Settings::MQTTPort = 1883;

#endif