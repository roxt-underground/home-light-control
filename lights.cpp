#include "lights.hpp"
#include <Arduino.h>


DigitalLight::DigitalLight(unsigned char pinNumber)
  : _pin(pinNumber),
    _state(LIGHTS_OFF)
{
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



void DigitalLight::delayOff(unsigned long _delay = 1000 * 30) {
  if (_state == LIGHTS_OFF) return;
  _state = LIGHTS_DELAY_OFF;
  _off_delay = _delay;
  _off_planed_at = millis();
}


void DigitalLight::checkDelayOff(void) {
  if (millis() - _off_planed_at > _off_delay) switchOff();
}

AnalogLight::AnalogLight(unsigned char pinNumber): DigitalLight(pinNumber) { }

void AnalogLight::setBrightness(short brtns){
  if (brtns <= 0) {
    switchOff();
    return;
  }
  if (_state != LIGHTS_SHAIDING) _state = LIGHTS_ON;
  _brightness = min(255, brtns);
  if (_brightness == 255) {
    switchOn();
  }
  analogWrite(_pin, _brightness);
}


void AnalogLight::shadeBrightness(unsigned short brtns){}


void AnalogLight::brightnessUp(unsigned short brtns = 5){}


void AnalogLight::brightnessDown(unsigned short brtns = 5){}
