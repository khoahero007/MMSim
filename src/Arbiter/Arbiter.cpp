#include "Arbiter.h"

Arbiter::Arbiter(int n):Module(4){
  std::string isAvai_s,sendPackage_s,isDone_s,getPackage_s;
  isAvai_s = "isAvai";
  sendPackage_s = "sendPackage";
  isDone_s = "isDone";
  getPackage_s = "getPackage";
  for (auto i=0;i<n;i++){
    ToBeCalledList.push_back(std::bind(&Arbiter::isAvai,this,i,std::placeholders::_1));
    ToBeCalledTag.push_back(isAvai_s+"_"+std::to_string(i)+"_");
    ToBeCalledList.push_back(std::bind(&Arbiter::sendPackage,this,i,std::placeholders::_1));
    ToBeCalledTag.push_back(sendPackage_s+"_"+std::to_string(i)+"_");
    ToBeCalledList.push_back(std::bind(&Arbiter::isDone,this,i,std::placeholders::_1));
    ToBeCalledTag.push_back(isDone_s+"_"+std::to_string(i)+"_");
    ToBeCalledList.push_back(std::bind(&Arbiter::getPackage,this,i,std::placeholders::_1));
    ToBeCalledTag.push_back(getPackage_s+"_"+std::to_string(i)+"_");
  }

  
  ToCallTag.push_back("isAvai");
  ToCallTag.push_back("sendPackage");
  ToCallTag.push_back("isDone");
  ToCallTag.push_back("getPackage");
}
