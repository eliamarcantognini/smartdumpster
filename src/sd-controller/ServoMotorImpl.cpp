#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;  
} 

void ServoMotorImpl::on(){
  motor.attach(pin);    
}

void ServoMotorImpl::setPosition(int angle){
  currentAngle = angle;
  float coeff = (2250.0-750.0)/180;
  motor.write(750 + currentAngle*coeff);
}

int ServoMotorImpl::getPosition() {
  return currentAngle;
}

void ServoMotorImpl::off() {
  motor.detach();    
}