#ifndef ARBITER_H_
#define ARBITER_H_
#include "../Common.h"

class Arbiter: public Module{
 public:
  Arbiter(int);
 protected:
  virtual Package isAvai(int,Package){};
  virtual Package sendPackage(int,Package){};
  virtual Package isDone(int,Package){};
  virtual Package getPackage(int,Package){};
};


#endif //ARBITER_H_
