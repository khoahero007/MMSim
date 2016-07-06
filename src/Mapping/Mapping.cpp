#include "Mapping.h"

Mapping::Mapping(int mapProp_in,std::vector<int> map_in):Module(map_in.size()*4){
  std::string isAvai_s,sendPackage_s,isDone_s,getPackage_s;
  isAvai_s = "isAvai";
  sendPackage_s = "sendPackage";
  isDone_s = "isDone";
  getPackage_s = "getPackage";
  
  ToBeCalledList.push_back(std::bind(&Mapping::isAvai,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isAvai");
  ToBeCalledList.push_back(std::bind(&Mapping::sendPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("sendPackage");
  ToBeCalledList.push_back(std::bind(&Mapping::isDone,this,std::placeholders::_1));
  ToBeCalledTag.push_back("isDone");
  ToBeCalledList.push_back(std::bind(&Mapping::getPackage,this,std::placeholders::_1));
  ToBeCalledTag.push_back("getPackage");
  
  map = map_in;
  mapProp = mapProp_in;
  for (auto i=0;i<map.size();i++){
    ToCallTag.push_back(isAvai_s+"_"+std::to_string(i)+"_");
    ToCallTag.push_back(sendPackage_s+"_"+std::to_string(i)+"_");
    ToCallTag.push_back(isDone_s+"_"+std::to_string(i)+"_");
    ToCallTag.push_back(getPackage_s+"_"+std::to_string(i)+"_");
  }

  MasterTag.push_back("Anything");
}

void Mapping::tick(int n){
  timeStamp = timeStamp + n;
}

int Mapping::map_port(Package in){
  return *(int*)in[mapProp];
}

Package Mapping::isAvai(Package in){
  tick(Master[0]->getTimeStamp()-timeStamp);
  int m=map_port(in);
  Package out,p;
  out.push_back(new int());
  *(int*)out[0]=AVAILABLE;
  for (auto i=0;i<map.size();i++)
    if (map[i]==m){
      p=ToCallList[4*i](in);
      if (*(int*)p[0]==NOT_AVAILABLE){
	*(int*)out[0]=NOT_AVAILABLE;
	return out;
      }	
    }
  return out;
}

Package Mapping::sendPackage(Package in){
  tick(Master[0]->getTimeStamp()-timeStamp);
  int m=map_port(in);
  Package out;
  for (auto i=0;i<map.size();i++)
    if (map[i]==m){
      out = ToCallList[4*i+1](in);
#ifdef MAPPING_DEBUG
      std::cout << "Mapping " << nameTag << " route package to port " << std::dec << i << " at timestamp " << std::dec << timeStamp << std::endl;
#endif	//MAPPING_DEBUG
    }
  return out;
}

Package Mapping::isDone(Package in){
  tick(Master[0]->getTimeStamp()-timeStamp);
  int m=map_port(in);
  Package out,p;
  out.push_back(new int());
  *(int*)out[0]=DONE;
  for (auto i=0;i<map.size();i++)
    if (map[i]==m){
      p=ToCallList[4*i+2](in);
      if (*(int*)p[0]==NOT_DONE){
	*(int*)out[0]=NOT_DONE;
	return out;
      }	
    }
  return out;
}

Package Mapping::getPackage(Package in){
  tick(Master[0]->getTimeStamp()-timeStamp);
  int m=map_port(in);
  Package out,p;
  out = in;
  for (auto i=0;i<map.size();i++)
    if (map[i]==m){
      p = ToCallList[4*i+3](in);
      for (auto i = in.size(); i < p.size(); i++)
	out.push_back(p[i]);
#ifdef MAPPING_DEBUG
      std::cout << "Mapping " << nameTag << " get package from port " << std::dec << i << " at timestamp " << std::dec << timeStamp << std::endl;
#endif	//MAPPING_DEBUG
    }
  return out;
}
