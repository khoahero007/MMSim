#ifndef MAPPING_H_
#define MAPPING_H_

#include "../Common.h"
#include <iostream>

class Mapping: public Module{
 public:
  Mapping(int,std::vector<int>);
  void tick(int);
 protected:
  Package isAvai(Package);
  Package sendPackage(Package);
  Package isDone(Package);
  Package getPackage(Package);
  int map_port(Package);
  std::vector<int> map;
  int mapProp;
};

#endif //MAPPING_H_
