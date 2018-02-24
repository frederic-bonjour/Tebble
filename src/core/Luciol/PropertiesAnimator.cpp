#include "PropertiesAnimator.h"
#include <NeoPixelBus.h>


float PropertiesAnimator::getFloat(String name) {

}


int PropertiesAnimator::getInt(String name) {
    
}


RgbColor PropertiesAnimator::getColor(String name) {
    
}


PropertiesAnimator* PropertiesAnimator::add(String name, Property<int>* property) {

}


PropertiesAnimator* PropertiesAnimator::add(String name, Property<float>* property) {

}


PropertiesAnimator* PropertiesAnimator::add(String name, Property<RgbColor>* property) {

}


void PropertiesAnimator::start() {
    startTime = millis();
}