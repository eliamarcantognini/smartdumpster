#ifndef __MSGSERVICEBT__
#define __MSGSERVICEBT__

#include "Arduino.h"
#include "SoftwareSerial.h"

class Msg {
  String content;

public:
  Msg(const String& content){
    this->content = content;
  }
  
  String getContent(){
    return content;
  }
};

class MsgService {
    
public: 
  MsgService();  
  void init();  
  bool isMsgAvailable();
  Msg* receiveMsg();
  void sendMsg(Msg msg);

private:
  String content;
  SoftwareSerial* channel;
  
};

#endif
