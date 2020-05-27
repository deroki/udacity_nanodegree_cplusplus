#include "linux_parser.h"
#include "processor.h"
#include <iostream>

int main()
{   
    Processor myprocessor;
    std::vector<long> myvect  = myprocessor.getProcessUseVector();
    long total = myprocessor.getTotal();
    long idle = myprocessor.getIdle();
    float utilization = myprocessor.Utilization();

    std::cout << LinuxParser::OperatingSystem() << "\n";
    std::cout << LinuxParser::Kernel() << "\n";
    std::cout << LinuxParser::MemoryUtilization() << "\n";
    std::cout << LinuxParser::UpTime() << "\n";
    std::cout << LinuxParser::Jiffies() << "\n";
    std::cout << "woselwosel";

}