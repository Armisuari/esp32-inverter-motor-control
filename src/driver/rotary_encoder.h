#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#define ENCODER_PIN_A 2          // Channel A - Use interrupt-capable pins
#define ENCODER_PIN_B 4          // Channel B - Use interrupt-capable pins
#define PULSES_PER_REVOLUTION 1050 // Calibrated value
#define SAMPLE_TIME_MS 100       // 100ms sampling window
#define MOVING_AVG_SIZE 5        // Moving average buffer size
#define OVERSPEED_LIMIT 2600     // Motor protection threshold (max ~2700 RPM)

class rotary_encoder
{
public:
    bool begin();
    float getRPM();           // Returns raw RPM
    float getFilteredRPM();   // Returns smoothed RPM
    int8_t getDirection();    // Returns 1 for forward, -1 for reverse, 0 for stopped
    bool isOverspeed() const; // Returns true if RPM exceeds limit

private:
    static void IRAM_ATTR isrRouter();
    void IRAM_ATTR handlePulse();
    
    float updateMovingAverage(float newValue);

    // Pulse counting
    volatile long _pulseCount = 0;
    long _lastPulseCount = 0;
    int8_t _direction = 0; // 1 = forward, -1 = reverse, 0 = stopped

    // Sampling window
    unsigned long _lastSampleTime = 0;
    
    // RPM values
    float _rpm = 0;           // Raw RPM from current window
    float _rpmFiltered = 0;   // Smoothed RPM (moving average)
    
    // Moving average buffer
    float _rpmBuffer[MOVING_AVG_SIZE];
    int _bufferIndex = 0;

    static rotary_encoder *instance; // For ISR routing
};