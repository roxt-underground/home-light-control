#include "button.hpp"
#include "lights.hpp"

#define p_void (void(*)(void))

InputButton button1(3);
InputButton button2(4);

DigitalLight light1(5);
DigitalLight light2(6);
DigitalLight light3(7);

void groupSwitchOff(void);


void setup() {
  // put your setup code here, to run once:
  button1.setShortClick([](){ light1.toggle(); });
  button1.setLongClick([](){ light1.delayOff(1000 * 10); });

  button2.setShortClick([](){ 
                              light2.toggle(); 
                              light3.switchOff(); 
                            });
  button2.setLongClick([]() {
                              light1.switchOn();
                              light2.switchOn();
                              light3.switchOn();
                            });
}

void loop() {
  button1.tick();
  button2.tick();
  
  light1.tick();
  light2.tick();
  delay(10);
}

void groupSwitchOff(void) {
  light1.switchOn();
  light2.switchOn();
}
