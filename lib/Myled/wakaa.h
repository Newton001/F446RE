#ifndef MBED_WAKAA_H
#define MBED_WAKAA_H

#include <mbed.h>

class Wakaa {
public:
    Wakaa(PinName pin);
    void wakaa(int n);

private:
    DigitalOut _pin;    
};

#endif
