#include "LedController.h"

LedController::LedController() {
    ledA = new Led(LA_PIN);
    ledB = new Led(LB_PIN);
    ledC = new Led(LC_PIN);
}

void LedController::on(TrashType trash) {
    switch(trash) {
      case 0: ledA->switchOn(); break;
      case 1: ledB->switchOn(); break;
      case 2: ledC->switchOn(); break;
    }
}

void LedController::off() {
    ledA->switchOff();
    ledB->switchOff();
    ledC->switchOff();
}