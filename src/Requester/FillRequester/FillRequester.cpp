#include "FillRequester.h"

FillRequester::FillRequester(std::string filename):Requester(){
  fileStream.open(filename.c_str(),std::ifstream::in);
  finish = 0;
  isFull_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
}

void FillRequester::tick(int n){
  if (finish == 1)
    timeStamp = timeStamp+n;
  else{
    Package p,t;
    uint64_t   end = timeStamp + n;
    while (timeStamp<end){
      p=(*isFull_p)(t);
      if (*(int*)p[0]==0){
	p=readPackage();
	if (*(int*)p[0]==-1){
	  finish = 1;
	  timeStamp = end;
	  fileStream.close();
	  return;
	}else{
	  p.erase(p.begin());
	  #ifdef FILL_REQUESTER_DEBUG
	  std::cout << "Send Package at " << std::dec << timeStamp << std::endl;
	  std::cout << *(int*)p[0] << " " << std::hex<< *(uint64_t*)p[1] << std::endl;
	  #endif
	  p=(*sendPackage_p)(p);
	}
      }
      p=(*isDone_p)(t);
      if (*(int*)p[0]==1){
	p=(*getPackage_p)(t);
	#ifdef FILL_REQUESTER_DEBUG
	std::cout << "Get Package at " << std::dec << timeStamp << std::endl;
	std::cout << *(int*)p[0] << " " << std::hex<< *(uint64_t*)p[1] << std::endl;
	#endif
      }
      timeStamp++;
    }
  }
}

Package FillRequester::readPackage(){
  Package p;
  if (fileStream.eof()){
    p.push_back(new int());
    *(int*)p[0]=-1;
  }else{
    p.push_back(new int());
    p.push_back(new int());
    p.push_back(new uint64_t());
    *(int*)p[0]=1;
    std::string s;
    int i;
    fileStream >> std::hex >> *(uint64_t*)p[2];
    fileStream >> s;
    fileStream >> i;
    if (s.compare("W")==0){
      *(int*)p[1]=REQUEST_WRITE;
    }else{
      *(int*)p[1]=REQUEST_READ;
    }
  }
  return p;
}

int FillRequester::isFinish(){
  return finish;
}
