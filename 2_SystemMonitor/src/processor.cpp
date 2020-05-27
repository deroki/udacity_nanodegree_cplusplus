#include "processor.h"
#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization

using namespace LinuxParser;


void Processor::parseProcessUseVector(){
  std::vector<long> procVector;
  std::string line;
  std::string valueString;
      std::ifstream fileStream (kProcDirectory + kStatFilename);
  if (fileStream.is_open()){
      std::getline(fileStream, line);
      std::istringstream stringStream(line);
      while (stringStream >> valueString){
        if (valueString == "cpu"){ continue;}
        procVector.push_back(std::stol(valueString));
      }
  }
  _processUseVector = procVector;
}

std::vector<long> Processor::getProcessUseVector(){
  return _processUseVector;
}

long Processor::getTotal(){
  long total {0};
  for (long num : _processUseVector){
    total += num;
  }
  return total;
}

long Processor::getIdle(){
  if(_processUseVector.size() > 4){
    return _processUseVector[3] + _processUseVector[4];
  }
  return 0;
}

float Processor::Utilization() {
  long total, total_0, idle, idle_0;
  parseProcessUseVector();
  total_0 = getTotal();
  idle_0 = getIdle();
  sleep(1);
  parseProcessUseVector();
  total = getTotal();
  idle = getIdle();
     return (float)((total - total_0)- (idle - idle_0)) / float(total - total_0);
      }