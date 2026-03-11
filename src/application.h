#pragma once

#include <Arduino.h>
#ifndef NO_FUZZY
#include "system/fuzzy_inference.h"
#endif
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
#ifndef NO_FUZZY
    FuzzyInference _fuzzyInference;
#endif
    rotary_encoder _rotaryEncoder;

    InverterVFD vfd;
    display_lcd lcd;

    float _setpointRPM = 50.0f;
    float _currentRPM  = 0.0f;
    float _deltaError  = 0.0f;
    float _freqAdjust  = 0.0f;
    float _voltageOut  = 0.0f;
    float _currentOut  = 0.0f;

    String screen1Labels[4] = {
        "CUR RPM",
        "SET RPM",
        "ERROR",
        "FREQ Hz"
    };
    float screen1Values[4];

    String screen2Labels[3] = {
        "OUT V",
        "OUT I",
        "ERROR"
    };
    float screen2Values[3];

    uint8_t currentScreen = 0;
    unsigned long lastScreenChange = 0;

    void updateLCD();
    void processSerial();
};
