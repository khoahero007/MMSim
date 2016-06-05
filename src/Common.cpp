#include "Common.h"
#include <iostream>

Module::Module(int x){
  timeStamp = 0;
  ToCallList.resize(x);
}


CallBackFunc Module::getToBeCalled(std::string T){
  std::vector<std::string>::iterator it = std::find (ToBeCalledTag.begin(),ToBeCalledTag.end(),T);
  if (it !=ToBeCalledTag.end()){
    auto pos = std::distance(ToBeCalledTag.begin(),it);
    auto ret = ToBeCalledList.at(pos);
    
    ToBeCalledTag.erase(ToBeCalledTag.begin()+pos);
    ToBeCalledList.erase(ToBeCalledList.begin()+pos);
    return ret;
  }else{
    throw std::invalid_argument("Can not find Tag in ToBeCalledTag");
  }
}


void Module::setToCall(CallBackFunc f, std::string T){
  std::vector<std::string>::iterator it = std::find (ToCallTag.begin(),ToCallTag.end(),T);
  if (it != ToCallTag.end()){
    auto pos = std::distance(ToCallTag.begin(),it);
    ToCallList[pos]=f;;
  }else{
    throw std::invalid_argument("Can not find Tag in ToCallTag");
  }
}

void Module::addMaster(Module* m, std::string T){
  std::vector<std::string>::iterator it = std::find (MasterTag.begin(),MasterTag.end(),T);
  if (it != MasterTag.end()){
    auto pos = std::distance(MasterTag.begin(),it);
    if (Master.size()<=pos) Master.resize(pos+1);
    Master[pos]=m;
  }else{
    //throw std::invalid_argument("Can not find Tag in MasterTag");
  }
}

uint64_t Module::getTimeStamp(){
  return timeStamp;
}

void Module::tick(int n){
  timeStamp = timeStamp + n;
  panic("This module is not final yet");
}

void Module::Diagnose(){
  for (auto s : SubModules){
    s.Diagnose();
  };
}

std::vector<std::string> Module::getMasterList(){
  return MasterTag;
}

void connect(Module *master,std::string MTag, Module *slave, std::string STag, std::string MasterTag){
  try{
    auto f = slave->getToBeCalled(STag);
    master->setToCall(f,MTag);
    slave->addMaster(master,MasterTag);
  }catch(const std::exception &e){
    panic(e.what());
  }
}

void panic(std::string e){
  std::cerr << e << std::endl;
  exit(-1);
}
