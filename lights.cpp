#include "lights.hpp"
#include <Arduino.h>


DigitalLight::DigitalLight(unsigned short pinNumber) {
  _pin = pinNumber;
  _state = LIGHTS_OFF;
  pinMode(_pin, OUTPUT);
}


void DigitalLight::tick(void) {
  if (_state == LIGHTS_DELAY_OFF) checkDelayOff();
}


void DigitalLight::switchOff(void) {
  _state = LIGHTS_OFF;
  digitalWrite(_pin, LOW);
}


void DigitalLight::switchOn(void) {
  _state = LIGHTS_ON;
  digitalWrite(_pin, HIGH);
}


void DigitalLight::toggle(void) {
  if (_state == LIGHTS_OFF) switchOn(); 
  else if (_state == LIGHTS_ON) switchOff();
  else if (_state == LIGHTS_DELAY_OFF) switchOn();
}


void DigitalLight::delayOff(void) {
  if (_state == LIGHTS_OFF) return;
  _state == LIGHTS_DELAY_OFF;
  _off_delay = 1000 * 5 * 60; // 5 minutes
  _off_planed_at = millis();
}

void DigitalLight::checkDelayOff(void) {
  if (millis() - _off_planed_at > _off_delay) switchOff();
}
