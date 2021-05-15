#ifndef __LED_CONTROLLER__
#define __LED_CONTROLLER__

#include "Led.h"
#include "config.h"

class LedController {
    private:
        Light* ledA;
        Light* ledB;
        Light* ledC;

    public:
        LedController();
        void on(TrashType trash);
        void off();
};

#endif