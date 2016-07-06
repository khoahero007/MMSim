#include <vector>
#include <iostream>
#include "Common.h"
#include "Queue/PingQueue/PingQueue.h"
#include "Requester/TimedRequester/TimedRequester.h"
#include "Requester/FillRequester/FillRequester.h"
#include "Arbiter/PriorityArbiter/PriorityArbiter.h"
#include "Arbiter/RRArbiter/RRArbiter.h"
#include "Mapping/Mapping.h"
#include "CommandIssue/DRAMCommandIssue/DRAMCommandIssue.h"
#include "MemDevice/DRAMDevice/DRAMDevice.h"


using namespace std;

int main(){

  DRAMDevice mem0("/home/khoahero007/Dropbox/Khoa/Documents/NCTU/MMSim/cputraces/Timing",4);
  cout << "Generated Mem Device " << mem0.getNameTag() << endl;
  DRAMCommandIssue ci;
  cout << "Generated CommandIssue " << ci.getNameTag() << endl;
  
  TimedRequester r0("/home/khoahero007/Dropbox/Khoa/Documents/NCTU/MMSim/cputraces/401.bzip2");
  cout << "Generated TimedRequester " << r0.getNameTag() << endl;
  TimedRequester r1("/home/khoahero007/Dropbox/Khoa/Documents/NCTU/MMSim/cputraces/403.gcc");
  cout << "Generated TimedRequester " << r1.getNameTag() << endl;
  FillRequester r2("/home/khoahero007/Dropbox/Khoa/Documents/NCTU/MMSim/cputraces/random.trc");
  cout << "Generated FillRequester " << r2.getNameTag() << endl;
  /*
  vector<int> map;
  map.push_back(0);
  map.push_back(1);
  map.push_back(1);
  map.push_back(0);
  
  Mapping m(RANK_PACKAGE_POS,map);
  cout << "Generated Mapping " << m.getNameTag() << endl;
  */
  RRArbiter a(3);
  cout << "Generated RRArbiter " << a.getNameTag() << endl;

  connect (&ci,"isDone",&mem0,"isDone","Command");
  connect (&ci,"isAvai",&mem0,"isAvai","Command");
  connect (&ci,"sendPackage",&mem0,"sendPackage","Command");
  connect (&ci,"getPackage",&mem0,"getPackage","Command");
  
  connect (&a,"isDone",&ci,"isDone","Request");
  connect (&a,"isAvai",&ci,"isAvai","Request");
  connect (&a,"sendPackage",&ci,"sendPackage","Request");
  connect (&a,"getPackage",&ci,"getPackage","Request");

  connect (&r0,"isDone",&a,"isDone_0_","Anything_0_");
  connect (&r0,"isAvai",&a,"isAvai_0_","Anything_0_");
  connect (&r0,"sendPackage",&a,"sendPackage_0_","Anything_0_");
  connect (&r0,"getPackage",&a,"getPackage_0_","Anything_0_");

  connect (&r1,"isDone",&a,"isDone_1_","Anything_1_");
  connect (&r1,"isAvai",&a,"isAvai_1_","Anything_1_");
  connect (&r1,"sendPackage",&a,"sendPackage_1_","Anything_1_");
  connect (&r1,"getPackage",&a,"getPackage_1_","Anything_1_");

  connect (&r2,"isDone",&a,"isDone_2_","Anything_2_");
  connect (&r2,"isAvai",&a,"isAvai_2_","Anything_2_");
  connect (&r2,"sendPackage",&a,"sendPackage_2_","Anything_2_");
  connect (&r2,"getPackage",&a,"getPackage_2_","Anything_2_");
  /*
  connect (&m,"isDone_0_",&q0,"isDone","Anything");
  connect (&m,"isAvai_0_",&q0,"isAvai","Anything");
  connect (&m,"sendPackage_0_",&q0,"sendPackage","Anything");
  connect (&m,"getPackage_0_",&q0,"getPackage","Anything");

  connect (&m,"isDone_1_",&q1,"isDone","Anything");
  connect (&m,"isAvai_1_",&q1,"isAvai","Anything");
  connect (&m,"sendPackage_1_",&q1,"sendPackage","Anything");
  connect (&m,"getPackage_1_",&q1,"getPackage","Anything");
  
  connect (&m,"isDone_2_",&q2,"isDone","Anything");
  connect (&m,"isAvai_2_",&q2,"isAvai","Anything");
  connect (&m,"sendPackage_2_",&q2,"sendPackage","Anything");
  connect (&m,"getPackage_2_",&q2,"getPackage","Anything");

  connect (&m,"isDone_3_",&q3,"isDone","Anything");
  connect (&m,"isAvai_3_",&q3,"isAvai","Anything");
  connect (&m,"sendPackage_3_",&q3,"sendPackage","Anything");
  connect (&m,"getPackage_3_",&q3,"getPackage","Anything");
  */
  //auto isFull = q.getToBeCalled("isFull");
  //auto sendPackage = q.getToBeCalled("sendPackage");
  //auto isDone = q.getToBeCalled("isDone");
  //auto getPackage = q.getToBeCalled("getPackage");

  for (auto i = 0; i<10000;i++){
    //ut << "TimeStamp "<< std::dec<< i << endl;
    r0.tick(1);
    //cout << "At "<< std::dec << a.getTimeStamp() << " prioritized port " << a.getPort() << endl;
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

