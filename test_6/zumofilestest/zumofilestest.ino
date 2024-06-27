//test 6
#include <Zumo32U4.h>
#include "prox.h"
#include <Wire.h>
frontProxSensor proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Motors motors;

void setup() {
  buttonA.waitForButton();
}

bool status_ButtonB = false;
bool status_ButtonC = false;

void loop() {
  if (buttonB.isPressed()){//dit doe ik inplaats van dat het een bruine lijn leest, want dat lukte mij niet.
      status_ButtonB = true;
  }
  else if(status_ButtonB == true){
    proxSensors.proxStart();//dit werkt

  }
  if (buttonC.isPressed()){
    status_ButtonC = true;
  }
  while (status_ButtonC == true){
    proxSensors.stop();
  }
      
}

  

