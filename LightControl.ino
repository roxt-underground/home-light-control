#include "button.hpp"
#include "lights.hpp"

#define p_void (void(*)(void))

InputButton button1(3);
InputButton button2(4);

DigitalLight light1(5);
DigitalLight light2(6);
AnalogLight light3(9);

void groupSwitchOff(void);


void setup() {
  // put your setup code here, to run once:
  button1.setShortClick([](){ 
                              light3.shadeToggle();
                            });
  button1.setLongClick([](){ 
                              light3.shadeBrightness(16, 30, 5);
                              light2.switchOn();
                           });

  button2.setShortClick([](){ 
                              light1.toggle();
                            });
  button2.setLongClick([]() {
                              light1.switchOff();
                              light2.switchOff();
                              light3.switchOff();
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
