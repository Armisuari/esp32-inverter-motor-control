#include <Arduino.h>

#include "application.h"

Application app;
static uint64_t lastRun = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  app.init();
  Serial.println("Running application...");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (millis() - lastRun > 1000) {
    lastRun = millis();
    app.run();
  }
  
}