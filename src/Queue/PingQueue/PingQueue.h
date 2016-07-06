#ifndef PINGQUEUE_H_
#define PINGQUEUE_H_
#include "../Queue.h"

class PingQueue: public Queue{
 public:
  PingQueue(int,int);
  void tick(int);
 protected:
  Package isAvai(Package);
  Package sendPackage(Package);
  Package isDone(Package);
  Package getPackage(Package);
  uint64_t last;
  int delay;
};

#endif // PINGQUEUE_H_
