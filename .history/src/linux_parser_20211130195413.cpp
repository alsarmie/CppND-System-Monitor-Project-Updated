#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
using std::stof;
using std::string;
using std::to_string;
using std::vector;
namespace fs = std::filesystem;
/*
This implementation uses the following StackOverflow approach for the per-PID
CPU calculation:
https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599

*/
// DONE: An example of how to read data from the filesystem
void LinuxParser::OperatingSystem(string& os) {
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
          os = value;
        }
      }
    }
    filestream.close();
  }
}

// DONE: An example of how to read data from the filesystem
void LinuxParser::Kernel(string& kernel) {
  string os{""};
  string version{""};
  string line{""};
  std::ifstream filestream(kProcDirectory + kVersionFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
    filestream.close();
  }
}

// BONUS: Update this to use std::filesystem
void LinuxParser::Pids(vector<int>& pids) {
  for (const auto& filename : fs::directory_iterator(kProcDirectory))
    if (fs::is_directory(filename)) {
      string directory(filename.path());
      directory.erase(0, kProcDirectory.length());
      if (std::all_of(directory.begin(), directory.end(), isdigit)) {
        int pid = stoi(directory);
        pids.emplace_back(pid);
      }
    }
}

// DONE: Read and return the system memory utilization
void LinuxParser::MemoryUtilization(LinuxParser::Memory& memory) {
  // This function should read only the memory values, the actual calculation
  // should be done in system.cpp
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  string line{""};
  string key{""};
  string unit{""};
  int idx{0};
  double value{0.0};
  if (filestream.is_open()) {
    // Get the values first, then we make the calculation.
    while (getline(filestream, line)) {
      // Maybe redundant, but it ensures we are reading the correct element.
      std::istringstream ss(line);
      ss >> key >> value >> unit;
      auto it = std::find(memory.keywords.begin(), memory.keywords.end(), key);
      if (it != memory.keywords.end()) {
        idx = it - memory.keywords.begin();
        memory.values[idx] = value;
      }
    }
    filestream.close();
  }
}

// DONE: Read and return the system uptime
void LinuxParser::UpTime(long& uptime) {
  string line{""};
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    uptime = stol(line.substr(0, line.find(" ")));
    filestream.close();
  }
}

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return ActiveJiffies() + IdleJiffies(); }

// DONE: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line{""};
  string value{""};
  long activeJiffies{0};
  int count{0};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream ss(line);
    while (ss >> value) {
      if (count >= 13 && count <= 16) activeJiffies += stol(value);
      count++;
    }
    filestream.close();
  }

  return activeJiffies;
}

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line{""};
  long jiffies[10] = {};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    line = line.substr(3);
    std::istringstream ss(line);
    ss >> jiffies[CPUFields::kUser_] >> jiffies[CPUFields::kNice_] >>
        jiffies[CPUFields::kSystem_] >> jiffies[CPUFields::kIdle_] >>
        jiffies[CPUFields::kIOwait_] >> jiffies[CPUFields::kIRQ_] >>
        jiffies[CPUFields::kSoftIRQ_] >> jiffies[CPUFields::kSteal_] >>
        jiffies[CPUFields::kGuest_] >> jiffies[CPUFields::kGuestNice_];
    filestream.close();
  }

  return jiffies[CPUFields::kUser_] + jiffies[CPUFields::kNice_] +
         jiffies[CPUFields::kSystem_] + jiffies[CPUFields::kIRQ_] +
         jiffies[CPUFields::kSoftIRQ_] + jiffies[CPUFields::kSteal_];
}

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line{""};
  long jiffies[10] = {};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    line = line.substr(3);
    std::istringstream ss(line);
    ss >> jiffies[CPUFields::kUser_] >> jiffies[CPUFields::kNice_] >>
        jiffies[CPUFields::kSystem_] >> jiffies[CPUFields::kIdle_] >>
        jiffies[CPUFields::kIOwait_] >> jiffies[CPUFields::kIRQ_] >>
        jiffies[CPUFields::kSoftIRQ_] >> jiffies[CPUFields::kSteal_] >>
        jiffies[CPUFields::kGuest_] >> jiffies[CPUFields::kGuestNice_];
  }
  filestream.close();
  return jiffies[CPUFields::kIdle_] + jiffies[CPUFields::kIOwait_];
}

