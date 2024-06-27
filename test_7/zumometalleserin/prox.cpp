#include "prox.h"

#define LEFT 0
#define RIGHT 1

//constructor wordt aangemaakt
frontProxSensor::frontProxSensor()
    :senseDir(RIGHT), turningLeft(false), turningRight(false), turnSpeed(turnSpeedMax), lastTimeObjectSeen(0){
      proxSensors.initFrontSensor();
      Serial.println("Proximity sensors initialized");
}


//Door deze methode draait de zumo naar rechts
void frontProxSensor::turnRight(){
    // Serial.println("hij gaat naar rechts");
    motors.setSpeeds(turnSpeed, -turnSpeed);
    turningLeft = false;
    turningRight = true;
}

//Door deze methode draait de zumo naar links
void frontProxSensor::turnLeft(){
    // Serial.println("hij gaat naar links");
    motors.setSpeeds(-turnSpeed, turnSpeed);
    turningLeft = true;
    turningRight = false;
}

//Door deze methode stopt de robot met rijden
void frontProxSensor::stop(){
    motors.setSpeeds(0, 0);
    turningLeft = false;
    turningRight = false;
}

void frontProxSensor::proxStart() {
  Serial.println("ik zit in proxstart");
  proxSensors.read();
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds(); //hier worden twee variabelen aangemaakt waar waardes in worden opgeslagen
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds(); //de waardes zijn de aftand tussen de zumo en het object
  
  Serial.print("Left Value: "); //hier print je de waardes
  Serial.println(leftValue);
  Serial.print("Right Value: ");
  Serial.println(rightValue);

  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
  bool objectInfront = (leftValue == rightValue);

  if (objectSeen) {
    turnSpeed -= deceleration;
  } else {
    turnSpeed += acceleration;
  }

  turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);

  if (objectSeen) {

    if (leftValue < rightValue) { //als leftvalue kleiner is dan rechtervalue dan draait de zumo naar rechts
      Serial.println("Turning Right");
      turnRight();
      senseDir = RIGHT;
    } else if (leftValue > rightValue) { //als leftvalue groter is dan rightvalue dan draait de zumo naar links
      Serial.println("Turning Left");
      turnLeft();
      senseDir = LEFT;
    }
    while (objectInfront) {
      motors.setSpeeds(200, 200);
      proxSensors.read();
      leftValue = proxSensors.countsFrontWithLeftLeds();
      rightValue = proxSensors.countsFrontWithRightLeds();
      objectInfront = (leftValue == rightValue);
      if (!objectInfront) {
        break;
      }
    }
  } else {
    Serial.println("No object detected, continuing in last direction");
    if (senseDir == RIGHT) {
      turnRight();
    } else {
      turnLeft();
    }
  }
}