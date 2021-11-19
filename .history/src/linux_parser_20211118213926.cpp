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
  }
  filestream.close();
}

// DONE: An example of how to read data from the filesystem
void LinuxParser::Kernel(string& kernel) {
  string os, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  stream.close();
}

// BONUS: Update this to use std::filesystem
void LinuxParser::Pids(vector<int>& pids) {
  for (const auto& filename : fs::directory_iterator(kProcDirectory))
    if (fs::is_directory(filename)) {
      string directory(filename.path());
      directory.erase(0, kProcDirectory.length());
      if (std::all_of(directory.begin(), directory.end(), isdigit)) {
        int pid = stoi(directory);
        pids.push_back(pid);
      }
    }
}

// DONE: Read and return the system memory utilization
void LinuxParser::MemoryUtilization(LinuxParser::Memory& memory) {
  // This function should read only the memory values, the actual calculation
  // should be done in system.cpp
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string line, key, unit;
  int idx{0};
  float value{0.0};
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
  stream.close();
}

// DONE: Read and return the system uptime
void LinuxParser::UpTime(long& uptime) {
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    getline(stream, line);
    uptime = stof(line.substr(0, line.find(" ")));
  }
  stream.close();
}

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return ActiveJiffies() + IdleJiffies(); }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line;
  string value;
  long activeJiffies{0};
  int count{0};
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    getline(stream, line);
    std::istringstream ss(line);
    while(ss>>value){
      count
    }
     

  }
  stream.close();
  return 0;
}

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line;
  long jiffies[10] = {};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    getline(stream, line);
    line = line.substr(3);
    std::istringstream ss(line);
    ss >> jiffies[CPUFields::kUser_] >> jiffies[CPUFields::kNice_] >>
        jiffies[CPUFields::kSystem_] >> jiffies[CPUFields::kIdle_] >>
        jiffies[CPUFields::kIOwait_] >> jiffies[CPUFields::kIRQ_] >>
        jiffies[CPUFields::kSoftIRQ_] >> jiffies[CPUFields::kSteal_] >>
        jiffies[CPUFields::kGuest_] >> jiffies[CPUFields::kGuestNice_];
  }
  stream.close();
  return jiffies[CPUFields::kUser_] + jiffies[CPUFields::kNice_] +
         jiffies[CPUFields::kSystem_] + jiffies[CPUFields::kIRQ_] +
         jiffies[CPUFields::kSoftIRQ_] + jiffies[CPUFields::kSteal_];
}

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line;
  long jiffies[10] = {};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    getline(stream, line);
    line = line.substr(3);
    std::istringstream ss(line);
    ss >> jiffies[CPUFields::kUser_] >> jiffies[CPUFields::kNice_] >>
        jiffies[CPUFields::kSystem_] >> jiffies[CPUFields::kIdle_] >>
        jiffies[CPUFields::kIOwait_] >> jiffies[CPUFields::kIRQ_] >>
        jiffies[CPUFields::kSoftIRQ_] >> jiffies[CPUFields::kSteal_] >>
        jiffies[CPUFields::kGuest_] >> jiffies[CPUFields::kGuestNice_];
  }
  stream.close();
  return jiffies[CPUFields::kIdle_] + jiffies[CPUFields::kIOwait_];
}

// DONE: Read and return the aggregate CPU values
void LinuxParser::CpuUtilization(float (&values)[10]) {
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    getline(stream, line);  // first line contains the aggregate information.
    line = line.substr(3);
    std::istringstream ss(line);
    ss >> values[CPUFields::kUser_] >> values[CPUFields::kNice_] >>
        values[CPUFields::kSystem_] >> values[CPUFields::kIdle_] >>
        values[CPUFields::kIOwait_] >> values[CPUFields::kIRQ_] >>
        values[CPUFields::kSoftIRQ_] >> values[CPUFields::kSteal_] >>
        values[CPUFields::kGuest_] >> values[CPUFields::kGuestNice_];
  }
  stream.close();
}

void LinuxParser::CpuUtilization(float (&values)[10], int kCPU) {
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      if (line.find("cpu" + to_string(kCPU)) != std::string::npos) {
        line = line.substr(3);
        std::istringstream ss(line);
        ss >> values[CPUFields::kUser_] >> values[CPUFields::kNice_] >>
            values[CPUFields::kSystem_] >> values[CPUFields::kIdle_] >>
            values[CPUFields::kIOwait_] >> values[CPUFields::kIRQ_] >>
            values[CPUFields::kSoftIRQ_] >> values[CPUFields::kSteal_] >>
            values[CPUFields::kGuest_] >> values[CPUFields::kGuestNice_];
      }
    }
  }
  stream.close();
}

// DONE: Read and return the total number of processes
void LinuxParser::TotalProcesses(int& processes) {
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
}

// DONE: Read and return the number of running processes
void LinuxParser::RunningProcesses(int& running_processes) {
  string line;
  const string keyword{"procs_running"};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      if (line.find(keyword) != string::npos)
        running_processes = stoi(line.substr(keyword.length() + 1));
    }
  }
  stream.close();
}

void LinuxParser::NumCores(int& cores) {
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
    while (getline(stream, line))
      if (line.find("cpu") != std::string::npos) cores++;

  stream.close();
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
