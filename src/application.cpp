#include "application.h"
#include <Arduino.h>

Application::Application()
  : vfd(Serial2, 9600),
    lcd(0x27, 20, 4)
{
}

void Application::init()
{
    Serial.begin(115200);

    lcd.begin();
    lcd.printCenter(1, "Motor Control");
    lcd.printCenter(2, "System Start");
    delay(1500);
    lcd.clear();

    lcd.setData(lcdLabels, lcdValues, 4, 1);

    _rotaryEncoder.begin();
    _fuzzyInference.setup();

    vfd.begin(1);
    vfd.start();
}


void Application::run()
{
    processSerial();

    _deltaError = _setpointRPM - _currentRPM;

    _fuzzyInference.setInput(1, _currentRPM);
    _fuzzyInference.setInput(2, _deltaError);
    _fuzzyInference.fuzzify();

    _freqAdjust = _fuzzyInference.defuzzify(1);
    vfd.setSpeedHz(_freqAdjust);

    // Update LCD values
    lcdValues[0] = _currentRPM;
    lcdValues[1] = _setpointRPM;
    lcdValues[2] = _deltaError;
    lcdValues[3] = _freqAdjust;

    lcd.update();

    Serial.print("CUR: "); Serial.print(_currentRPM);
    Serial.print(" | SET: "); Serial.print(_setpointRPM);
    Serial.print(" | ERR: "); Serial.print(_deltaError);
    Serial.print(" | FREQ: "); Serial.println(_freqAdjust);
}


void Application::processSerial()
{
    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        input.trim();

        float newRPM = input.toFloat();
        if (newRPM >= 0 && newRPM <= 10000)
        {
            _setpointRPM = newRPM;
            Serial.print("Setpoint updated: ");
            Serial.println(_setpointRPM);
        }
        else
        {
            Serial.println("RPM invalid (0–10000)");
        }
    }
}
