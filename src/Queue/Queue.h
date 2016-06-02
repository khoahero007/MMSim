#ifndef QUEUE_H_
#define QUEUE_H_
#include "../Common.h"

class Queue: public Module{
 public:
  Queue(int);
 protected:
  virtual Package isFull(Package){};
  virtual Package sendPackage(Package){};
  virtual Package isDone(Package){};
  virtual Package getPackage(Package){};
  std::vector<Package> queue;
  std::vector<int> done;
  int size;
  
};

#endif // QUEUE_H_
