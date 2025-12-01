#include <Arduino.h>

#include "application.h"

Application app;

void setup() {
  // put your setup code here, to run once:
  app.init();
}

void loop() {
  // put your main code here, to run repeatedly:

  static uint64_t lastRun = 0;
  if (millis() - lastRun < 10) {
    lastRun = millis();
    app.run();
  }
  
}