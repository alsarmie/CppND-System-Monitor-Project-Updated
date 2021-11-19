#include "processor.h"

#include <vector>

#include "linux_parser.h"
using namespace LinuxParser;
/*
This implementation uses the algorithm proposed here:
https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

*/
// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  float prev_idle_{0.0};
  float idle_{0.0};
  float prev_non_idle_{0.0};
  float non_idle_{0.0};
  float prev_total_{0.0};
  float total_{0.0};
  float delta_total_{0.0};
  float delta_idle_{0.0};

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

  if (delta_total_ > 0) return (delta_total_ - delta_idle_) / delta_total_;
  return 0.0;
}
// DONE: Return per-CPU core utilization
float Processor::Utilization(int kCore) {
    //This implentation could have used the Jiffies functions from LinuxParser
  float prev_idle_{0.0};
  float idle_{0.0};
  float prev_non_idle_{0.0};
  float non_idle_{0.0};
  float prev_total_{0.0};
  float total_{0.0};
  float delta_total_{0.0};
  float delta_idle_{0.0};

  // For per-CPU utilization
  CpuUtilization(per_core_values[kCore], kCore);

  prev_idle_ = prev_per_core_values[kCore][CPUFields::kIdle_] +
               prev_per_core_values[kCore][CPUFields::kIOwait_];
  idle_ = per_core_values[kCore][CPUFields::kIdle_] +
          per_core_values[kCore][CPUFields::kIOwait_];
  prev_non_idle_ = prev_per_core_values[kCore][CPUFields::kUser_] +
                   prev_per_core_values[kCore][CPUFields::kNice_] +
                   prev_per_core_values[kCore][CPUFields::kSystem_] +
                   prev_per_core_values[kCore][CPUFields::kIRQ_] +
                   prev_per_core_values[kCore][CPUFields::kSoftIRQ_] +
                   prev_per_core_values[kCore][CPUFields::kSteal_];
  non_idle_ = per_core_values[kCore][CPUFields::kUser_] +
              per_core_values[kCore][CPUFields::kNice_] +
              per_core_values[kCore][CPUFields::kSystem_] +
              per_core_values[kCore][CPUFields::kIRQ_] +
              per_core_values[kCore][CPUFields::kSoftIRQ_] +
              per_core_values[kCore][CPUFields::kSteal_];
  prev_total_ = prev_idle_ + prev_non_idle_;
  total_ = idle_ + non_idle_;
  delta_total_ = total_ - prev_total_;
  delta_idle_ = idle_ - prev_idle_;

  //  History
  std::copy(std::begin(per_core_values[kCore]),
            std::end(per_core_values[kCore]),
            std::begin(prev_per_core_values[kCore]));
  // This should not occur, but to avoid division by 0
  if (delta_total_ > 0) return (delta_total_ - delta_idle_) / delta_total_;
  return 0.0;
}

void Processor::setCores() {
  // Read and set number of cores available
  NumCores(cores_);
}
int Processor::getCores() { return cores_; }