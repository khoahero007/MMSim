#include "PingQueue.h"

PingQueue::PingQueue(int x):Queue(x){
  //Queue::Queue(x);
  last = 0;
  MasterTag.push_back("Anything");
}

void PingQueue::tick(int n){
  if (n==0)
    return;
  else{
    if (timeStamp+n>=last+DELAY && queue.size()>0)
      done[0]=1;
    timeStamp = timeStamp+n;
  }
}

Package PingQueue::isFull(Package in){
  Package out;
  tick(Master[0]->getTimeStamp()-timeStamp);
  out.push_back(new int());
  if (queue.size()<size)
    *((int*)out[0])=0;
  else
    *((int*)out[0])=1;
  return out;
}

Package PingQueue::isDone(Package in){
  Package out;
  tick(Master[0]->getTimeStamp()-timeStamp);
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

Package PingQueue::sendPackage(Package in){
  Package out;
  tick(Master[0]->getTimeStamp()-timeStamp);
  out.push_back(new int());
  if (queue.size()==size)
    panic("Try to send package into full queue");
  else{
    queue.push_back(in);
    done.push_back(0);
    *((int*)out[0])=1;
    if (queue.size()==1)
      last = timeStamp;
  }
  return out;
}

Package PingQueue::getPackage(Package in){
  Package out;
  tick(Master[0]->getTimeStamp()-timeStamp);
  if (queue.size()==0)
    panic("Try to get package from an empty queue");
  else
    if (done[0]==0)
      panic("Try to get an undone package");
    else{
      out=queue[0];
      queue.erase(queue.begin());
      done.erase(done.begin());
      last=timeStamp;
    }
  return out;
}
