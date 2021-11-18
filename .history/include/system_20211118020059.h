#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // DONE: See src/system.cpp
  long UpTime();                      // DONE: See src/system.cpp
  int TotalProcesses();               // DONE: See src/system.cpp
  int RunningProcesses();             // DONE: See src/system.cpp
  std::string Kernel();               // DONE: See src/system.cpp
  std::string OperatingSystem();      // DONE: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  std::string kernel_{};
  std::string os_{};
  long uptime_{0};
  int total_processes{0};
  int running_processes{0};
  std::vector<Process> processes_ = {};


Processor cpu_ = {};
  enum MemType : int {
    kMemTotal_ = 0,
    kMemFree_,
    kBuffers_,
    kCached_,
    kShmem_,
    kSReclaimable_,
  };
  LinuxParser::Memory memory 
};

#endif