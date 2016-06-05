#include "Queue.h"

Queue::Queue(int x):Module(4){
  //timeStamp=0;
  size = x;
  ToBeCalledList.push_back(std::bind(&Queue::isFull,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isFull");
  ToBeCalledList.push_back(std::bind(&Queue::sendPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("sendPackage");
  ToBeCalledList.push_back(std::bind(&Queue::isDone,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isDone");
  ToBeCalledList.push_back(std::bind(&Queue::getPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("getPackage");
    
  ToCallTag.push_back("isFull");
  ToCallTag.push_back("sendPackage");
  ToCallTag.push_back("isDone");
  ToCallTag.push_back("getPackage");
}
/*
Package Queue::IsFull(Package in){
  Package out;
  tick(Master[0].getTimeStamp()-timeStamp());
  out.push_back(new int());
  if (queue.size()<size)
    *((int*)out[0])=1;
  else
    *((int*)out[0])=0;
  return out;
}

Package Queue::IsDone(Package in){
  Package out;
  tick(Master[0].getTimeStamp()-timeStamp());
  out.push_back(new int());
  if (queue.size()==0)
    *((int*)out[0])=0;
  else
    if (done[0]==1)
      *((int*)out[0])=1;
    else
      *((int*)out[0])=0;
  return out;
}

Package Queue::sendPackage(Package in){
  Package out;
  tick(Master[0].getTimeStamp()-timeStamp());
  out.push_back(new int());
  if (queue.size()==size)
    panic("Try to send package into full queue");
  else{
    queue.push_back(in);
    done.push_back(0);
    *((int*)out[0])=1;
  }
  return out;
}

Package Queue::getPackage(Package in){
  Package out;
  tick(Master[0].getTimeStamp()-timeStamp());
  if (queue.size()==0)
    panic("Try to get package from an empty queue");
  else
    if (done[0]==0)
      panic("Try to get an undone package");
    else{
      out=queue[0];
      queue.erase(queue.begin());
      done.erase(done.begin());
    }
  return out;
}
*/
