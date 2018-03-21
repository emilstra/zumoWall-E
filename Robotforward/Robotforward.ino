#include <Arduino.h>
#line 1 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
#line 1 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
/*
Drive forward and turn left or right when border is detected
  - Only reflectionsensor 0 and 5 are used.
*/
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
 
#define LED 13
 
// this might need to be tuor different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  200 // ned f
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     400 // 0 is stopped, 400 is full speed
#define TURN_SPEED        400
#define FORWARD_SPEED     400
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     150 // ms
 
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

unsigned long time = 0;

int x = 0;

#line 34 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
void setup();
#line 42 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
void loop();
#line 67 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
void turnLeft();
#line 78 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
void turnRight();
#line 34 "C:\\Users\\Gauldal VGS\\Documents\\Arduino\\Robotforward\\Robotforward.ino"
void setup()
{
   Serial.begin(9600);
   sensors.init();
   button.waitForButton();
   
}

void loop() {
  x = random(1,2);
  sensors.read(sensor_values);

  if (sensor_values[0] < QTR_THRESHOLD || sensor_values[1] < QTR_THRESHOLD)
  {
    turnLeft(); 
  }
  else if (sensor_values[5] < QTR_THRESHOLD || sensor_values[4] < QTR_THRESHOLD)
  {
    turnRight(); 
  }
  else
  {   
    if (millis() > time + 750) {
       motors.setSpeeds(FORWARD_SPEED/2, FORWARD_SPEED/2);
    } else {
       motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    }
    // otherwise, go straight
    
   
  }
}

void turnLeft () {   
      time = millis();
      // if leftmost sensor detects line, reverse and turn to the right
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      delay(REVERSE_DURATION);
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      delay(TURN_DURATION*x);
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);

}

void turnRight ()  {
    time = millis();
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION*x);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
