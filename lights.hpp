#define LIGHTS_OFF 0
#define LIGHTS_ON 1
#define LIGHTS_DELAY_OFF 2
#define LIGHTS_SHAIDING 3


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
};


class AnalogLight: public DigitalLight {
  public:
    AnalogLight(unsigned char pinNumber);

    void setBrightness(short brtns);
    void shadeBrightness(unsigned short brtns);
    void brightnessUp(unsigned short brtns = 5);
    void brightnessDown(unsigned short brtns = 5);
  private:
    unsigned short _brightness, _brightness_step;
    unsigned long _shade_timeout, _last_shade_step_time;
};
