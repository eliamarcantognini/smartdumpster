#ifndef __DUMPSTERDOOR__
#define __DUMPSTERDOOR__

#include "ServoMotorImpl.h"
#include "LedController.h"

class DumpsterDoor {

    private:
    ServoMotorImpl* servo;
    LedController* ledController;
    
    public:
    DumpsterDoor();
    void open(TrashType trash);
    void close();

    protected:
    ServoMotorImpl* getServo() {
        return servo;
    }
    LedController* getLedController() {
        return ledController;
    }

};

#endif