#include "PropertiesAnimator.h"
#include <NeoPixelBus.h>
#include <Arduino.h>


float PropertiesAnimator::getFloat(String name) {
    Property<float>* p = floatProperties[name];
    double percent = (millis() - startTime) / (double)p->duration;
    if (percent == 0.0) return p->from;
    if (percent >= 1.0) return p->to;
    float diff = p->to - p->from;
    return p->from + diff * percent;
}


int PropertiesAnimator::getInt(String name) {
    Property<int>* p = intProperties[name];
    double percent = (millis() - startTime) / (double)p->duration;
    if (percent == 0.0) return p->from;
    if (percent >= 1.0) return p->to;
    int diff = p->to - p->from;
    return p->from + round(diff * percent);
}


RgbColor PropertiesAnimator::getColor(String name) {
    Property<RgbColor>* p = colorProperties[name];
    double percent = (millis() - startTime) / (double)p->duration;
    if (percent == 0.0) return p->from;
    if (percent >= 1.0) return p->to;
    return RgbColor::LinearBlend(p->from, p->to, percent);
}


PropertiesAnimator* PropertiesAnimator::add(String name, Property<int>* property) {
    if (property->duration > duration) {
        duration = property->duration;
    }
    intProperties[name] = property;
}


PropertiesAnimator* PropertiesAnimator::add(String name, Property<float>* property) {
    if (property->duration > duration) {
        duration = property->duration;
    }
    floatProperties[name] = property;
}


PropertiesAnimator* PropertiesAnimator::add(String name, Property<RgbColor>* property) {
    if (property->duration > duration) {
        duration = property->duration;
    }
    colorProperties[name] = property;
}


void PropertiesAnimator::start() {
    startTime = millis();
}


bool PropertiesAnimator::isComplete() {
    return (millis() - startTime) >= duration;
}