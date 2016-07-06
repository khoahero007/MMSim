#include "PriorityArbiter.h"

PriorityArbiter::PriorityArbiter(int n):Arbiter(n){
  for (auto i = 0; i<n;i++)
    MasterTag.push_back("Anything_"+std::to_string(i)+"_");
  isAvai_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
}

void PriorityArbiter::tick(int n){
  uint64_t end = timeStamp + n;
  uint64_t minTimeStamp = end;
  for (auto i=0;i<Master.size();i++)
    if (Master[i]->getTimeStamp()<minTimeStamp)
      minTimeStamp = Master[i]->getTimeStamp();
  timeStamp = minTimeStamp;
  if (minTimeStamp == end){
    #ifdef PRIORITY_ARBITER_DEBUG
    std::cout << "PriorityArbiter move to timeStamp " << std::dec << timeStamp << std::endl;
    #endif
    return;
  }else{
    while (timeStamp < end){
      for (auto i = 0; i < Master.size();i++)
	if (Master[i]->getTimeStamp() == timeStamp)
	  Master[i]->tick(1);
	else if (Master[i]->getTimeStamp()<timeStamp)
	  Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
      timeStamp++;
      #ifdef PRIORITY_ARBITER_DEBUG
      std::cout << "PriorityArbiter move to timeStamp " << std::dec << timeStamp << std::endl;
      #endif
    }
  }
}

Package PriorityArbiter::isAvai(int n,Package in){
  Package out;
  out.push_back(new int());
  if (Master[n]->getTimeStamp() < timeStamp){
    *(int*)out[0]=NOT_AVAILABLE;
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (int i=0;i<n;i++)
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    if (Master[n]->getTimeStamp()<timeStamp)
      *(int*)out[0]=NOT_AVAILABLE;
    else
      out = (*isAvai_p)(in);
  }
  return out;
}

Package PriorityArbiter::sendPackage(int n,Package in){
  Package out;
  if (Master[n]->getTimeStamp()<timeStamp){
    panic("The Slave have already move past timeStamp "+std::to_string(Master[n]->getTimeStamp()));
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (int i=0;i<n;i++)
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    if (Master[n]->getTimeStamp()<timeStamp)
      panic("The Slave have been used in this timeStamp "+std::to_string(Master[n]->getTimeStamp()));
    else{
      in.push_back(new int());
      *(int*)in.back()=n;
      out = (*sendPackage_p)(in);
    }
  }
  return out;
}

Package PriorityArbiter::isDone(int n,Package in){
  Package out;
  out.push_back(new int());
  if (Master[n]->getTimeStamp() < timeStamp){
    *(int*)out[0]=NOT_DONE;
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (int i=0;i<n;i++)
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    if (Master[n]->getTimeStamp()<timeStamp)
      *(int*)out[0]=NOT_DONE;
    else{
      in.push_back(new int());
      *(int*)in.back()=n;
      out = (*isDone_p)(in);
    }
  }
  return out;
}

Package PriorityArbiter::getPackage(int n,Package in){
  Package out;
  if (Master[n]->getTimeStamp() < timeStamp){
    panic("The Slave have already move past timeStamp "+std::to_string(Master[n]->getTimeStamp()));
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (int i=0;i<n;i++)
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    if (Master[n]->getTimeStamp()<timeStamp)
      panic("The Slave have been used in this timeStamp "+std::to_string(Master[n]->getTimeStamp()));
    else
      out = (*getPackage_p)(in);
  }
  return out;
}
