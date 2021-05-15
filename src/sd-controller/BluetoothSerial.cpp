#include "BluetoothSerial.h"

BluetoothSerial::BluetoothSerial() {
  msgService.init();
  this->time = false;
  this->trash = TrashType(-1);
};

void BluetoothSerial::reset(char param) {
  switch(param){
    case 'm': this->trash = TrashType(-1); break;
    case 't': this->time = false; break;
    }
}

void BluetoothSerial::checkMessage() {
  lastMsg = msgService.receiveMsg();
  if(lastMsg != NULL){
    String msg = lastMsg->getContent();
    switch(msg[0]){
      case 't': this->time = true; break;
      case 'A' : this->trash = TrashType(0); break;
      case 'B' : this->trash = TrashType(1); break;
      case 'C' : this->trash = TrashType(2); break;
    }
  }
};

TrashType BluetoothSerial::rcvTrashType() {
  this->checkMessage();
  int tmp = this->trash;
  reset('m');
  return TrashType(tmp);
}

bool BluetoothSerial::rcvAddTime() {
  this->checkMessage();
  int tmp = this->time;
  reset('t');
  return tmp;
}

void BluetoothSerial::displayTime(long timeInMillis) {
  int time = (timeInMillis / 1000) + 1;
  msgService.sendMsg(Msg(String(time)));
}

void BluetoothSerial::noTime() {
  msgService.sendMsg(Msg("n"));
}
