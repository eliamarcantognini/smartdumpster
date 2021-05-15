#ifndef __MAIN_TASK__
#define __MAIN_TASK__

#include "Task.h"
#include "config.h"
#include "BluetoothSerial.h"
#include "DumpsterDoor.h"

class MainTask: public Task {
    private:
        enum {OPEN, CLOSED} state;
        BluetoothSerial* serial;
        DumpsterDoor* door;
        long depositTime;
        void openDumpster(TrashType trash);
        void closeDumpster();

    public:
        MainTask();
        void init(int period);
        void tick();

    protected:
        BluetoothSerial* getUserConsole(){
            return serial;
        }
        DumpsterDoor* getDumpsterDoor(){
            return door;
        }
};


#endif