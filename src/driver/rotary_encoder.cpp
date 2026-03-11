#include "rotary_encoder.h"
#include <Arduino.h>
#include <cmath>

rotary_encoder *rotary_encoder::instance = nullptr;

bool rotary_encoder::begin()
{
    instance = this;
    
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    
    // Initialize moving average buffer
    for (int i = 0; i < MOVING_AVG_SIZE; i++) {
        _rpmBuffer[i] = 0;
    }
    
    _lastSampleTime = millis();
    _lastPulseCount = 0;
    _bufferIndex = 0;
    
    // Attach interrupt on channel A (RISING edge)
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), rotary_encoder::isrRouter, RISING);
    
    return true;
}

void IRAM_ATTR rotary_encoder::isrRouter()
{
    if (instance) {
        instance->handlePulse();
    }
}

void IRAM_ATTR rotary_encoder::handlePulse()
{
    // Read channel B to determine direction
    // When A rises: if B is LOW, forward; if B is HIGH, reverse
    if (digitalRead(ENCODER_PIN_B)) {
        _pulseCount++; // Forward
    } else {
        _pulseCount--; // Reverse
    }
}

float rotary_encoder::updateMovingAverage(float newValue)
{
    _rpmBuffer[_bufferIndex] = newValue;
    _bufferIndex++;
    
    if (_bufferIndex >= MOVING_AVG_SIZE) {
        _bufferIndex = 0;
    }
    
    float sum = 0;
    for (int i = 0; i < MOVING_AVG_SIZE; i++) {
        sum += _rpmBuffer[i];
    }
    
    return sum / MOVING_AVG_SIZE;
}

float rotary_encoder::getRPM()
{
    // Sample every SAMPLE_TIME_MS
    unsigned long currentTime = millis();
    
    if (currentTime - _lastSampleTime >= SAMPLE_TIME_MS) {
        // Get pulse count snapshot
        long currentPulse = _pulseCount;
        long deltaPulse = currentPulse - _lastPulseCount;
        
        _lastPulseCount = currentPulse;
        _lastSampleTime = currentTime;
        
        // Calculate RPM from pulse window (600.0 = 60sec * 10 for 100ms)
        _rpm = (deltaPulse * 60.0) / PULSES_PER_REVOLUTION;
        
        // Determine direction from sign
        if (_rpm > 0) {
            _direction = 1;
        } else if (_rpm < 0) {
            _direction = -1;
        } else {
            _direction = 0;
        }
        
        // Use absolute value for magnitude
        _rpm = abs(_rpm);
        
        // Apply moving average filter
        _rpmFiltered = updateMovingAverage(_rpm);
    }
    
    return _rpm;
}

float rotary_encoder::getFilteredRPM()
{
    // Ensure getRPM() has been called at least once
    getRPM();
    return _rpmFiltered;
}

int8_t rotary_encoder::getDirection()
{
    return _direction;
}

bool rotary_encoder::isOverspeed() const
{
    return _rpmFiltered > OVERSPEED_LIMIT;
}