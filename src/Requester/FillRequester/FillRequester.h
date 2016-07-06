#ifndef FILL_REQUESTER_H_
#define FILL_REQUESTER_H_

#include <iostream>
#include <fstream>
#include "../Requester.h"

class FillRequester: public Requester{
 public:
  FillRequester(std::string);
  void tick(int);
  int isFinish();
 protected:
  std::ifstream fileStream;
  int finish;
  int nextPackageValid;
  std::vector<Package> sentPackage;
  Package nextPackage;
  Package readPackage();
  CallBackFunc* isAvai_p;
  CallBackFunc* sendPackage_p;
  CallBackFunc* isDone_p;
  CallBackFunc* getPackage_p;
};

#endif //FILL_REQUESTER_H_
