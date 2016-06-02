#include <vector>
#include <iostream>
#include "Common.h"
#include "Queue/PingQueue/PingQueue.h"


using namespace std;

int main(){
  PingQueue q(10);
  Module r;

  auto isFull = q.getToBeCalled("isFull");
  auto sendPackage = q.getToBeCalled("sendPackage");
  auto isDone = q.getToBeCalled("isDone");
  auto getPackage = q.getToBeCalled("getPackage");

  q.addMaster(&r,"Anything");
  Package t;
  for (auto i=0;i<100;i++){
    
    Package p = isFull(t);
    if (*(int*)p[0]==0){
      p=sendPackage(p);
      cout << "Send package at " << i << endl;
    }
    p = isDone(t);
    if (*(int*)p[0]==1){
      p=getPackage(p);
      cout << "Get package at " << i << endl;
    }
    r.tick(1);
  }
  
  /*
  Test1 t1;
  Test2 t2;
  
  connect(&t1,"Relay",&t2,"Add");
  
  connect(&t2,"Relay",&t1,"Add");
 
  auto t1_f = t1.getToBeCalled("Relay");
 
  auto t2_f = t2.getToBeCalled("Relay");
  
  Package p;
  p.push_back(new int());
  p.push_back(new double());
  *((double*)p[1])=10;
  *((int*)p[0])=1;
  //cout << "HEHE" << endl;
  Package p1 =t1_f (p);
  Package p2 =t2_f (p);
  cout << *((double*)p1[0]) << endl;
  cout << *((double*)p2[0]) << endl;*/
}

