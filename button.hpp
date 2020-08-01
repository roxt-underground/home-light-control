class InputButton {
  public:
    InputButton(short pinNumber);
    void tick(void);
    int long_press_limit = 1500;

    void setShortClick(void (* func)(void));
    void setLongClick(void (* func)(void));

  private:
    int _pin;
    unsigned long _pressed_at;
    bool _last_state;

    void (* shortClick)(void);
    void (* longClick)(void);
};

void nope(void);
