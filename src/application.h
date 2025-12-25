#pragma once

#include <Arduino.h>
#include "system/fuzzy_inference.h"
#include "driver/inverter_vfd.h"
#include "driver/rotary_encoder.h"
#include "driver/display_lcd.h"

class Application
{
public:
    Application();
    void init();
    void run();

private:
    FuzzyInference _fuzzyInference;
    rotary_encoder _rotaryEncoder;

    InverterVFD vfd;
    display_lcd lcd;

    float _setpointRPM = 50.0f;
    float _currentRPM = 0.0f;
    float _deltaError = 0.0f;
    float _freqAdjust = 0.0f;

    String lcdLabels[4] = {
        "CUR RPM",
        "SET RPM",
        "DEL ERR",
        "FREQ Hz"
    };

    float lcdValues[4];

    void updateFuzzyInputs();
    void processSerial();
};
