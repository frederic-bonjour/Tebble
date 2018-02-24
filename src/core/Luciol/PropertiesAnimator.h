#ifndef _PropertiesAnimator_H_
#define _PropertiesAnimator_H_

#include <Arduino.h>
#include <NeoPixelBus.h>


template <class T> class Property {
    T from;
    T to;
    uint16_t duration;

    public:
        Property(uint16_t d, T f, T t) {
            from = f;
            to = t;
            duration = d;
        }
};


class PropertiesAnimator {

    uint32_t startTime;

    public:

        PropertiesAnimator* add(String name, Property<int>* property);
        PropertiesAnimator* add(String name, Property<float>* property);
        PropertiesAnimator* add(String name, Property<RgbColor>* property);

        float getFloat(String name);
        int getInt(String name);
        RgbColor getColor(String name);

        void start();
};

#endif