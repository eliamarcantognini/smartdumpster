#include "MainTask.h"

MainTask::MainTask() {
  serial = new BluetoothSerial();
  door = new DumpsterDoor();
  depositTime = DEPOSIT_TIME;
};

void MainTask::init(int period) {
    Task::init(period);
    state = CLOSED;
}

void MainTask::tick() {
    switch(state) {
        case CLOSED: {
            TrashType trash = serial->rcvTrashType();
            if (trash != -1) {
                openDumpster(trash);
            }
            break;
        }
        case OPEN: {
            depositTime -= getPeriod();
            if (serial->rcvAddTime()) {
                depositTime += DEPOSIT_TIME;
            }
            serial->displayTime(depositTime);
            if (depositTime <= 0) {
                closeDumpster();
            }
            break;
        } 
    }
}

void MainTask::openDumpster(TrashType trash) {
    getDumpsterDoor()->open(trash);
    state = OPEN;
}

void MainTask::closeDumpster() {
    getDumpsterDoor()->close();
    getUserConsole()->noTime();
    state = CLOSED;
    depositTime = DEPOSIT_TIME;
}