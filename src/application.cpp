#include "application.h"
#include <Arduino.h>

Application::Application()
{
}

void Application::init()
{
    Serial.begin(115200);
    Serial.println("\nMotor Control System Started");
    Serial.println("Enter setpoint RPM (e.g., 1500):");
    
    _rotaryEncoder.begin();
    _fuzzyInference.setup();
}

void Application::run()
{
    processSerial();
    // float currentRPM = _rotaryEncoder.getRPM();
    _fuzzyInference.setInput(1, _currentRPM);
    float deltaError = _setpointRPM - _currentRPM;
    _fuzzyInference.setInput(2, deltaError); // delta error
    _fuzzyInference.fuzzify();

    float frequencyAdjustment = _fuzzyInference.defuzzify(1);
    Serial.print("Current RPM: ");
    Serial.print(_currentRPM);
    Serial.print(" | Setpoint RPM: ");
    Serial.print(_setpointRPM);
    Serial.print(" | Delta Error: ");
    Serial.print(deltaError);
    Serial.print(" | Frequency Adjustment: ");
    Serial.print(frequencyAdjustment);
    Serial.println();
}

void Application::processSerial()
{
    if (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');
        input.trim();
        
        if (input.length() > 0)
        {
            float newRPM = input.toFloat();
            
            if (newRPM >= 0 && newRPM <= 10000)
            {
                _currentRPM = newRPM;
                Serial.print("RPM updated to: ");
                Serial.print(_currentRPM);
                Serial.println(" RPM");
            }
            else
            {
                Serial.println("Invalid RPM! Enter value between 0-10000 RPM");
            }
        }
    }
}