#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() { return pid_; }
auto& Process::getCPU() const { return cpu_; }
// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  float total_time{0.0};
  float seconds{0.0};
  long sys_uptime{0};
  float ()
  LinuxParser::UpTime(sys_uptime);
  total_time = LinuxParser::ActiveJiffies(pid_);
  seconds = (float)sys_uptime - LinuxParser::UpTime(pid_);

  return (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  
}

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DONE: Return the age of this process (in seconds)
long Process::UpTime() { return LinuxParser::UpTime(pid_); }

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process& a) const {
  return this->getCPU() < a.getCPU();
}