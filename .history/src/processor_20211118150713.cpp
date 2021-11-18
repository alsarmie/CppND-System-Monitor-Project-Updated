#include "processor.h"

#include <vector>

#include "linux_parser.h"
using namespace LinuxParser;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  CpuUtilization(this->agg_cpu_values);
  prev_idle_ = prev_agg_cpu_values[CPUFields::kIdle_] +
               prev_agg_cpu_values[CPUFields::kIOwait_];
  idle_ =
      agg_cpu_values[CPUFields::kIdle_] + agg_cpu_values[CPUFields::kIOwait_];
  prev_non_idle_ = prev_agg_cpu_values[CPUFields::kUser_] +
                   prev_agg_cpu_values[CPUFields::kNice_] +
                   prev_agg_cpu_values[CPUFields::kSystem_] +
                   prev_agg_cpu_values[CPUFields::kIRQ_] +
                   prev_agg_cpu_values[CPUFields::kSoftIRQ_] +
                   prev_agg_cpu_values[CPUFields::kSteal_];
  non_idle_ =
      agg_cpu_values[CPUFields::kUser_] + agg_cpu_values[CPUFields::kNice_] +
      agg_cpu_values[CPUFields::kSystem_] + agg_cpu_values[CPUFields::kIRQ_] +
      agg_cpu_values[CPUFields::kSoftIRQ_] + agg_cpu_values[CPUFields::kSteal_];
  prev_total_ = prev_idle_ + prev_non_idle_;
  total_ = idle_ + non_idle_;
  delta_total_ = total_ - prev_total_;
  delta_idle_ = idle_ - prev_idle_;

  //  History
  prev_agg_cpu_values = agg_cpu_values;
  return (delta_total_ - delta_idle_) / delta_total_;
}
// TODO: Return per-CPU core utilization
float Processor::Utilization(int kCPU) { return 0.0; }

void Processor::Cores() {
  // Read and set number of cores available
  NumCores(this->cores_);
}
auto& Processor::getCores() { return this->cores_; }