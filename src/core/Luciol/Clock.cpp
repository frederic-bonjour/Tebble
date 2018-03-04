#include "Clock.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "Settings.h"


WiFiUDP ntpUDP;
 
int16_t utc = 1; //UTC -3:00 Brazil
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
 
NTPClient timeClient(ntpUDP, Settings::NTPServer.c_str(), utc*3600, 60000);


void Clock::init() {
    timeClient.begin();
    sync();
}


void Clock::sync() {
    timeClient.update();
}


int Clock::getHours() {
    return timeClient.getHours();
}


int Clock::getMinutes() {
    return timeClient.getMinutes();
}


int Clock::getSeconds() {
    return timeClient.getSeconds();
}