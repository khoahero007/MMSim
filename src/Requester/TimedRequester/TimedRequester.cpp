#include "TimedRequester.h"

TimedRequester::TimedRequester(std::string filename):Requester(){
  fileStream.open(filename.c_str(),std::ifstream::in);
  finish = 0;
  timeStampToSend = 0;
  readPackage();
  if (toSend.size()==0){
    finish = 1;
    fileStream.close();
  }
  toSend[0] = AddressMap::getMap(toSend[0]);
  if (toSend.size()==2)
    toSend[1] = AddressMap::getMap(toSend[1]);
  isAvai_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
}

void TimedRequester::tick(int n){
  if (finish == 1)
    timeStamp = timeStamp + n;
  else{
    Package p;
    uint64_t end = timeStamp +n;
    while (timeStamp<end){
      if (timeStamp >= timeStampToSend && finish==0){
	if (toSend.size()==0){
	  readPackage();
	  if (toSend.size()==0){
	    finish = 1;
	    fileStream.close();
	    return;
	  }
	  toSend[0] = AddressMap::getMap(toSend[0]);
	  if (toSend.size()==2)
	    toSend[1] = AddressMap::getMap(toSend[1]);
	}
	p=(*isAvai_p)(toSend[0]);
	if (p[0]==AVAILABLE){;
	  #ifdef TIMED_REQUESTER_DEBUG
	  std::cout << "TimedRequester " << nameTag << " send Package at " << std::dec << timeStamp << std::endl;
	  printPackage(toSend[0]);
	  //std::cout << *(int*)toSend[0][0] << " " << std::hex<< *(uint64_t*)toSend[0][1] << std::endl;
	  #endif
	  p=(*sendPackage_p)(toSend[0]);
	  sentPackage.push_back(toSend[0]);
	  toSend.erase(toSend.begin());
	}
      }
      if (sentPackage.size()>0){
	p=(*isDone_p)(sentPackage[0]);
	if (p[0]==DONE){
	  p=(*getPackage_p)(sentPackage[0]);
#ifdef TIMED_REQUESTER_DEBUG
	  std::cout << "TimeRequester " << nameTag << " get Package at " << std::dec << timeStamp << std::endl;
	  printPackage(toSend[0]);
	  //std::cout << *(int*)p[0] << " " << std::hex<< *(uint64_t*)p[1] << std::endl;
#endif
	  sentPackage.erase(sentPackage.begin());
	}
      }
      timeStamp++;
    }
  }
}


void TimedRequester::readPackage(){

  if (fileStream.eof()){
    finish = 1;
    return;
  }else{
    Package p;

    std::string line;
    std::getline(fileStream,line);
    std::stringstream linestream1(line);
    std::stringstream linestream2(line);

    int a;
    uint64_t b,c;

    if (linestream1 >> a >> b >> c){
      p.push_back(0);
      p.push_back(0);
      p.push_back(0);
      p[0]=a;
      p[1]=b;
      p[2]=c;
    }else{
      linestream2 >> a >> b;
      p.push_back(0);
      p.push_back(0);
      p[0]=a;
      p[1]=b;      
    }
    
    timeStampToSend = timeStamp + p[0];
    Package readPackage;
    Package writePackage;
    readPackage.push_back(0);
    readPackage[0]=REQUEST_READ;
    readPackage.push_back(p[1]);
    readPackage.push_back(0);
    readPackage[2]=0;
    toSend.push_back(readPackage);
    if (p.size()==3){
      writePackage.push_back(0);
      writePackage[0]=REQUEST_WRITE;
      writePackage.push_back(p[2]);
      writePackage.push_back(0);
      writePackage[2]=0;
      toSend.push_back(writePackage);
    }
  }
}

int TimedRequester::isFinish(){
  return finish;
}
