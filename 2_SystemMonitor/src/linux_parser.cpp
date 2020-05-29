#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>  kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float MemUtilization, MemTotal, MemFree;
  string line, key, value;
  std::ifstream fileStream(kProcDirectory + kMeminfoFilename);
  if (fileStream.is_open()){
    while(std::getline(fileStream, line)){
      std::istringstream lineString(line);
      lineString >> key >> value;
      if ( key == "MemTotal:") { MemTotal = std::stof(value);}
      if ( key == "MemFree:") { MemFree = std::stof(value); break;}
    }
    MemUtilization = (MemTotal - MemFree)/MemTotal;
  }
  return MemUtilization; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long uptime, idle;
  std::ifstream fileStream(kProcDirectory + kUptimeFilename);
  if (fileStream.is_open()){
    std::getline(fileStream,line);
    std:: istringstream stringStream(line);
    stringStream >> uptime >> idle ;
  }
  return uptime; 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies(){
  long ticks = sysconf(_SC_CLK_TCK);
  return ticks * UpTime();
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

float LinuxParser::CpuUtilizationProcess(int pid){
  std::string line, value;
  int utime, stime, cutime, cstime, startime;
  std::ifstream fs(kProcDirectory +std::to_string(pid) + kStatFilename);
  if (fs.is_open()){
    std::getline(fs,line);
    std::istringstream ss(line);
    int i{1};             //we start counting on 1
    while(ss >> value){
      switch (i)
      {
      case 14:
        utime = std::stoi(value);
        break;
      case 15:
        stime = std::stoi(value);
        break;
      case 16:
        cutime = std::stoi(value);
        break;
      case 17:
        cstime = std::stoi(value);
        break;
      case 22:
        startime = std::stoi(value);
        break;

      default:
        break;
      }
    i++;
    }
  }
  int hertz = sysconf(_SC_CLK_TCK);
  int uptime = UpTime();
  int totaltime = utime + stime  + cutime + cstime; 
  float secs = (float)uptime - ((float)startime/(float)hertz);
  float cpuUsage = (100.0f * ((float)totaltime / (float)hertz))/secs;

  return cpuUsage;
}

string LinuxParser::Command(int pid[[maybe_unused]]) {
  std::string line;
  std::ifstream fs(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (fs.is_open()){
    fs >> line;
    return line;
  }
  return "";
}

string LinuxParser::Ram(int pid) {
  std::string line, type, ram, ignore;
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (fileStream.is_open()){
    while(std::getline(fileStream, line)){
      if(line.substr(0,7) == "VmSize:"){
        std::stringstream ss(line);
        ss >> type >> ram >> ignore;
        return ram;
      }
      }
      }
  return "";  
}

string LinuxParser::Uid(int pid) {
  std::string line, type, uid;
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (fileStream.is_open()){
    while(std::getline(fileStream, line)){
      if(line.substr(0,4) == "Uid:"){
        std::stringstream ss(line);
        ss >> type >> uid;
        return uid;  
      }
      }
      }
  return "";  
}

string LinuxParser::User(int pid) {
  std::string line, ignore, uid,  name;
  std::ifstream fs("/etc/passwd");
  if (fs.is_open()){
    while(std::getline(fs, line)){
      std::istringstream ss(line);
      while(std::getline(ss, name, ':')){
        std::getline(ss, ignore, ':');
        std::getline(ss, uid, ':');
        if (uid == to_string(pid)){
          return name;
        }
      }
    }
;  }
  return ""; 
}

long LinuxParser::UpTime(int pid) {
  std::string line, value;
  long starttime, uptime;
  std::ifstream fs(kProcDirectory +std::to_string(pid) + kStatFilename);
  if (fs.is_open()){
    std::getline(fs,line);
    std::istringstream ss(line);
    int i{1};             //we start counting on 1
    while(ss >> value){
      switch (i)
      {
      case 22:
        starttime = std::stoi(value);
        break;

      default:
        break;
      }
    i++;
    }
  }
  uptime = starttime/sysconf(_SC_CLK_TCK);
  return uptime;
}
