#define LIGHTS_OFF 0
#define LIGHTS_ON 1
#define LIGHTS_DELAY_OFF 2

class DigitalLight {
  public:
    DigitalLight(unsigned short pinNumber);
    void tick(void);

    void switchOff(void);
    void switchOn(void);
    void toggle(void);
    void delayOff(void);

  private:
    unsigned short _pin, _state;
    unsigned long _off_delay = 0, _off_planed_at; 
    void checkDelayOff(void);
};
