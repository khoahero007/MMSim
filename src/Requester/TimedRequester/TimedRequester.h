#ifndef TIMED_REQUESTER_H_
#define TIMED_REQUESTER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Requester.h"

class TimedRequester: public Requester{
 public:
  TimedRequester(std::string);
  void tick(int);
  int isFinish();
 protected:
  std::ifstream fileStream;
  int finish;
  void readPackage();
  CallBackFunc* isFull_p;
  CallBackFunc* sendPackage_p;
  CallBackFunc* isDone_p;
  CallBackFunc* getPackage_p;
  
  std::vector<Package> toSend;
  uint64_t timeStampToSend;
};

#endif //TIMED_REQUESTER_H_
