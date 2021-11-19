#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu() {

  return cpu_;
}
// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  LinuxParser::Pids(pids_);
  for(auto pid:pids_)
    processes_.emplace_back(Process(pid));
  
  processes_
  return processes_; }

// DONE: Return the system's kernel identifier (string)
string System::Kernel() {
  LinuxParser::Kernel(kernel_);
  return kernel_;
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization() {
  // This implementation uses the formula:
  // Used Mem = (MemTotal-(MemFree + Buffers + Cached))/MemTotal <- not in
  // percentage as that is handled by ncurses_display.cpp
  // Cached=Cached + SReclaimable - Shmem

  float mem_utilization{0.0}, total_cached{0.0};
  LinuxParser::MemoryUtilization(memory_);
  //    0           1           2         3        4          5
  //"MemTotal", "MemFree", "Buffers", "Cached", "Shmem","SReclaimable"
  total_cached = memory_.values[MemType::kCached_] +
                 memory_.values[MemType::kSReclaimable_] -
                 memory_.values[MemType::kShmem_];
  mem_utilization = (memory_.values[MemType::kMemTotal_] -
                     (memory_.values[MemType::kMemFree_] +
                      memory_.values[MemType::kBuffers_] + total_cached)) /
                    memory_.values[MemType::kMemTotal_];
  return mem_utilization;
}

// DONE: Return the operating system name
string System::OperatingSystem() {
  LinuxParser::OperatingSystem(os_);
  return os_;
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() {
  LinuxParser::RunningProcesses(running_processes);
  return running_processes;
}

// DONE: Return the total number of processes on the system
int System::TotalProcesses() {
  LinuxParser::TotalProcesses(total_processes);
  return total_processes;
}

// DONE: Return the number of seconds since the system started running
long System::UpTime() {
  LinuxParser::UpTime(uptime_);
  return uptime_;
}