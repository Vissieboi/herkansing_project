#include "ZumoLineFollower.h"

ZumoLineFollower::ZumoLineFollower() : 
    calibrator(lineSensors, buttonA, buzzer),
    pidController(maxVermogen, 2000, 1.5, 0.5, 0.5), // maxvermogen, target error, const_int, const_afg, const_error
    maxVermogen(400) {}

void ZumoLineFollower::setup() {
    buttonA.waitForButton();
    lineSensors.initFiveSensors();
    calibrator.calibrateColor();
    calibrator.calibrateLineSensors(motors);
    delay(1000);
    buttonA.waitForButton();
    delay(200);
}

void ZumoLineFollower::checkuitkomst() {
    Serial.print(sensorWaarde[1]);
    Serial.print(" ");
    Serial.print(sensorWaarde[2]);
    Serial.print(" ");
    Serial.print(sensorWaarde[3]);
    Serial.println();
}

void ZumoLineFollower::drive() {
    int green = calibrator.getColorValue("green");
    int brown = calibrator.getColorValue("brown");
    int black = calibrator.getColorValue("black");
    int gray = calibrator.getColorValue("gray");
    int gray2 = calibrator.getColorValue("gray2");


    if (sensorWaarde[2] > green - 30 && sensorWaarde[2] < green + 30) {
        maxVermogen = 200;
    }
    else if (sensorWaarde[2] > black - 30 && sensorWaarde[2] < black + 30) {
        maxVermogen = 350;

    }
    /*
    else if (sensorWaarde[2] > brown - 30 && sensorWaarde[2] < brown + 30) {
        motors.setSpeeds(0, 0);
        buzzer.play(">g32");
        motors.setSpeeds(100, 100);
        delay(1500);

    }
    */
 
    //rechtsafslaan
    //  else if (sensorWaarde[4] > gray - 15 && sensorWaarde[4] < gray + 15) { //vergelijk de sensor waarde met de vooraf gecalibreerde grijze kleur en hij mag er 15 vanaf zitten.
    //   motors.setSpeeds(250,50);    //de motors een bocht laten maken
    //   delay(1200);                  //delay van 1 sec
    //   motors.setSpeeds(0,0);        // de motoren stoppen
    // }

    // //linksafslaan
    //  else if (sensorWaarde[2] > gray2 - 15 && sensorWaarde[2] < gray2 + 15) { //vergelijk de sensor waarde met de vooraf gecalibreerde grijze kleur en hij mag er 15 vanaf zitten.
    //   motors.setSpeeds(50,250);    //de motors een bocht laten maken
    //   delay(1200);                  //delay van 1 sec
    //   motors.setSpeeds(0,0);        // de motoren stoppen
    // }
}


void ZumoLineFollower::loop() {
    Serial.println("ik zit in linefollower loop");
    lineSensors.read(sensorWaarde);
    motors.setSpeeds(100,100);
    drive();
}