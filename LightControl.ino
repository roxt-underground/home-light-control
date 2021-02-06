#include "button.hpp"
#include "lights.hpp"

#define p_void (void(*)(void))

InputButton button1(A0);
InputButton button2(A1);

AnalogLight light1(D5);
DigitalLight light2(D6);
AnalogLight light3(D9);

void groupSwitchOff(void);


void setup() {
  // put your setup code here, to run once:
  button1.setShortClick([](){ 
                              light3.shadeToggle();
                            });
  button1.setLongClick([](){ 
                              light3.shadeBrightness(24, 30, 5);
                           });

  button2.setShortClick([](){ 
                              light1.shadeToggle();
                            });
  button2.setLongClick([]() {
                              light1.shadeBrightness(0, 30, 5);
//                              light2.switchOff();
                              light3.shadeByTime(0, 30000);
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
