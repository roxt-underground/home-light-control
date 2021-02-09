#include <Arduino.h>

#define LIGHTS_OFF 0
#define LIGHTS_ON 1
#define LIGHTS_DELAY_OFF 2
#define LIGHTS_SHAIDING 3

#ifndef PWMRANGE
#define PWMRANGE 255
#endif


class DigitalLight {
  public:
    DigitalLight(unsigned char pinNumber);
    void tick(void);

    void switchOff(void);
    void switchOn(void);
    void toggle(void);
    void delayOff(unsigned long _delay = 1000 * 30);

  protected:
    unsigned char _state;
    const unsigned char _pin;

  private:
    unsigned long _off_delay = 0, _off_planed_at; 
    void checkDelayOff(void);
    const unsigned short low_state = LOW, high_state = HIGH;
};


class DigitalLightInverted: public DigitalLight {
  public:
    DigitalLightInverted(unsigned char pinNumber);

  private:
    const unsigned short low_state = HIGH, high_state = LOW;
};


class AnalogLight: public DigitalLight {
  public:
    AnalogLight(unsigned char pinNumber);
    
    void tick(void);
    void switchOff(void);
    void switchOn(void);

    void setBrightness(short brtns);
    void shadeBrightness(unsigned short brtns, 
                         unsigned long shade_timeout=30, 
                         short brightness_step=15);
    void shadeByTime(unsigned short brtns, unsigned long shade_timeout=10000);
    void shadeToggle(unsigned long shade_timeout=30, 
                     short brightness_step=15);
    void brightnessUp(unsigned short brtns = 5);
    void brightnessDown(unsigned short brtns = 5);
  private:
    void checkShaiding(void);
    short _brightness_step;
    short _brightness, _goal_brightness;
    unsigned long _shade_timeout, _last_shade_step_time;
    
};
