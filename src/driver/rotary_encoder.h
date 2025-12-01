#pragma once

#include <stdint.h>
#include <stdbool.h>

class rotary_encoder
{
    public:
        bool begin();
        int32_t getPosition();
        void setPosition(int32_t position);
        void handle();
    private:
        int32_t _position = 0;
        int8_t _lastEncoded = 0;
        const int8_t _encoderPins[2] = {18, 19}; // Example pins, adjust as necessary
};