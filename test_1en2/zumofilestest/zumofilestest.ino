//test 1 en 2
#include "prox.h"
#include <Wire.h>
frontProxSensor proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;

void setup() {
  // put your setup code here, to run once:
  proxSensors.proxSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  proxSensors.proxLoop();
}

// #include <Zumo32U4.h>
// #include "prox.h"
// #include <Wire.h>
// frontProxSensor proxSensors;
// Zumo32U4ButtonA buttonA;
// Zumo32U4ButtonB buttonB;
// Zumo32U4Motors motors;

// void setup() {
//   // put your setup code here, to run once:
//   // lineSensors.setup();
//   buttonA.waitForButton();
//   // Serial.println("Knop A is ingedrukt");
//   // frontProxSensor.proxSetup();
// }

// bool loop_prox = false;

// void loop() {
//   // put your main code here, to run repeatedly:
//   // lineSensors.loop();
//   if (buttonB.isPressed()){//dit doe ik inplaats van dat het een bruine lijn leest, want dat lukte mij niet.
//       loop_prox = true;
      
//   }
//   if(loop_prox == true){
//       proxSensors.proxStart();//dit werkt

//   }
// }
