#ifndef PRIORITY_ARBITER_H_
#define PRIORITY_ARBITER_H_

#include <iostream>
#include "../Arbiter.h"

class PriorityArbiter: public Arbiter{
 public:
  PriorityArbiter(int);
  void tick(int);
 protected:
  Package isAvai(int,Package);
  Package sendPackage(int,Package);
  Package isDone(int,Package);
  Package getPackage(int,Package);

  CallBackFunc* isAvai_p;
  CallBackFunc* sendPackage_p;
  CallBackFunc* isDone_p;
  CallBackFunc* getPackage_p;
  
};

#endif //PRIORITY_ARBITER_H_
