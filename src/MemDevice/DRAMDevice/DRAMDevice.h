#ifndef DRAM_DEVICE_H_
#define DRAM_DEVICE_H_

#include "../MemDevice.h"

class DRAMDevice:public MemDevice{
 public:
  DRAMDevice(std::string,int);
  void tick(int);
 protected:
  Package isAvai(Package);
  Package sendPackage(Package);
  Package isDone(Package);
  Package getPackage(Package);
  void RA(Package);
  void CR(Package);
  void CW(Package);
  void PR(Package);
  int tBurst,tCAS,tCMD,tCWD,tDQS,tFAW,tRAS,tRC,tRCD,tRFC,tRRD,tRP,tWR;
  std::vector<int> row_buffer;
  uint64_t RA_avai,CR_avai,CW_avai,PR_avai,doneTimeStamp;
  std::vector<uint64_t> tFAW_array;
};

#endif
