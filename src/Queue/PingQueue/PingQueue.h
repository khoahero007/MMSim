#ifndef PINGQUEUE_H_
#define PINGQUEUE_H_
#include "../Queue.h"
#define DELAY 4

class PingQueue: public Queue{
 public:
  PingQueue(int);
  void tick(int);
 protected:
  Package isFull(Package);
  Package sendPackage(Package);
  Package isDone(Package);
  Package getPackage(Package);
  uint64_t last;
};

#endif // PINGQUEUE_H_
