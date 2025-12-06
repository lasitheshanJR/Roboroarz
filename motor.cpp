#inlcude <webots/Motor.hpp>
#include <webots/Robot.hpp>
//these are header files in webots simulation 

using namespace webots;

//every 32ms it will loop thourgh out 
static const int Time=32;
static const int Max=6.28;

int main(){
  Robot *robo=new Robot();

  Motor *leftMo=robo->getMotor("left wheel motor");
  Motor *rightMo=robo->getMotor("right wheel motor");

  leftMo->setPosition(INFINITY);
  rightMo->setPosition(INFINITY);

  leftMo->setVelocity(3.0);
  rightMo->setVelocity(3.0);

  while (robo->set(Time)!=-1){}
  return 0;
}
