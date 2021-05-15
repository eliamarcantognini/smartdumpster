#ifndef __SERVOMOTORIMPL__
#define __SERVOMOTORIMPL__

#include "ServoMotor.h"
#include <Arduino.h>
#include "ServoTimer2.h"
#include "config.h"

class ServoMotorImpl: public ServoMotor {

public:
  ServoMotorImpl(int pin);

  void on();
  void setPosition(int angle);
  int getPosition();
  void off();
    
private:
  int pin;
  int currentAngle;
  ServoTimer2 motor; 
};

#endif
