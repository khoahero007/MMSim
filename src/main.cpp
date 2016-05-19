#include <vector>
#include <iostream>
#include "Common.h"
#include "Test/Test.h"


using namespace std;

int main(){
  //Module m;
  //Test1 t;
  //Test2 t;
  //funct<Package(Package)> k1,k2;
  //k1 = Test1.Connect
  Test1 t1;
  Test2 t2;
  
  connect(&t1,"Relay",&t2,"Add");
  
  connect(&t2,"Relay",&t1,"Add");
 
  auto t1_f = t1.getToBeCalled("Relay");
 
  auto t2_f = t2.getToBeCalled("Relay");
  
  Package p;
  p.push_back(new int());
  p.push_back(new double());
  *((double*)p[1])=10;
  *((int*)p[0])=1;
  //cout << "HEHE" << endl;
  Package p1 =t1_f (p);
  Package p2 =t2_f (p);
  cout << *((double*)p1[0]) << endl;
  cout << *((double*)p2[0]) << endl;
}

