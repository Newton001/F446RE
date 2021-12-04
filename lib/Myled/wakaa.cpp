#include <mbed.h>
#include <wakaa.h>

Wakaa::Wakaa(PinName pin) : _pin(pin) {
    _pin = 0;
}
void Wakaa::wakaa(int n) {
    for (int i=0; i<n*2; i++) {
        _pin = !_pin;
        wait_us(200000);
    }
}



