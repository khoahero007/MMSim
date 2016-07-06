#include "MemDevice.h"

MemDevice::MemDevice():Module(0){
  ToBeCalledList.push_back(std::bind(&MemDevice::isAvai,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isAvai");
  ToBeCalledList.push_back(std::bind(&MemDevice::sendPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("sendPackage");
  ToBeCalledList.push_back(std::bind(&MemDevice::isDone,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isDone");
  ToBeCalledList.push_back(std::bind(&MemDevice::getPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("getPackage");

  MasterTag.push_back("Command");
}
