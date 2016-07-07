#include "RRArbiter.h"

RRArbiter::RRArbiter(int n):Arbiter(n){
  for (auto i = 0; i<n;i++)
    MasterTag.push_back("Anything_"+std::to_string(i)+"_");
  isAvai_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
  port = 0;
  used = 0;
}

void RRArbiter::tick(int n){
  uint64_t end = timeStamp + n;
  uint64_t minTimeStamp = end;
  if (n == 0)
    return;
  for (auto i=0;i<Master.size();i++)
    if (Master[i]->getTimeStamp()<minTimeStamp)
      minTimeStamp = Master[i]->getTimeStamp();
  if (minTimeStamp > timeStamp){
    if (used==1){
	used = 0;
	port = (port + 1) % Master.size();
	#ifdef RR_ARBITER_DEBUG
        std::cout << "RRArbiter @" << nameTag << " prioritize port " << std::dec << port << " at timestamp " << std::dec << timeStamp+1 << std::endl;
	#endif
    }
    timeStamp = minTimeStamp;
  }
  if (minTimeStamp == end){
    return;
  }else{
    while (timeStamp < end){
      for (auto ix = port; ix < port+Master.size();ix++){
	auto i = ix % Master.size();
	if (Master[i]->getTimeStamp() == timeStamp)
	  Master[i]->tick(1);
	else if (Master[i]->getTimeStamp()<timeStamp)
	  Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
      }
      if (used==1){
	used = 0;
	port = (port + 1) % Master.size();
	#ifdef RR_ARBITER_DEBUG
        std::cout << "RRArbiter " << nameTag << " prioritize port " << std::dec << port << " at timestamp " << std::dec<< timeStamp+1 << std::endl;
        #endif
      }
      timeStamp++;
      
    }
  }
}

Package RRArbiter::isAvai(int n,Package in){
  Package out;
  out.push_back(new int());
  if (Master[n]->getTimeStamp() < timeStamp){
    *(int*)out[0]=NOT_AVAILABLE;
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (auto ix=port;ix<port+Master.size();ix++){
      auto i = ix % Master.size();
      if (i == n) break;
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    }
    if (Master[n]->getTimeStamp()<timeStamp)
      *(int*)out[0]=NOT_AVAILABLE;
    else
      out = (*isAvai_p)(in);
  }
  return out;
}

Package RRArbiter::sendPackage(int n,Package in){
  Package out;
  if (Master[n]->getTimeStamp()<timeStamp){
    panic("The Slave have already move past timeStamp "+std::to_string(Master[n]->getTimeStamp()));
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (auto ix=port;ix<port+Master.size();ix++){
      auto i = ix % Master.size();
      if (i == n) break;
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    }
    if (Master[n]->getTimeStamp()<timeStamp)
      panic("The Slave have been used in this timeStamp "+std::to_string(Master[n]->getTimeStamp()));
    else{
      in.push_back(new int());
      *(int*)in.back()=n;
      out = (*sendPackage_p)(in);
      timeStamp++;
#ifdef RR_ARBITER_DEBUG
      std::cout << "RRArbiter " << nameTag << " send Package from port " << std::dec << n  << " at timestamp " << std::dec<< timeStamp << std::endl;
      printPackage(in);
      //std::cout << *(int *)in[0] << " " << *(uint*)in[1] << std:: endl;
#endif
      if (port == n)
	used = 1;
    }
  }
  return out;
}

Package RRArbiter::isDone(int n,Package in){
  Package out;
  out.push_back(new int());
  if (Master[n]->getTimeStamp() < timeStamp){
    *(int*)out[0]=NOT_DONE;
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (auto ix=port;ix<port+Master.size();ix++){
      auto i = ix % Master.size();
      if (i == n) break;
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    }
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

Package RRArbiter::getPackage(int n,Package in){
  Package out;
  if (Master[n]->getTimeStamp() < timeStamp){
    panic("The Slave have already move past timeStamp "+std::to_string(Master[n]->getTimeStamp()));
  }else{
    if (Master[n]->getTimeStamp()>timeStamp)
      tick(Master[n]->getTimeStamp()-timeStamp);
    for (auto ix=port;ix<port+Master.size();ix++){
      auto i = ix % Master.size();
      if (i == n) break;
      if (Master[i]->getTimeStamp()<=timeStamp)
	Master[i]->tick(timeStamp-Master[i]->getTimeStamp()+1);
    }
    if (Master[n]->getTimeStamp()<timeStamp)
      panic("The Slave have been used in this timeStamp "+std::to_string(Master[n]->getTimeStamp()));
    else{
      out = (*getPackage_p)(in);
      timeStamp++;
    }
    if (port == n)
      used = 1;
  }
  return out;
}
