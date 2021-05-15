#include "Arduino.h"
#include "Scheduler.h"
#include "MainTask.h"

Scheduler sched;

void setup(){  
  sched.init(100);
  Task* mainTask = new MainTask();
  mainTask->init(100);
  mainTask->enable();
  sched.addTask(mainTask);
}

void loop(){
  sched.run();  
}

