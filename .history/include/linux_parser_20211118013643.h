#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// Memory
struct Memory {
  // Parts of the /proc/meminfo
  std::vector<std::string> keywords{"MemTotal:", "MemFree:", "Buffers:",
                                    "Cached:",   "Shmem:",   "SReclaimable:"};
  std::vector<float> values{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
};

// System
Memory MemoryUtilization();
long UpTime();
std::vector<int> Pids(std::vector<int>);
void TotalProcesses(int&);
void RunningProcesses(int&);
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUFields : int {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
void NumCores(int&);

std::vector<float> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif