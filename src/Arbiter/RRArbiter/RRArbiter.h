#ifndef RR_ARBITER_H_
#define RR_ARBITER_H_

#include <iostream>
#include "../Arbiter.h"

class RRArbiter: public Arbiter{
 public:
  RRArbiter(int);
  void tick(int);
  int getPort(){return port;};
 protected:
  Package isAvai(int,Package);
  Package sendPackage(int,Package);
  Package isDone(int,Package);
  Package getPackage(int,Package);

  CallBackFunc* isAvai_p;
  CallBackFunc* sendPackage_p;
  CallBackFunc* isDone_p;
  CallBackFunc* getPackage_p;

  int port,used;
};

#endif //RR_ARBITER_H_
