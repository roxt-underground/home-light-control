#include "button.hpp"

InputButton button1(3);

void setup() {
  // put your setup code here, to run once:
  button1.long_press_limit = 2000;
}

void loop() {
  // put your main code here, to run repeatedly:
  button1.tick();
  delay(100);
}
