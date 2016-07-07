#include "FillRequester.h"

FillRequester::FillRequester(std::string filename):Requester(){
  fileStream.open(filename.c_str(),std::ifstream::in);
  finish = 0;
  nextPackageValid = 0;
  isAvai_p      = &ToCallList[0];
  sendPackage_p = &ToCallList[1];
  isDone_p      = &ToCallList[2];
  getPackage_p  = &ToCallList[3];
}

void FillRequester::tick(int n){
  if (finish == 1)
    timeStamp = timeStamp+n;
  else{
    Package p;

    uint64_t   end = timeStamp + n;
    while (timeStamp<end){
      //Read new Package if needed
      if (nextPackageValid == 0){
	nextPackage = readPackage();
	if (nextPackage[0]==-1){
	  finish = 1;
	  timeStamp = timeStamp +n;
	  fileStream.close();
	  return;
	}
	nextPackageValid = 1;
	nextPackage.erase(nextPackage.begin());
	nextPackage = AddressMap::getMap(nextPackage);
      }
      //Priority send new Package over get finished Package
      //Check available and send Package
      p=(*isAvai_p)(nextPackage);
      if (p[0]==AVAILABLE){
	#ifdef FILL_REQUESTER_DEBUG
	std::cout << "FillRequester " << nameTag << " send Package at " << std::dec << timeStamp << std::endl;
	printPackage(nextPackage);
	//std::cout << *(int*)nextPackage[0] << " " << std::hex<< *(uint64_t*)nextPackage[1] << std::endl;
	#endif
	p=(*sendPackage_p)(nextPackage);
	sentPackage.push_back(nextPackage);
	nextPackageValid = 0;
      }
      //Check sentPackage have been finished and get it back
      //Get Package in order with the sent order
      if (sentPackage.size()>0){
	p=(*isDone_p)(sentPackage[0]);
	if (p[0]==DONE){
	  p=(*getPackage_p)(sentPackage[0]);
#ifdef FILL_REQUESTER_DEBUG
	  std::cout << "FillRequester " << nameTag << " get Package at " << std::dec << timeStamp << std::endl;
	  printPackage(nextPackage);
	  //std::cout << *(int*)p[0] << " " << std::hex<< *(uint64_t*)p[1] << std::endl;
#endif
	  sentPackage.erase(sentPackage.begin());
	}
      }
      timeStamp++;
    }
  }
}

Package FillRequester::readPackage(){
  Package p;
  if (fileStream.eof()){
    p.push_back(-1);
  }else{
    p.push_back(0);
    p.push_back(0);
    p.push_back(0);
    p.push_back(0);
    p[0]=1;
    std::string s;
    int i;
    fileStream >> std::hex >> p[2];
    fileStream >> s;
    fileStream >> i;
    if (s.compare("W")==0){
      p[1]=REQUEST_WRITE;
    }else{
      p[1]=REQUEST_READ;
    }
    p[3]=0;
  }
  return p;
}

int FillRequester::isFinish(){
  return finish;
}
