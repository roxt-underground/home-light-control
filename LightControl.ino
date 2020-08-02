#include "button.hpp"
#include "lights.hpp"

#define p_void (void(*)(void))

InputButton button1(3);
InputButton button2(4);

DigitalLight light1(5);
DigitalLight light2(6);

void groupSwitchOff(void);

void setup() {
  // put your setup code here, to run once:
  button1.long_press_limit = 2000;
  button1.setShortClick(p_void &light1.toggle);
  button1.setLongClick(p_void &light1.delayOff);

  button2.setShortClick(p_void &light2.toggle);
  button2.setLongClick(&groupSwitchOff);
}

void loop() {
  button1.tick();
  button2.tick();
  
  light1.tick();
  light2.tick();
  delay(100);
}

void groupSwitchOff(void) {
  light1.switchOff();
  light2.switchOff();
}
