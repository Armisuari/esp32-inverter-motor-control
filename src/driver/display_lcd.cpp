#include "display_lcd.h"

display_lcd::display_lcd(uint8_t addr, uint8_t c, uint8_t r)
    : lcd(addr, c, r),
      cols(c),
      rows(r),
      labels(nullptr),
      values(nullptr),
      count(0),
      precision(1),
      lastUpdate(0),
      firstDraw(true) {}

void display_lcd::begin()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void display_lcd::clear()
{
  lcd.clear();
  firstDraw = true;
}

void display_lcd::setCursor(uint8_t col, uint8_t row)
{
  lcd.setCursor(col, row);
}

void display_lcd::print(const String &text)
{
  lcd.print(text);
}

void display_lcd::printAt(uint8_t col, uint8_t row, const String &text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

void display_lcd::printCenter(uint8_t row, const String &text)
{
  int pos = (cols - text.length()) / 2;
  if (pos < 0)
    pos = 0;
  lcd.setCursor(pos, row);
  lcd.print(text);
}

void display_lcd::setBacklight(bool state)
{
  state ? lcd.backlight() : lcd.noBacklight();
}

void display_lcd::setData(const String labels[], float *vals,
                          uint8_t cnt, uint8_t prec)
{
  this->labels = labels;
  this->values = vals;
  this->count = cnt;
  this->precision = prec;
  firstDraw = true;
}

void display_lcd::forceRedraw()
{
  firstDraw = true;
}

void display_lcd::update()
{
  if (!labels || !values)
    return;

  unsigned long now = millis();
  if (now - lastUpdate < 500)
    return;
  lastUpdate = now;

  char buf[21];

  for (uint8_t i = 0; i < count && i < rows; i++)
  {

    if (firstDraw)
    {
      lcd.setCursor(0, i);
      lcd.print(labels[i]);
      lcd.print(": ");
    }

    uint8_t valueCol = labels[i].length() + 2;
    lcd.setCursor(valueCol, i);

    dtostrf(values[i], 0, precision, buf);
    lcd.print(buf);

    uint8_t used = strlen(buf);
    for (uint8_t j = valueCol + used; j < cols; j++)
    {
      lcd.print(' ');
    }
  }

  firstDraw = false;
}
