
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <vector>

using namespace webots;
using namespace std;

static const int TIME_STEP = 32;        
static const double MAX_SPEED = 6.28;   


const double KP = 2.5;                  
const double DESIRED_DIST = 0.035;     
const double BASE_SPEED = 3.0;          

int main(int argc, char **argv) {
  Robot *robot = new Robot();


  Motor *leftMotor = robot->getMotor("left wheel motor");
  Motor *rightMotor = robot->getMotor("right wheel motor");
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);


  vector<DistanceSensor*> ps(8);
  for (int i = 0; i < 8; ++i) {
    char name[8];
    sprintf(name, "ps%d", i);
    ps[i] = robot->getDistanceSensor(name);
    if (ps[i]) ps[i]->enable(TIME_STEP);
  }


  const int RIGHT_SENSOR_A = 2;
  const int RIGHT_SENSOR_B = 3;

  cout << "Starting simple right-wall follower..." << endl;

  while (robot->step(TIME_STEP) != -1) {

    double r1 = ps[RIGHT_SENSOR_A] ? ps[RIGHT_SENSOR_A]->getValue() : 1e6;
    double r2 = ps[RIGHT_SENSOR_B] ? ps[RIGHT_SENSOR_B]->getValue() : 1e6;
    double rightDist = (r1 + r2) / 2.0;

    double error = DESIRED_DIST - rightDist;

    double correction = KP * error;

 
    double leftSpeed  = BASE_SPEED + correction;
    double rightSpeed = BASE_SPEED - correction;

    if (leftSpeed > MAX_SPEED) leftSpeed = MAX_SPEED;
    if (leftSpeed < -MAX_SPEED) leftSpeed = -MAX_SPEED;
    if (rightSpeed > MAX_SPEED) rightSpeed = MAX_SPEED;
    if (rightSpeed < -MAX_SPEED) rightSpeed = -MAX_SPEED;


    leftMotor->setVelocity(leftSpeed);
    rightMotor->setVelocity(rightSpeed);

  
  }

  delete robot;
  return 0;
}
