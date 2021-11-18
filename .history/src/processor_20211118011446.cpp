#include "processor.h"

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    
    return 0.0; }
// TODO: Return per-CPU core utilization
float Processor::Utilization(int kCPU) { return 0.0; }

void Processor::Cores() {
  // Read and set number of cores available
  LinuxParser::NumCores(this->cores_);
}