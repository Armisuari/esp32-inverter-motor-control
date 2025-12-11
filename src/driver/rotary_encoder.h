#pragma once

#include <stdint.h>
#include <stdbool.h>

#define ENCODER_PIN_A 2          // Channel A - Use interrupt-capable pins
#define ENCODER_PIN_B 4          // Channel B - Use interrupt-capable pins
#define PULSES_PER_REVOLUTION 600 // Set how many pulses there are on each revolution.
#define TIMEOUT 100000           // Timeout in microseconds to consider the encoder stopped.

class rotary_encoder
{
public:
    bool begin();
    float getRPM();
    int8_t getDirection(); // Returns 1 for forward, -1 for reverse, 0 for stopped

private:
    static void isrRouter();
    void handlePulse();
    float _rpm = 0;
    int8_t _direction = 0; // 1 = forward, -1 = reverse, 0 = stopped

    bool _measureDone = false;
    static rotary_encoder *instance; // For ISR routing

    volatile unsigned long _lastPulseTime = 0;
    volatile unsigned long _currentTime = 0;
    volatile unsigned long _periodBetweenPulses = 1;
    volatile int32_t _pulseCount = 0; // Track encoder position
};