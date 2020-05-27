#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <unistd.h>

class Processor {
 public:
  void parseProcessUseVector();     //parsed  /proc/stat file for aggregate CPU
  std::vector<long> getProcessUseVector();
  long getTotal();                              // sum of all jiffies from the boot
  long getIdle();                               // sum of all jiffier idle from the boot
  float Utilization();  // TODO: See src/processor.cpp
  
  // TODO: Declare any necessary private members
 private:
  std::vector<long> _processUseVector {0};
};

#endif