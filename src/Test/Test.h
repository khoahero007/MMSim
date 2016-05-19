#ifndef TEST_H_
#define TEST_H_
#include "../Common.h"

class Test1: public Module{
 public:
  Test1();
 protected:
  double x;
  Package add(Package);
  Package relay(Package);
};

class Test2: public Module{
 public:
  Test2();
 protected:
  double x;
  Package add(Package);
  Package relay(Package);
};
#endif // TEST_H
