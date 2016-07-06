#include "CommandIssue.h"

CommandIssue::CommandIssue():Module(4){
  ToBeCalledList.push_back(std::bind(&CommandIssue::isAvai,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isAvai");
  ToBeCalledList.push_back(std::bind(&CommandIssue::sendPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("sendPackage");
  ToBeCalledList.push_back(std::bind(&CommandIssue::isDone,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isDone");
  ToBeCalledList.push_back(std::bind(&CommandIssue::getPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("getPackage");
    
  ToCallTag.push_back("isAvai");
  ToCallTag.push_back("sendPackage");
  ToCallTag.push_back("isDone");
  ToCallTag.push_back("getPackage");

  MasterTag.push_back("Request");
}
