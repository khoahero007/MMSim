#include <vector>
#include <iostream>
#include "Common.h"
#include "Queue/PingQueue/PingQueue.h"
#include "Requester/TimedRequester/TimedRequester.h"


using namespace std;

int main(){
  PingQueue q(10);
  //FillRequester r("/home/khoahero007/Dropbox/Khoa/Documents/NCTU/MMSim/cputraces/random.trc");
  TimedRequester r("/home/khoahero007/Dropbox/Khoa/Documents/NCTU/MMSim/cputraces/401.bzip2");
  
  connect (&r,"isDone",&q,"isDone","Anything");
  connect (&r,"isFull",&q,"isFull","Anything");
  connect (&r,"sendPackage",&q,"sendPackage","Anything");
  connect (&r,"getPackage",&q,"getPackage","Anything");

  //auto isFull = q.getToBeCalled("isFull");
  //auto sendPackage = q.getToBeCalled("sendPackage");
  //auto isDone = q.getToBeCalled("isDone");
  //auto getPackage = q.getToBeCalled("getPackage");

  for (auto i = 0; i<100;i++){
    r.tick(1);
    cout << "TimeStamp "<< std::dec<< i << endl;
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

