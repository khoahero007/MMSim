#ifndef COMMON_H_   /* Include guard */
#define COMMON_H_

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <algorithm>
#include "Request.h"
#include "DEBUG_FLAG.h"
class Module;
typedef std::vector<void*> Package;
typedef std::function<Package(Package)> CallBackFunc ;
typedef std::vector<CallBackFunc> CBFuncList;
				      
				      
class Module{
 public:
  CallBackFunc getToBeCalled(std::string);
  void setToCall(CallBackFunc,std::string);
  void addMaster(Module*,std::string);
  void Diagnose();
  std::vector<std::string> getMasterList();
  uint64_t getTimeStamp();
  virtual void tick(int);
  Module(int);
 protected:
  uint64_t timeStamp;
  CBFuncList ToBeCalledList;
  std::vector<std::string> ToCallTag;
  
  CBFuncList ToCallList;
  std::vector<std::string> ToBeCalledTag;
  
  std::vector<Module*> Master;
  std::vector<std::string> MasterTag;
  
  std::vector<Module> SubModules;
};

void connect(Module*,std::string,Module*,std::string,std::string);
void panic(std::string);

//Package NULL_PACKAGE;

#endif // COMMON_H_

/**********************HOW TO IMPLEMENT CALLBACK****************
class A{
 public:
  int x;
  std::function <int(int)>k;
  int add(int y){
    x=x+y;
    return x;
  }
  
  A(){
    x=0;
    k = std::bind(&A::add,this,std::placeholders::_1);
  }
    
};

class B{
 public:
  //int x;
  std::function <int(int)> k;
  int test(int x){
    return k(x);
  }
  B(A *a){
    std::cout << a << std::endl;
    //k = std::bind(&A::add,a,std::placeholders::_1);
    k=a->k;
  }
};

int man(){
  
  A *t1=new A();
  B *t2=new B(t1);

  cout << t1 << endl;
  cout << t1->add(3) << endl;
  cout << t1->x << endl;
  //cout << t1->x << endl;
  cout << t2->test(10) << endl;
  cout << t1->x << endl;
  
}
****************************************************************/
