#include "DumpsterDoor.h"

DumpsterDoor::DumpsterDoor() {
  ledController = new LedController();
  servo = new ServoMotorImpl(SERVO_PIN);
}

void DumpsterDoor::open(TrashType trash) {
  this->getLedController()->on(trash);
  this->getServo()->on();
  this->getServo()->setPosition(SERVO_OPEN);
  this->getServo()->off();
}

void DumpsterDoor::close() {
  this->getLedController()->off();
  this->getServo()->on();
  this->getServo()->setPosition(SERVO_CLOSED);
  this->getServo()->off();
}
