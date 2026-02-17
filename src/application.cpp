#include "application.h"
#include <Arduino.h>

// #define SIMULATION_TESTING 1

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

    lcd.setData(screen1Labels, screen1Values, 4, 1);

    _rotaryEncoder.begin();
    _fuzzyInference.setup();

    vfd.begin(1);
    vfd.start();
}

void Application::updateLCD()
{
    if (millis() - lastScreenChange > 3000)
    {
        lastScreenChange = millis();
        currentScreen ^= 1;

        lcd.clear();
        if (currentScreen == 0)
        {
            lcd.setData(screen1Labels, screen1Values, 4, 1);
        }
        else
        {
            lcd.setData(screen2Labels, screen2Values, 2, 2);
        }
    }

    lcd.update();
}

void Application::run()
{
// #if SIMULATION_TESTING == 0
    _currentRPM = _rotaryEncoder.getRPM();
    // Serial.println("Current Encoder RPM: " + String(_currentRPM));
// #else
    // Simulation Mode: Increment current RPM towards setpoint RPM
    processSerial();
// #endif

    int phaseErrCode = vfd.checkPhaseError();

    if (phaseErrCode > 0)
    {
        Serial.print("!!! ALERT: ");
        Serial.println(vfd.getPhaseErrorString(phaseErrCode));
        screen2Values[2] = vfd.checkPhaseError();
    }

    else if (phaseErrCode == -1)
    {
        Serial.println("Warning: Cannot read from VFD (Comm Error)");
    }

    _deltaError = _setpointRPM - _currentRPM;

    _fuzzyInference.setInput(1, _currentRPM);
    _fuzzyInference.setInput(2, _deltaError);
    _fuzzyInference.fuzzify();

    _freqAdjust = _fuzzyInference.defuzzify(1);
    vfd.setSpeedHz(_freqAdjust);

    screen1Values[0] = _currentRPM;
    screen1Values[1] = _setpointRPM;
    screen1Values[2] = _deltaError;
    screen1Values[3] = _freqAdjust;

    if (vfd.readOutputVoltage(_voltageOut))
    {
        screen2Values[0] = _voltageOut;
    }

    if (vfd.readOutputCurrent(_currentOut))
    {
        screen2Values[1] = _currentOut;
    }

    updateLCD();

    Serial.print("sp:");
    Serial.print(_setpointRPM);
    Serial.print("\t");
    Serial.print("rpm:");
    Serial.print(_currentRPM);
    // Serial.print("\t");
    // Serial.print("delta error:");
    // Serial.print(_deltaError);
    Serial.print("\t");
    Serial.print("freq:");
    Serial.println(_freqAdjust);
}

void Application::processSerial()
{
    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() > 0)
        {
            // Parse command format: "curr <value>" or "setp <value>"
            int spaceIndex = input.indexOf(' ');

            if (spaceIndex > 0 && spaceIndex < input.length() - 1)
            {
                String command = input.substring(0, spaceIndex);
                String valueStr = input.substring(spaceIndex + 1);
                command.trim();
                valueStr.trim();

                float value = valueStr.toFloat();

                // Validate range
                if (value >= -300 && value <= 300)
                {
                    // if (command == "curr" || command == "current")
                    // {
                    //     _currentRPM = value;
                    //     Serial.print("Updated -> Current RPM: ");
                    //     Serial.println(_currentRPM);
                    // }
                    // else 
                    if (command == "setp" || command == "setpoint")
                    {
                        _setpointRPM = value;
                        Serial.print("Updated -> Setpoint RPM: ");
                        Serial.println(_setpointRPM);
                    }
                    else
                    {
                        Serial.println("Invalid command! Use 'curr' or 'setp'");
                        Serial.println("Examples: curr 100 | setp 250");
                    }
                }
                else
                {
                    Serial.println("Invalid RPM value! Enter values between -300 and 300");
                }
            }
            else
            {
                Serial.println("Invalid format! Use: curr <value> or setp <value>");
                Serial.println("Examples: curr 100 | setp 250");
            }
        }
    }
}

// Fuzzy Simulation Test Cases:
// 1. 0,100 → Δ=+100 → expect high increase (freq ~50–60 Hz)            - Fail (Actual: ~45 Hz)
// 2. 100,0 → Δ=−100 → expect strong decrease (freq ~0–15 Hz)           - Fail (Actual: ~30 Hz)
// 3. 150,200 → Δ=+50 → expect moderate increase (freq ~45–55 Hz)       - Pass (Actual: ~45 Hz)
// 4. 200,150 → Δ=−50 → expect moderate decrease (freq ~15–25 Hz)       - Fail (Actual: ~35.49 Hz)
// 5. 150,150 → Δ=0 → expect no change (freq ~30–45 Hz)                 - Pass (Actual: ~43.75 Hz)
// 6. 100,105 → Δ=+5 → near-stable (freq ~30–45 Hz)                     - Pass (Actual: ~45 Hz)
// 7. -100,0 → Δ=+100 → increase (freq ~50–60 Hz)                       - Fail (Actual: ~30 Hz)
// 8. -150,-100 → Δ=+50 → small increase (freq ~45–55 Hz)               - Fail (Actual: ~30 Hz)
// 9. 50,130 → Δ=+80 → stronger increase (freq ~50–60 Hz)               - Fail (Actual: ~47.89 Hz)
// 10. 130,50 → Δ=−80 → stronger decrease (freq ~10–20 Hz)              - Fail (Actual: ~30 Hz)
// 11. 0,-80 → Δ=−80 → decrease (freq ~10–20 Hz)                        - Pass (Actual: ~15 Hz)
// 12. 25,75 → Δ=+50 → moderate increase (freq ~45–55 Hz)               - Pass (Actual: ~45 Hz)