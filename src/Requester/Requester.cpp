#include "Requester.h"

Requester::Requester():Module(4){
  //Module::Module();
  ToCallTag.push_back("isAvai");
  ToCallTag.push_back("sendPackage");
  ToCallTag.push_back("isDone");
  ToCallTag.push_back("getPackage");
}

int Requester::isFinish(){
  panic("This module is not final yet");
  return -1;
}
