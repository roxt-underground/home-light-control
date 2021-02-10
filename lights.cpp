#include "lights.hpp"
#include <Arduino.h>
#include <math.h>


#if defined(ESP8266) || defined(ESP32)
long e_min(long a, long b) {
  if (a < b) return a;
  else return b;
}

long e_max(long a, long b) {
  if (a > b) return a;
  else return b;
}
#endif

DigitalLight::DigitalLight(unsigned char pinNumber)
  : _pin(pinNumber),
    _state(LIGHTS_OFF)
{
  pinMode(_pin, OUTPUT);
  this->switchOff();
}


void DigitalLight::tick(void) {
  if (_state == LIGHTS_DELAY_OFF) checkDelayOff();
}


void DigitalLight::switchOff(void) {
  _state = LIGHTS_OFF;
  digitalWrite(_pin, this->getLow());
}


void DigitalLight::switchOn(void) {
  _state = LIGHTS_ON;
  digitalWrite(_pin, this->getHigh());
}


void DigitalLight::toggle(void) {
  if (_state == LIGHTS_OFF) switchOn(); 
  else if (_state == LIGHTS_ON) switchOff();
  else if (_state == LIGHTS_DELAY_OFF) switchOn();
}



void DigitalLight::delayOff(unsigned long _delay) {
  if (_state == LIGHTS_OFF) return;
  _state = LIGHTS_DELAY_OFF;
  _off_delay = _delay;
  _off_planed_at = millis();
}


void DigitalLight::checkDelayOff(void) {
  if (millis() - _off_planed_at > _off_delay) switchOff();
}


DigitalLightInverted::DigitalLightInverted(unsigned char pinNumber)
  : DigitalLight(pinNumber)
{
  this->switchOff();
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
  _brightness = PWMRANGE;
}


void AnalogLight::setBrightness(short brtns){
#if defined(ESP8266) || defined(ESP32)
  _brightness = e_min(PWMRANGE, e_max(brtns, 0));
# else
  _brightness = min(PWMRANGE, max(brtns, 0));
# endif
  if (_brightness == 0) {
    switchOff();
    return;
  }
  if (_brightness == PWMRANGE) {
    switchOn();
    return;
  }
  if (_state != LIGHTS_SHAIDING) _state = LIGHTS_ON;
  
  analogWrite(_pin, _brightness);
}


void AnalogLight::shadeBrightness(unsigned short brtns, 
                                  unsigned long shade_timeout, 
                                  short brightness_step)
{
  _state = LIGHTS_SHAIDING;
  _brightness_step = abs((int)brightness_step);
  if (_brightness_step == 0) return;
  
#if defined(ESP8266) || defined(ESP32)
  _goal_brightness = e_min(PWMRANGE, e_max(brtns, 0));
#else
  _goal_brightness = min(PWMRANGE, max(brtns, 0));
#endif
  if (_brightness > _goal_brightness) _brightness_step = -_brightness_step;
  _shade_timeout = shade_timeout;
  _last_shade_step_time = millis();
}


void AnalogLight::shadeByTime(unsigned short brtns, unsigned long shade_timeout) {
#if defined(ESP8266) || defined(ESP32)
  short goal = e_min(PWMRANGE, e_max(brtns, 0)), delta = goal - (short)_brightness;
  short abt_step = e_max(delta / 50, 1) ;  // 255/5 ~= 50
#else
  short goal = min(PWMRANGE, max(brtns, 0)), delta = goal - (short)_brightness;
  short abt_step = max(delta / 50, 1) ;  // 255/5 ~= 50
#endif
  shadeBrightness(goal, shade_timeout/abs(delta/abt_step), abt_step);
}


void AnalogLight::shadeToggle(unsigned long shade_timeout, 
                 short brightness_step) {
  if (_state == LIGHTS_OFF) shadeBrightness(PWMRANGE, shade_timeout, brightness_step);
  else if (_state == LIGHTS_ON) shadeBrightness(0, shade_timeout, brightness_step);
  else if (_state == LIGHTS_DELAY_OFF) _state = LIGHTS_ON;
  else if (_state == LIGHTS_SHAIDING) {
    short _goal;
    if (_brightness_step > 0) _goal = 0;
    else _goal = PWMRANGE;
    shadeBrightness(_goal, shade_timeout, brightness_step);
  }
}


void AnalogLight::brightnessUp(unsigned short brtns) {
  setBrightness(_brightness + brtns);
}


void AnalogLight::brightnessDown(unsigned short brtns) {
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
