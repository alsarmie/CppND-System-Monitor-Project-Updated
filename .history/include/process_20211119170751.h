#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid) { cpu_ = CpuUtilization(); }
  int Pid();                         // DONE: See src/process.cpp
  std::string User();                // DONE: See src/process.cpp
  std::string Command();             // DONE: See src/process.cpp
  float CpuUtilization();            // DONE: See src/process.cpp
  std::string Ram();                 // DONE: See src/process.cpp
  long UpTime();                     // DONE: See src/process.cpp
  bool operator<(Process& a) const;  // DONE: See src/process.cpp
  auto& getCPU() const;

  // DONE: Declare any necessary private members
 private:
  int pid_;
  float cpu_util{0.0};
};

#endif