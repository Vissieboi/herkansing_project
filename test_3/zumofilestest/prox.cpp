#include "prox.h"

#define LEFT 0
#define RIGHT 1

frontProxSensor::frontProxSensor()
    :senseDir(RIGHT), turningLeft(false), turningRight(false), turnSpeed(turnSpeedMax), lastTimeObjectSeen(0){
      proxSensors.initFrontSensor();
      Serial.println("Proximity sensors initialized");

}

void frontProxSensor::turnRight(){
    // Serial.println("hij gaat naar rechts");
    motors.setSpeeds(turnSpeed, -turnSpeed);
    turningLeft = false;
    turningRight = true;
}

void frontProxSensor::turnLeft(){
    Serial.println("hij gaat naar links");
    motors.setSpeeds(-turnSpeed, turnSpeed);
    turningLeft = true;
    turningRight = false;
}

void frontProxSensor::stop(){
    motors.setSpeeds(0, 0);
    turningLeft = false;
    turningRight = false;
}

void frontProxSensor::proxLoop() {
  proxSensors.read();
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds();
  
  Serial.print("Left Value: ");
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
    lastTimeObjectSeen = millis();

    if (leftValue < rightValue) {
      // Serial.println("Turning Right");
      turnRight();
      senseDir = RIGHT;
    } else if (leftValue > rightValue) {
      Serial.println("Turning Left");
      turnLeft();
      senseDir = LEFT;
    } else {
      // Serial.println("Object in front, moving forward");
      motors.setSpeeds(200, 200);
    }

    while (objectInfront) {
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
