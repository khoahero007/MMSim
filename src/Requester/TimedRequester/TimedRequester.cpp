#include "TimedRequester.h"

TimedRequester::TimedRequester(std::string filename):Requester(){
  fileStream.open(filename.c_str(),std::ifstream::in);
  finish = 0;
  isFull_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
}

void TimedRequester::tick(int n){
  if (finish == 1)
    timeStamp = timeStamp + n;
  else{
    Package p,t;
    uint64_t end = timeStamp +n;
    while (timeStamp<end){
      p=(*isFull_p)(t);
      if (*(int*)p[0]==0){
	if (toSend.size()==0)
	  readPackage();
	if (toSend.size()==0){
	  finish = 1;
	  timeStamp = end;
	  fileStream.close();
	  return;
	}

	if (timeStamp >=timeStampToSend){
	  #ifdef TIMED_REQUESTER_DEBUG
          std::cout << "Send Package at " << std::dec << timeStamp << std::endl;
          std::cout << *(int*)toSend[0][0] << " " << std::hex<< *(uint64_t*)toSend[0][1] << std::endl;
	  #endif
	  p=(*sendPackage_p)(toSend[0]);
	  toSend.erase(toSend.begin());
	}
      }
      p=(*isDone_p)(t);
      if (*(int*)p[0]==1){
	p=(*getPackage_p)(t);
	#ifdef TIMED_REQUESTER_DEBUG
	std::cout << "Get Package at " << std::dec << timeStamp << std::endl;
	std::cout << *(int*)p[0] << " " << std::hex<< *(uint64_t*)p[1] << std::endl;
	#endif
      }
      timeStamp++;
    }
  }
}


void TimedRequester::readPackage(){

  if (fileStream.eof()){
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
      p.push_back(new int());
      p.push_back(new uint64_t());
      p.push_back(new uint64_t());
      *(int*)p[0]=a;
      *(uint64_t*)p[1]=b;
      *(uint64_t*)p[2]=c;
    }else{
      linestream2 >> a >> b;
      p.push_back(new int());
      p.push_back(new uint64_t());
      *(int*)p[0]=a;
      *(uint64_t*)p[1]=b;      
    }
    
    timeStampToSend = timeStamp + *(int*)p[0];
    Package readPackage;
    Package writePackage;
    readPackage.push_back(new int());
    *(int*)readPackage[0]=REQUEST_READ;
    readPackage.push_back(p[1]);
    toSend.push_back(readPackage);
    if (p.size()==3){
      writePackage.push_back(new int());
      *(int*)writePackage[0]=REQUEST_WRITE;
      writePackage.push_back(p[2]);
      toSend.push_back(writePackage);
    }
  }
}

int TimedRequester::isFinish(){
  return finish;
}
