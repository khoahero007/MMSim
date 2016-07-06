#include "DRAMDevice.h"
#include <fstream>
#include <iostream>

DRAMDevice::DRAMDevice(std::string file,int bank_num):MemDevice(){
  std::ifstream fileStream;
  std::string s;
  int t;
  fileStream.open(file.c_str(),std::ifstream::in);
  while (!fileStream.eof()){
    fileStream >> s >> t;
    
    if (s ==  "tBurst")
      tBurst = t;
    else if (s == "tCAS")
      tCAS = t;
    else if (s == "tCMD")
      tCMD = t;
    else if (s == "tCWD")
      tCWD = t;
    else if (s == "tDQS")
      tDQS = t;
    else if (s == "tFAW")
      tFAW = t;
    else if (s == "tRAS")
      tRAS = t;
    else if (s == "tRC")
      tRC = t;
    else if (s == "tRCD")
      tRCD = t;
    else if (s == "tRFC")
      tRFC = t;
    else if (s == "tRRD")
      tRRD = t;
    else if (s == "tRP")
      tRP = t;
    else if (s == "tWR")
      tWR = t;
    else
      panic("Wrong timing Parameter");
  }
  RA_avai = 0;
  CR_avai = 0;
  CW_avai = 0;
  PR_avai = 0;
  tFAW_array.resize(4,0);
  row_buffer.resize(bank_num,-1);
  fileStream.close();
}


void DRAMDevice::tick(int n){
  timeStamp = timeStamp + n;
}

void DRAMDevice::RA(Package in){
  doneTimeStamp = timeStamp + tCMD + tRAS;
  RA_avai = doneTimeStamp;
  CR_avai = doneTimeStamp;
  CW_avai = doneTimeStamp;
  PR_avai = doneTimeStamp - tCMD;
  //Row to Row Delay
  if (timeStamp + tRRD > RA_avai)
    RA_avai = timeStamp + tRRD;
  //Four Activation Window
  for (auto i=0;i<3;i++)
    tFAW_array[i]=tFAW_array[i+1];
  tFAW_array[3]=timeStamp;
  if (tFAW_array[0]+tFAW > RA_avai)
    RA_avai = timeStamp + tFAW;
  //Set row buffer
  if (*(int*)in[BANK_PACKAGE_POS]==-1){
    for (auto i = 0; i<row_buffer.size();i++)
      row_buffer[i]=*(int*)in[ROW_PACKAGE_POS];
  }else{
    row_buffer[*(int*)in[BANK_PACKAGE_POS]] = *(int*)in[ROW_PACKAGE_POS];
  }
}

void DRAMDevice::PR(Package in){
  doneTimeStamp = timeStamp + tCMD + tRP;
  RA_avai = doneTimeStamp;
  CR_avai = doneTimeStamp;
  CW_avai = doneTimeStamp;
  PR_avai = doneTimeStamp;
  //Reset row buffer
  if (*(int*)in[BANK_PACKAGE_POS]==-1){
    for (auto i = 0; i<row_buffer.size();i++)
      row_buffer[i]=*(int*)in[ROW_PACKAGE_POS];
  }else{
    row_buffer[*(int*)in[BANK_PACKAGE_POS]] = *(int*)in[ROW_PACKAGE_POS];
  }
}

void DRAMDevice::CW(Package in){
  doneTimeStamp = timeStamp + tCWD + tBurst+ tWR;
  RA_avai = doneTimeStamp;
  CR_avai = doneTimeStamp;
  CW_avai = doneTimeStamp;
  PR_avai = doneTimeStamp;
}

void DRAMDevice::CR(Package in){
  doneTimeStamp = timeStamp + tCAS + tBurst;
  RA_avai = doneTimeStamp;
  CR_avai = doneTimeStamp;
  CW_avai = doneTimeStamp;
  PR_avai = doneTimeStamp;
}

Package DRAMDevice::isAvai(Package in){
  tick(Master[0]->getTimeStamp()-timeStamp);
  Package out;
  out.push_back(new int());
  out.push_back(new int());
  if (*(int*)in[0] == REQUEST_READ || *(int*)in[0] == REQUEST_WRITE || *(int*)in[0] == REQUEST_REFRESH){
    *(int*)out[0] = AVAILABLE;
    *(int*)out[1] = row_buffer[*(int*)in[BANK_PACKAGE_POS]];
  }else if (*(int*)in[0] == COMMAND_RA){
    if (timeStamp >= RA_avai)
      *(int*)out[0] = AVAILABLE;
    else
      *(int*)out[0] = NOT_AVAILABLE;
  }else if (*(int*)in[0] == COMMAND_PR){
    if (timeStamp >= PR_avai)
      *(int*)out[0] = AVAILABLE;
    else
      *(int*)out[0] = NOT_AVAILABLE;
  }else if (*(int*)in[0] == COMMAND_CW){
    if (timeStamp >= CW_avai)
      *(int*)out[0] = AVAILABLE;
    else
      *(int*)out[0] = NOT_AVAILABLE;
  }else if (*(int*)in[0] == COMMAND_CR){
    if (timeStamp >= CR_avai)
      *(int*)out[0] = AVAILABLE;
    else
      *(int*)out[0] = NOT_AVAILABLE;
  }else{
    panic("Invalid package for mem device");
  }
  return out;
}

Package DRAMDevice::sendPackage(Package in){
  tick(Master[0]->getTimeStamp()-timeStamp);
  if (*(int*)in[0] == COMMAND_RA){
    if (timeStamp < RA_avai)
      panic("Unable to receive RA command");
    RA(in);
  }else if (*(int*)in[0] == COMMAND_PR){
    if (timeStamp < PR_avai)
      panic("Unable to receive PR command");
    PR(in);
  }else if (*(int*)in[0] == COMMAND_CW){
    if (timeStamp < CW_avai)
      panic("Unable to receive CW command");
    CW(in);
  }else if (*(int*)in[0] == COMMAND_CR){
    if (timeStamp < CR_avai)
      panic("Unable to receive CR command");
    CR(in);
  }else{
    panic("Invalid command for mem device");
  }
  return in;
}

Package DRAMDevice::isDone(Package in){
  Package out = in;
  if (Master[0]->getTimeStamp()<timeStamp){
    *(int*)out[0]=NOT_DONE;
  }else{
    tick(Master[0]->getTimeStamp()-timeStamp);
    if (doneTimeStamp > timeStamp)
      *(int*)out[0]=NOT_DONE;
    else
      *(int*)out[0]=DONE;
  }
  return out;
}

Package DRAMDevice::getPackage(Package in){
  if (Master[0]->getTimeStamp()<timeStamp)
    panic("Try to get package from unavailable mem device");
  else{
    tick(Master[0]->getTimeStamp()-timeStamp);
  }
  return in;
}
