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
  filestream.close();
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  stream.close();
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  for (const auto& filename : fs::directory_iterator(kProcDirectory))
    if (fs::is_directory(filename)) {
      string directory(filename.path());
      directory.erase(0, kProcDirectory.length());
      if (std::all_of(directory.begin(), directory.end(), isdigit)) {
        int pid = stoi(directory);
        pids.push_back(pid);
      }
    }
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  // This implementation uses the formula:
  // Used Mem = (MemTotal-(MemFree + Buffers + Cached))/MemTotal <- not in
  // percentage as that is handled by ncurses_display.cpp
  // Cached=Cached + SReclaimable - Shmem

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string line, key, unit;
  float value{0.0};
  float mem_utilization{0.0}, total_cached{0.0};
  Memory memory;
  int idx{0};

  if (stream.is_open()) {
    // Get the values first, then we make the calculation.
    while (getline(stream, line)) {
      // Maybe redundant, but it ensures we are reading the correct element.
      std::istringstream ss(line);
      ss >> key >> value >> unit;
      auto it = std::find(memory.keywords.begin(), memory.keywords.end(), key);
      if (it != memory.keywords.end()) {
        idx = it - memory.keywords.begin();
        memory.values[idx] = value;
      }
    }
  }
  //    0           1           2         3        4          5
  //"MemTotal", "MemFree", "Buffers", "Cached", "Shmem","SReclaimable"
  total_cached = memory.values[3] + memory.values[5] - memory.values[4];
  mem_utilization = (memory.values[0] -
                     (memory.values[1] + memory.values[2] + total_cached)) /
                    memory.values[0];
  stream.close();
  return mem_utilization;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime{0};
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    getline(stream, line);
    uptime = stof(line.substr(0, line.find(" ")));
  }
  stream.close();
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int processes{0};
  string line;
  const string keyword{"processes"};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      if (line.find(keyword) != string::npos)
        processes = stoi(line.substr(keyword.length() + 1));
    }
  }
  stream.close();
  return processes;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int procs_running{0};
  string line;
  const string keyword{"procs_running"};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      if (line.find(keyword) != string::npos)
        procs_running = stoi(line.substr(keyword.length() + 1));
    }
  }
  stream.close();
  return procs_running;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }
