#ifndef COMMAND_ISSUE_H_
#define COMMAND_ISSUE_H_

#include "../Common.h"

class CommandIssue: public Module{
 public:
  CommandIssue();
 protected:
  virtual Package isAvai(Package){};
  virtual Package sendPackage(Package){};
  virtual Package isDone(Package){};
  virtual Package getPackage(Package){};
};


#endif //COMMAND_ISSUE_H_