// DONE: Read and return the aggregate CPU values
void LinuxParser::CpuUtilization(double (&values)[10]) {
  string line{""};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream,
            line);  // first line contains the aggregate information.
    line = line.substr(3);
    std::istringstream ss(line);
    ss >> values[CPUFields::kUser_] >> values[CPUFields::kNice_] >>
        values[CPUFields::kSystem_] >> values[CPUFields::kIdle_] >>
        values[CPUFields::kIOwait_] >> values[CPUFields::kIRQ_] >>
        values[CPUFields::kSoftIRQ_] >> values[CPUFields::kSteal_] >>
        values[CPUFields::kGuest_] >> values[CPUFields::kGuestNice_];
    filestream.close();
  }
}

void LinuxParser::CpuUtilization(double (&values)[10], int kCPU) {
  string line{""};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      if (line.find("cpu" + to_string(kCPU)) != std::string::npos) {
        line = line.substr(3);  // We discard the cpu tag .
        std::istringstream ss(line);
        ss >> values[CPUFields::kUser_] >> values[CPUFields::kNice_] >>
            values[CPUFields::kSystem_] >> values[CPUFields::kIdle_] >>
            values[CPUFields::kIOwait_] >> values[CPUFields::kIRQ_] >>
            values[CPUFields::kSoftIRQ_] >> values[CPUFields::kSteal_] >>
            values[CPUFields::kGuest_] >> values[CPUFields::kGuestNice_];
      }
    }
    filestream.close();
  }
}

// DONE: Read and return the total number of processes
void LinuxParser::TotalProcesses(int& processes) {
  string line{""};
  const string keyword{"processes"};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line))
      if (line.find(keyword) != string::npos)
        processes = stoi(line.substr(keyword.length() + 1));

    filestream.close();
  }
}

// DONE: Read and return the number of running processes
void LinuxParser::RunningProcesses(int& running_processes) {
  string line{""};
  const string keyword{"procs_running"};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line))
      if (line.find(keyword) != string::npos)
        running_processes = stoi(line.substr(keyword.length() + 1));

    filestream.close();
  }
}

void LinuxParser::NumCores(int& cores) {
  string line{""};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line))
      if (line.find("cpu") != std::string::npos) cores++;

    filestream.close();
  }
}

// DONE: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string command;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    getline(filestream, command);
    filestream.close();
  }
  return command;
}

// DONE: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line{""};
  string tag{""};
  string units{""};
  double ram{0.0};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      if (line.find("VmSize:") != std::string::npos) {
        std::istringstream ss(line);
        ss >> tag >> ram >> units;
      }
    }
    filestream.close();
  }
  line = to_string(ram / 1000);
  line =
      line.substr(0, line.find(".") + 3);  // Truncate RAM value to 3 decimals
  return line;
}

// DONE: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line{""};
  string tag{""};
  string uid;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      if (line.find("Uid:") != std::string::npos) {
        std::istringstream ss(line);
        ss >> tag >> uid;
      }
    }
    filestream.close();
  }
  return uid;
}

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  string line;
  string user;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      if (line.find(uid) != std::string::npos) {
        user = line.substr(0, line.find(":"));
      }
    }
    filestream.close();
  }
  return user;
}

// DONE: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  string value;
  double start_time{0};
  int count{0};
  long sys_time{0};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream ss(line);
    // Only field #22 is relevant.
    while (ss >> value && count++ < 20)
      ;
    ss >> start_time;
  }
  LinuxParser::UpTime(sys_time);
  return sys_time - (long)(start_time / sysconf(_SC_CLK_TCK));
}
