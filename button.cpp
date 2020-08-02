#include "button.hpp"
#include <Arduino.h>


InputButton::InputButton(unsigned short pinNumber) {
  _pin = pinNumber;
  _last_state = false;
  shortClick = &nope;
  longClick = &nope;

  pinMode(_pin, INPUT);
}


void InputButton::setShortClick(void (* func)(void)) {
  shortClick = func;
}


void InputButton::setLongClick(void (* func)(void)) {
  longClick = func;
}


void InputButton::tick(void) {
  bool is_pressed = (digitalRead(_pin) == HIGH);
  unsigned long current_time = millis();

  if (is_pressed != _last_state) {
    if (_last_state) {
      if (current_time - _pressed_at < long_press_limit) shortClick();
      else longClick();
    }
    else {
      _pressed_at = current_time;
    }
    _last_state = is_pressed;
  }
}

void nope(void) {}
