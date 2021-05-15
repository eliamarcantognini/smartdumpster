#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
    this->pin = pin;
    updateValue();
}

float Potentiometer::getValue(){
    return value;
}

bool Potentiometer::updateValue(){ 
    float curr = map(analogRead(pin), 0, 1023, 0, 100);
    if(curr != value){
        value = curr;
        return true;
    }
    return false;
}