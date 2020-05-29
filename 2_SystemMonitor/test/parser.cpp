#include "linux_parser.h"
#include "processor.h"
#include "system.h"
#include "process.h"
#include "format.h"
#include <iostream>

#define PROC_NUM  1421  
#define USER      1000
int main()
{   
    System mysystem;
    for (auto proc : mysystem.Processes()){
      std::cout << proc.Pid() << ",";
    }
    std::cout << "\n";
    std::cout << "running processes  " << mysystem.RunningProcesses() << "\n";
    std::cout << "total processes  " << mysystem.TotalProcesses() << "\n";
    std::cout << "uptime  " << mysystem.UpTime() << "\n";
    std::cout << "formateduptime  " << Format::ElapsedTime(mysystem.UpTime()) << "\n";
    
    Processor myprocessor;
    std::vector<long> myvect  = myprocessor.getProcessUseVector();
    long total = myprocessor.getTotal();
    long idle = myprocessor.getIdle();
    float utilization = myprocessor.Utilization();

    Process myprocess1(1421);
    std::cout << myprocess1.CpuUtilization() << "\n";;
    Process myprocess2(1451);
    std::cout << myprocess2.CpuUtilization() << "\n";;
    std::cout << "1421 < 1451  " << (myprocess1 < myprocess2) << "\n";

    std::cout << "os  " << LinuxParser::OperatingSystem() << "\n";
    std::cout << "kernel  "<< LinuxParser::Kernel() << "\n";
    std::cout << "memory  "       << LinuxParser::MemoryUtilization() << "\n";
    std::cout << "uptime  "       << LinuxParser::UpTime() << "\n";
    std::cout << "jiffies "       << LinuxParser::Jiffies() << "\n";
    std::cout << "uid   "       << LinuxParser::Uid(PROC_NUM) << "\n";
    std::cout << "user  "       << LinuxParser::User(USER) << "\n";
    std::cout << "ram "       << LinuxParser::Ram(PROC_NUM) << "\n";
    std::cout << "command "       << LinuxParser::Command(PROC_NUM) << "\n";
    std::cout << "CpuUtilizationProcess "       << LinuxParser::CpuUtilizationProcess(PROC_NUM) << "\n";
    std::cout << "UpTimeProcess "       << LinuxParser::UpTime(PROC_NUM) << "\n";
    
    std::cout << "woselwosel";

}