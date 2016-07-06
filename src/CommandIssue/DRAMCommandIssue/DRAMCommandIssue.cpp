#include "DRAMCommandIssue.h"

DRAMCommandIssue::DRAMCommandIssue():CommandIssue(){
  currentPackageStatus = 0;
  lastCommand = 0;
  isAvai_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
}

void DRAMCommandIssue::tick(int n){
  if (n == 0)
    return;
  else{
    uint64_t end = timeStamp + n;
    Package t;
    while (timeStamp <end){
      if (currentPackageStatus != 1)
	timeStamp = end;
      else{
	if (lastCommand == 0){
	  t = (*isAvai_p)(currentPackage);
	  if (*(int*)t[0] == AVAILABLE){
	    if (*(int*)t[1] != *(int*)currentPackage[ROW_PACKAGE_POS]){
	      if (*(int*)t[1] >=0)
		send_PR();
	      else
		send_RA();
	    }else{
	      if (*(int*)currentPackage[0] == REQUEST_READ){
		send_CR();
	      }else if (*(int*)currentPackage[0] == REQUEST_WRITE){
		send_CW();
	      }else if (*(int*)currentPackage[0] == REQUEST_REFRESH){
		send_PR();
	      }else
		panic("Invalid Request type");
	    }
	}
	}
	t = (*isDone_p)(currentPackage);
	if (*(int*)t[0] == DONE){
	  t = (*getPackage_p)(currentPackage);
	  if (lastCommand == 1){
	    currentPackageStatus = 2;
	    lastCommand = 0;
	  } 
	}
	timeStamp++;
      }
    }
  }
}

void DRAMCommandIssue::send_RA(){
  Package t1,t;
  t1= currentPackage;
  *(int*)t1[0] = COMMAND_RA;
  t = (*isAvai_p)(t1);
  if (*(int*)t[0] == AVAILABLE){
#ifdef COMMAND_ISSUE_DEBUG
    std::cout << "Command Issue " << nameTag << " send command at timeStamp " << timeStamp << std::endl;
    printPackage(t1);
#endif
    t1=(*sendPackage_p)(t1);
  }
}

void DRAMCommandIssue::send_PR(){
  Package t1,t;
  t1= currentPackage;
  *(int*)t1[0] = COMMAND_PR;
  t = (*isAvai_p)(t1);
  if (*(int*)t[0] == AVAILABLE){
#ifdef COMMAND_ISSUE_DEBUG
    std::cout << "Command Issue " << nameTag << " send command at timeStamp " << timeStamp << std::endl;
    printPackage(t1);
#endif
    t1=(*sendPackage_p)(t1);
    if (*(int*)currentPackage[0] == REQUEST_REFRESH)
      lastCommand = 1;
  }
}

void DRAMCommandIssue::send_CR(){
  Package t1,t;
  t1= currentPackage;
  *(int*)t1[0] = COMMAND_CR;
  t = (*isAvai_p)(t1);
  if (*(int*)t[0] == AVAILABLE){
#ifdef COMMAND_ISSUE_DEBUG
    std::cout << "Command Issue " << nameTag << " send command at timeStamp " << timeStamp << std::endl;
    printPackage(t1);
#endif    
    t1=(*sendPackage_p)(t1);
    lastCommand = 1;
  }
}

void DRAMCommandIssue::send_CW(){
  Package t1,t;
  t1= currentPackage;
  *(int*)t1[0] = COMMAND_CW;
  t = (*isAvai_p)(t1);
#ifdef COMMAND_ISSUE_DEBUG
    std::cout << "Command Issue " << nameTag << " send command at timeStamp " << timeStamp << std::endl;
    printPackage(t1);
#endif
  if (*(int*)t[0] == AVAILABLE){
    t1=(*sendPackage_p)(t1);
    lastCommand = 1;
  }
}


Package DRAMCommandIssue::isAvai(Package in){
  Package out;
  out.push_back(new int());
  if (timeStamp > Master[0]->getTimeStamp())
    *(int*)out[0]=NOT_AVAILABLE;
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    if (currentPackageStatus == 0)
      *(int*)out[0]=AVAILABLE;
    else
      *(int*)out[0]=NOT_AVAILABLE;
  }
  return out;
    
}

Package DRAMCommandIssue::sendPackage(Package in){
  if (timeStamp > Master[0]->getTimeStamp() || currentPackageStatus != 0)
    panic("Try to send request to an unavailable module");
  else{
    currentPackage = in;
    currentPackageStatus = 1;
    lastCommand = 0;
#ifdef COMMAND_ISSUE_DEBUG
    std::cout << "Command Issue " << nameTag << " receive request at timeStamp " << timeStamp << std::endl;
    printPackage(in);
#endif    
  }
  return in;
}

Package DRAMCommandIssue::isDone(Package){
  Package out;
  out.push_back(new int());
  if (timeStamp > Master[0]->getTimeStamp())
    *(int*)out[0]=NOT_DONE;
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    if (currentPackageStatus == 2)
      *(int*)out[0]=DONE;
    else
      *(int*)out[0]=NOT_DONE;
  }
  return out;
}

Package DRAMCommandIssue::getPackage(Package){
  if (timeStamp > Master[0]->getTimeStamp() || currentPackageStatus != 2)
    panic("Try to get an unfinished request");
  else{
    currentPackageStatus = 0;
#ifdef COMMAND_ISSUE_DEBUG
    std::cout << "Command Issue " << nameTag << " return request at timeStamp " << timeStamp << std::endl;
    printPackage(currentPackage);
#endif    
  }
  return currentPackage;  
}
