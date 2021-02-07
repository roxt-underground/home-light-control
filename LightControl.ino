#include "button.hpp"
#include "lights.hpp"

#define p_void (void(*)(void))

InputButton button1(A0);
InputButton button2(A1);

AnalogLight light1(3); // PWM pin
DigitalLight light2(12); // simple digital pin
AnalogLight light3(6); // PWM pin

void groupSwitchOff(void);


void setup() {
  // put your setup code here, to run once:
  button1.setShortClick([](){ 
                              light1.shadeToggle();
                            });
  button1.setLongClick([](){ 
                              light2.toggle();
                           });

  button2.setShortClick([](){ 
                              light3.shadeToggle();
                            });
  button2.setLongClick([]() {
                              light1.shadeByTime(0, 5000);
                              light2.delayOff(10000);
                              light3.shadeByTime(0, 15000);
                            });
}

void loop() {
  button1.tick();
  button2.tick();
  
  light1.tick();
  light2.tick();
  light3.tick();
  delay(10);
}
