#ifndef __BLUETOOTH_SERIAL__
#define __BLUETOOTH_SERIAL__

#include "MsgService.h"
#include "config.h"

class BluetoothSerial {
  private:

    MsgService msgService;
    Msg* lastMsg;
    void reset(char param);
    TrashType trash;
    bool time;
  
  public:
  
    BluetoothSerial();
    void checkMessage();
    TrashType rcvTrashType();
    bool rcvAddTime();
    void displayTime(long timeInMillis);
    void noTime();
};
#endif
