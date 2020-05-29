#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid) : _pid(pid) {};

int Process::Pid() {
  return _pid;
 }

float Process::CpuUtilization() const {
  return LinuxParser::CpuUtilizationProcess(_pid);
}

string Process::Command() {
  return LinuxParser::Command(_pid);
}

string Process::Ram() {
  return LinuxParser::Ram(_pid);
}

string Process::User() {
  return LinuxParser::User(_pid); 
}

long int Process::UpTime() {
  return LinuxParser::UpTime(_pid);
}

bool Process::operator<(Process const& a) const { 
    return this->CpuUtilization() < a.CpuUtilization();
 }