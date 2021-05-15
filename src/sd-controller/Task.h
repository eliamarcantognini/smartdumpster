#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeElapsed;
  bool enabled = false;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  int getPeriod() {
    return myPeriod;
  }

  void enable() {
    enabled = true;
  }

  void disable() {
    enabled = false;
    timeElapsed = 0;
  }

  bool isEnabled() {
    return enabled;
  }

  
};

#endif
