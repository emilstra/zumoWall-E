
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
 
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
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

unsigned long time = 0;

int x = 0;

const int echoPin = A4;
const int triggerPin = A5;
const int maxDistance = 50;

const int servoPin = 6;
 
NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 

Pushbutton button(ZUMO_BUTTON); 

int degreesServo = 0;
int degreesStep = 5;

PLab_ZumoMotors plab_Motors;

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
  

   
   
   myServo.attach(servoPin); 
   myServo.write(90);
   button.waitForButton(); // start when button pressed
   
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

float sonarDistance() {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  Serial.println(distance);
  if (distance == 0.0) { // sonar gives zero when outside range
    // Turn off LED and just go forward
    digitalWrite(LED,LOW); 
   } else {
    digitalWrite(LED,HIGH);
   }
   return distance;
}

void stepServo() {
  
   degreesServo = degreesServo + degreesStep;
   if (degreesServo > 180) {
       degreesStep = -degreesStep;
       degreesServo = 180;
   } else if (degreesServo < 0) {
       degreesStep = -degreesStep;
       degreesServo = 0;
   } 
   myServo.write(degreesServo);
  
 
}

void loop() {
  x = random(1,2);
  sensors.read(sensor_values);

  stepServo();
  int distance = sonarDistance();
  

  if (sensor_values[0] < QTR_THRESHOLD || sensor_values[1] < QTR_THRESHOLD)
  {
    turnLeft(); 
  }
  else if (sensor_values[5] < QTR_THRESHOLD || sensor_values[4] < QTR_THRESHOLD)
  {
    turnRight(); 
  }
  else if (distance > 0) {
     if (degreesServo > 90) {
        plab_Motors.turnLeft(200,degreesServo-90);
        motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
     } else if (degreesServo < 90) {
       plab_Motors.turnRight(200,90-degreesServo);
       motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
     };
  }
  else
  {   
    if (millis() > time + 750) {
       motors.setSpeeds(FORWARD_SPEED/2, FORWARD_SPEED/2);
    } else {
       motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    }   
  }
}


