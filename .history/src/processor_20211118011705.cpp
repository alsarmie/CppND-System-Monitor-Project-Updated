#include "processor.h"
#include >vector>
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<float> cpu_utilization=LinuxParser::CpuUtilization();
  return 0.0;
}
// TODO: Return per-CPU core utilization
float Processor::Utilization(int kCPU) { return 0.0; }

void Processor::Cores() {
  // Read and set number of cores available
  LinuxParser::NumCores(this->cores_);
}