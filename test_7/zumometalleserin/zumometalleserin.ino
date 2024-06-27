#include "prox.h"
#include "ZumoLineFollower.h"
#include "ZumoPIDController.h"
#include "ZumoCalibrator.h"
#include <Zumo32U4.h>
#include <Wire.h>

frontProxSensor proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4Motors motors;
ZumoLineFollower zumo;

void setup() {
  // put your setup code here, to run once:
  zumo.setup();
}
bool status_ButtonB = false;

void loop() {
  // put your main code here, to run repeatedly:
  zumo.loop();
  // if (buttonB.isPressed()){
  //   status_ButtonB = true;
  // }
  // else if(status_ButtonB == true){
  //   proxSensors.proxStart();
  // }
}