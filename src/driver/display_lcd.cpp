#include "display_lcd.h"

display_lcd::display_lcd(uint8_t addr, uint8_t c, uint8_t r)
  : lcd(addr, c, r),
    cols(c),
    rows(r),
    labels(nullptr),
    values(nullptr),
    count(0),
    precision(1),
    lastUpdate(0) {}

void display_lcd::begin() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void display_lcd::clear() {
  lcd.clear();
}

void display_lcd::setCursor(uint8_t col, uint8_t row) {
  lcd.setCursor(col, row);
}

void display_lcd::print(const String &text) {
  lcd.print(text);
}

void display_lcd::printAt(uint8_t col, uint8_t row, const String &text) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

void display_lcd::printCenter(uint8_t row, const String &text) {
  int pos = (cols - text.length()) / 2;
  if (pos < 0) pos = 0;
  lcd.setCursor(pos, row);
  lcd.print(text);
}

void display_lcd::setBacklight(bool state) {
  state ? lcd.backlight() : lcd.noBacklight();
}

void display_lcd::setData(const String labels[], float *vals,
                          uint8_t cnt, uint8_t prec) {
  this->labels = labels;
  this->values = vals;
  this->count = cnt;
  this->precision = prec;
}

void display_lcd::update() {
  if (!labels || !values) return;

  unsigned long now = millis();
  if (now - lastUpdate < 500) return;
  lastUpdate = now;

  for (uint8_t i = 0; i < rows; i++) {
    lcd.setCursor(0, i);
    lcd.print("                    "); 
  }

  char buf[21]; 
  for (uint8_t i = 0; i < count && i < rows; i++) {
    lcd.setCursor(0, i);
    lcd.print(labels[i]);
    lcd.print(": ");

    dtostrf(values[i], 0, precision, buf);
    lcd.print(buf);
  }
}
