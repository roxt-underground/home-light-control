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

AnalogLight::AnalogLight(unsigned char pinNumber)
  : DigitalLight(pinNumber),
    _brightness(0)
{ }

void AnalogLight::tick(void) {
  DigitalLight::tick();
  if (_state == LIGHTS_SHAIDING) {checkShaiding();  }
}

void AnalogLight::switchOff(void) {
  DigitalLight::switchOff();
  _brightness = 0;
}


void AnalogLight::switchOn(void) {
  DigitalLight::switchOn();
  _brightness = 255;
}


void AnalogLight::setBrightness(short brtns){
  _brightness = min(255, max(brtns, 0));
  if (_brightness == 0) {
    switchOff();
    return;
  }
  if (_brightness == 255) {
    switchOn();
    return;
  }
  if (_state != LIGHTS_SHAIDING) _state = LIGHTS_ON;
  
  analogWrite(_pin, _brightness);
}

void AnalogLight::shadeBrightness(unsigned short brtns, 
                                  unsigned long shade_timeout=1000, 
                                  short brightness_step=25)
{
  _state = LIGHTS_SHAIDING;
  _brightness_step = abs((int)brightness_step);
  _goal_brightness = min(255, max(brtns, 0));
  if (_brightness > _goal_brightness) _brightness_step = -_brightness_step;
  _shade_timeout = shade_timeout;
  _last_shade_step_time = millis();
}


void AnalogLight::brightnessUp(unsigned short brtns = 5) {
  setBrightness(_brightness + brtns);
}


void AnalogLight::brightnessDown(unsigned short brtns = 5) {
  setBrightness(_brightness - brtns);
}


void AnalogLight::checkShaiding(void) {

  unsigned long millis_passed = millis() - _last_shade_step_time;
  if (millis_passed < _shade_timeout) return;
  short brt_delta = abs(_brightness - _goal_brightness), b_step = abs(_brightness_step);
  
  if(b_step > brt_delta) {
    _state = LIGHTS_ON; // if _goal_brightness == 0 it will be owerriden in setBrightness
    setBrightness(_goal_brightness);
  }
  else setBrightness(_brightness + _brightness_step);
  
  _last_shade_step_time = millis();
}
