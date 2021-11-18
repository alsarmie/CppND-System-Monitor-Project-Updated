#include "processor.h"

#include <vector>

#include "linux_parser.h"
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  float prev_idle_{0.0};
  float idle_{0.0};
  float prev_non_idle_{0.0};
  float non_idle_{0.0};
  float prev_total_{0.0};
  float total_{0.0};
  float delta_total_{0.0};
  float delta_idle_{0.0};
  float cpu_utilization_{0.0};

  CpuUtilization(agg_cpu_values);
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
  std::copy(std::begin(agg_cpu_values), std::end(agg_cpu_values),
            std::begin(prev_agg_cpu_values));

  return (delta_total_ - delta_idle_) / delta_total_;
}
// TODO: Return per-CPU core utilization
float Processor::Utilization(int kCPU) {
  float prev_idle_{0.0};
  float idle_{0.0};
  float prev_non_idle_{0.0};
  float non_idle_{0.0};
  float prev_total_{0.0};
  float total_{0.0};
  float delta_total_{0.0};
  float delta_idle_{0.0};
  float cpu_utilization_{0.0};

  // For per-CPU utilization

  float(*prev_per_core_values)[10];

  CpuUtilization(per_core_values[kCPU], kCPU);

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
  std::copy(std::begin(agg_cpu_values), std::end(agg_cpu_values),
            std::begin(prev_agg_cpu_values));

  return (delta_total_ - delta_idle_) / delta_total_;
}

void Processor::setCores() {
  // Read and set number of cores available
  NumCores(cores_);
}
int Processor::getCores() { return cores_; }