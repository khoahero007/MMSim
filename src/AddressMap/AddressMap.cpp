#include "../Common.h"

Package AddressMap::getMap(Package in){
  Package out;
  out = in;
  uint64_t add = out[1];
  out.erase(out.begin()+1);
  int row,column,bank,rank,channel;
  add = add >> 3;
  row = add & 0x3FF;
  add = add >> 10;
  column = add & 0x3FFF;
  add = add >> 14;
  bank = add & 0x3;
  add = add >> 3;
  rank = add & 1;
  channel = 0;
  out.insert(out.begin()+1,0);
  out.insert(out.begin()+1,0);
  out.insert(out.begin()+1,0);
  out.insert(out.begin()+1,0);
  out.insert(out.begin()+1,0);
  out[1]=row;
  out[2]=column;
  out[3]=bank;
  out[4]=rank;
  out[5]=channel;
  return out;
}
