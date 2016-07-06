#ifndef MEM_DEVICE_H_
#define MEM_DEVICE_H_

#include "../Common.h"

class MemDevice: public Module{
 public:
  MemDevice();
 protected:
  virtual Package isAvai(Package){};
  virtual Package sendPackage(Package){};
  virtual Package isDone(Package){};
  virtual Package getPackage(Package){};
};

#endif //MEM_DEVICE_H_
