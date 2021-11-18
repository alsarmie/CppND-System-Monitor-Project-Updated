#include "processor.h"

#include <vector>

#include "linux_parser.h"
using namespace LinuxParser;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  CpuUtilization(this->agg_cpu_values);
  prev_idle_ = prev_agg_cpu_values[CPUFields::kIdle_] +
               prev_agg_cpu_values[CPUFields::kIOwait_];
  idle_=
  //  History
  prev_agg_cpu_values = agg_cpu_values;
  return 0.0;
}
// TODO: Return per-CPU core utilization
float Processor::Utilization(int kCPU) { return 0.0; }

void Processor::Cores() {
  // Read and set number of cores available
  NumCores(this->cores_);
}