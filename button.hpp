#include <Arduino.h>

class InputButton {
  public:
    InputButton(unsigned short pinNumber);
    void tick(void);
    int long_press_limit = 500;

    void setShortClick(void (* func)(void));
    void setLongClick(void (* func)(void));

  protected:
    unsigned short _pin;
    virtual bool currentState(void);

  private:
    unsigned long _pressed_at;
    bool _last_state;

    void (* shortClick)(void);
    void (* longClick)(void);
};

class InputButtonInversed: public InputButton {
  public:
    InputButtonInversed(unsigned short pinNumber, unsigned short _pinMode=INPUT);
  protected:
    virtual bool currentState(void) override;
};

void nope(void);
