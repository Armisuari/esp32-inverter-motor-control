#pragma once

#include "system/fuzzy_inference.h"
#include "driver/rotary_encoder.h"

class Application
{
    public:
        Application();
        void init();
        void run();
        
    private:
        FuzzyInference _fuzzyInference;
        rotary_encoder _rotaryEncoder;

        void updateFuzzyInputs();
};