#include "rotary_encoder.h"
#include <Arduino.h>
rotary_encoder *rotary_encoder::instance = nullptr;
bool rotary_encoder::begin()
{
    instance = this;
    pinMode(ENCODER_PIN_A, INPUT);
    pinMode(ENCODER_PIN_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), rotary_encoder::isrRouter, RISING);
    return true;
}

void rotary_encoder::isrRouter()
{
    if (instance)
    {
        instance->handlePulse();
    }
}

void rotary_encoder::handlePulse()
{
    // Read channel B to determine direction
    // When A rises: if B is LOW, rotating forward; if B is HIGH, rotating reverse
    bool channelB = digitalRead(ENCODER_PIN_B);
    
    if (channelB == LOW)
    {
        _pulseCount++; // Forward rotation
        _direction = 1;
    }
    else
    {
        _pulseCount--; // Reverse rotation
        _direction = -1;
    }
    
    // Measure timing for RPM calculation
    if (_measureDone)
    {
        _currentTime = micros();
        _periodBetweenPulses = _currentTime - _lastPulseTime;
        _measureDone = false;
    }
    else
    {
        _lastPulseTime = micros();
        _measureDone = true;
    }
}

float rotary_encoder::getRPM()
{
    // Check if encoder has stopped (no pulses within timeout period)
    unsigned long timeSinceLastPulse = micros() - _lastPulseTime;

    if (timeSinceLastPulse > TIMEOUT || _periodBetweenPulses == 0)
    {
        _rpm = 0;
        _direction = 0;
    }
    else
    {
        // Calculate RPM and apply direction
        _rpm = ((60000000.0 / PULSES_PER_REVOLUTION) / _periodBetweenPulses) * _direction;
    }

    return _rpm;
}

int8_t rotary_encoder::getDirection()
{
    // Check if encoder has stopped
    unsigned long timeSinceLastPulse = micros() - _lastPulseTime;
    
    if (timeSinceLastPulse > TIMEOUT)
    {
        _direction = 0;
    }
    
    return _direction;
}