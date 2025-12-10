#include "rotary_encoder.h"
#include <Arduino.h>
rotary_encoder *rotary_encoder::instance = nullptr;
bool rotary_encoder::begin()
{
    instance = this;
    pinMode(ENCODER_PINS, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PINS), rotary_encoder::isrRouter, RISING);
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
    Serial.println("Pulse detected");
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
    }
    else
    {
        _rpm = (60000000 / PULSES_PER_REVOLUTION) / _periodBetweenPulses;
    }

    return _rpm;
}