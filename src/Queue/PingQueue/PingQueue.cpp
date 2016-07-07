#include "PingQueue.h"

PingQueue::PingQueue(int x,int d):Queue(x){
  //Queue::Queue(x);
  last = 0;
  delay = d;
  MasterTag.push_back("Anything");
}

void PingQueue::tick(int n){
  if (n==0)
    return;
  else{
    uint64_t end = timeStamp + n;
    while (timeStamp <end){
      if (timeStamp >= last + delay && queue.size()>0)
	done[0]=DONE;
      timeStamp++;
      if (timeStamp >= Master[0]->getTimeStamp() && timeStamp < end)
	Master[0]->tick(timeStamp - Master[0]->getTimeStamp()+1);
    }
    
  }
}

Package PingQueue::isAvai(Package in){
  Package out;
  
  out.push_back(0);
  if (Master[0]->getTimeStamp()<timeStamp)
    out[0]=NOT_AVAILABLE;
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    if (queue.size()<size)
      out[0]=AVAILABLE;
    else
      out[0]=NOT_AVAILABLE;
  }
  return out;
}

Package PingQueue::isDone(Package in){
  Package out;

  out.push_back(0);
  if (Master[0]->getTimeStamp()<timeStamp)
    out[0]=NOT_AVAILABLE;
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    if (queue.size()==0)
      out[0]=NOT_DONE;
    else if (done[0]==1 && (*(int*)in.back() == *(int*)queue[0].back()))
      out[0]=DONE;
    else
      out[0]=NOT_DONE;
  }
  return out;
}

Package PingQueue::sendPackage(Package in){
  Package out;
  if (Master[0]->getTimeStamp()<timeStamp)
    panic("Try to send package into unavailable queue");
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    out.push_back(0);
    if (queue.size()==size)
      panic("Try to send package into full queue");
    else{
      queue.push_back(in);
      done.push_back(0);
      out[0]=1;
      if (queue.size()==1)
	last = timeStamp;
      tick(1);
    }
  }
  return out;
}

Package PingQueue::getPackage(Package in){
  Package out;
  if (Master[0]->getTimeStamp()<timeStamp)
    panic("Try to get package from unavailable queue");
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    if (queue.size()==0)
      panic("Try to get package from an empty queue");
    else if (done[0]==NOT_DONE)
      panic("Try to get an undone package");
    else{
      out=queue[0];
      queue.erase(queue.begin());
      done.erase(done.begin());
      last=timeStamp;
      tick(1);
    }
  }
  return out;
}
