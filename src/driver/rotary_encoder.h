#pragma once

#include <stdint.h>
#include <stdbool.h>

#define ENCODER_PINS 2          // Use interrupt-capable pins
#define PULSES_PER_REVOLUTION 2 // Set how many pulses there are on each revolution.
#define TIMEOUT 100000           // Timeout in microseconds to consider the encoder stopped.

class rotary_encoder
{
public:
    bool begin();
    float getRPM();

private:
    static void isrRouter();
    void handlePulse();
    int16_t _rpm = 0;

    bool _measureDone = false;
    static rotary_encoder *instance; // For ISR routing

    volatile unsigned long _lastPulseTime = 0;
    volatile unsigned long _currentTime = 0;
    volatile unsigned long _periodBetweenPulses = 1;
};