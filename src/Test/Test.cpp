#include "Test.h"
#include <iostream>

Test1::Test1(){
  x=1.1;
  ToBeCalledList.push_back(std::bind(&Test1::add,this,std::placeholders::_1));
  ToBeCalledTag.push_back("Add");
  ToBeCalledList.push_back(std::bind(&Test1::relay,this,std::placeholders::_1));
  ToBeCalledTag.push_back("Relay");
  ToCallTag.push_back("Relay");
}

Test2::Test2(){
  x=1.2;
  ToBeCalledList.push_back(std::bind(&Test2::add,this,std::placeholders::_1));
  ToBeCalledTag.push_back("Add");
  ToBeCalledList.push_back(std::bind(&Test2::relay,this,std::placeholders::_1));
  ToBeCalledTag.push_back("Relay");
  ToCallTag.push_back("Relay");
}

Package Test1::relay(Package in){
  return ToCallList[0](in); 
}

Package Test2::relay(Package in){
  return ToCallList[0](in); 
}

Package Test1::add(Package in){
  Package out;
  out.push_back(new double());
  *((double*)out[0])=*(int*)(in[0])+*(double*)(in[1])+x;
  
  return out;
}

Package Test2::add(Package in){
  Package out;
  out.push_back(new double());
  *((double*)out.at(0))=*(int*)(in[0])+*(double*)(in[1])+x;
  
  return out; 
}
