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

        if (input.length() > 0)
        {
            // Find comma separator
            int commaIndex = input.indexOf(',');
            
            if (commaIndex > 0 && commaIndex < input.length() - 1)
            {
                // Extract currentRPM and setpointRPM
                String currentStr = input.substring(0, commaIndex);
                String setpointStr = input.substring(commaIndex + 1);
                
                currentStr.trim();
                setpointStr.trim();
                
                float currentRPM = currentStr.toFloat();
                float setpointRPM = setpointStr.toFloat();
                
                // Validate ranges
                if (currentRPM >= -300 && currentRPM <= 300 && 
                    setpointRPM >= -300 && setpointRPM <= 300)
                {
                    _currentRPM = currentRPM;
                    _setpointRPM = setpointRPM;
                    
                    Serial.print("Updated -> Current RPM: ");
                    Serial.print(_currentRPM);
                    Serial.print(" | Setpoint RPM: ");
                    Serial.println(_setpointRPM);
                }
                else
                {
                    Serial.println("Invalid RPM values! Enter values between -100 and 100");
                    Serial.println("Example: 50,80");
                }
            }
            else
            {
                Serial.println("Invalid format! Use: currentRPM,setpointRPM");
                Serial.println("Example: 100,1500");
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