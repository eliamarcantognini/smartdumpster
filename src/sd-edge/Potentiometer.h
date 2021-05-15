#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer {
public:
    Potentiometer(int pin);
    float getValue();
    bool updateValue();

private:
    int pin;
    float value;
};

#endif