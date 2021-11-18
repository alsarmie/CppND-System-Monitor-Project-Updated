#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
  //Processor cpu;
  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() {
  // This implementation uses the formula:
  // Used Mem = (MemTotal-(MemFree + Buffers + Cached))/MemTotal <- not in
  // percentage as that is handled by ncurses_display.cpp
  // Cached=Cached + SReclaimable - Shmem

  float mem_utilization{0.0}, total_cached{0.0};
  LinuxParser::Memory memory = LinuxParser::MemoryUtilization();
  //    0           1           2         3        4          5
  //"MemTotal", "MemFree", "Buffers", "Cached", "Shmem","SReclaimable"
  total_cached = memory.values[MemType::kCached_] +
                 memory.values[MemType::kSReclaimable_] -
                 memory.values[MemType::kShmem_];
  mem_utilization = (memory.values[MemType::kMemTotal_] -
                     (memory.values[MemType::kMemFree_] +
                      memory.values[MemType::kBuffers_] + total_cached)) /
                    memory.values[MemType::kMemTotal_];
  return mem_utilization;
}

// DONE: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long System::UpTime() { return LinuxParser::UpTime(); }