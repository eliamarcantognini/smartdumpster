#include "Arduino.h"
#include "MsgService.h"
#include "config.h"


MsgService::MsgService(){
  channel = new SoftwareSerial(BD_RX, BD_TX);
}

void MsgService::init(){
  MsgService();
  content.reserve(256);
  channel->begin(9600);
}

void MsgService::sendMsg(Msg msg){
  channel->println(msg.getContent());  
}

bool MsgService::isMsgAvailable(){
  return channel->available();
}

Msg* MsgService::receiveMsg(){
  while (channel->available()) {
    char ch = (char) channel->read();
    if (ch == '\n'){
      Msg* msg = new Msg(content); 
      content = "";
      return msg;    
    } else {
      content += ch;      
    }
  }
  return NULL;  
}
