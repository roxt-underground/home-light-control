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
  bool is_pressed = currentState();
  unsigned long current_time = millis();

  if (is_pressed != _last_state) {
    if (_last_state) {
      if (current_time - _pressed_at < long_press_limit) (*shortClick)();
      else (*longClick)();
    }
    else {
      _pressed_at = current_time;
    }
    _last_state = is_pressed;
  }
}

bool InputButton::currentState(void){
  return digitalRead(_pin) == HIGH;
}


InputButtonInversed::InputButtonInversed(unsigned short pinNumber, unsigned short _pinMode)
  :InputButton(pinNumber)
{
  pinMode(_pin, _pinMode);
}

bool InputButtonInversed::currentState(void) {
  return digitalRead(_pin) == LOW;
}

void nope(void) {};
