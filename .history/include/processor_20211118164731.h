#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <unordered_map>
class Processor {
 public:
  Processor() { setCores(); }
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int);
  void setCores();
  int getCores();
  // TODO: Declare any necessary private members
 private:
  int cores_{-1};  // To discard the aggregate cpu info.
  // For aggregate CPU utilization
  float agg_cpu_values[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float prev_agg_cpu_values[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // For per-CPU utilization

  float prev_idle_{0.0};
  float idle_{0.0};
  float prev_non_idle_{0.0};
  float non_idle_{0.0};
  float prev_total_{0.0};
  float total_{0.0};
  float delta_total_{0.0};
  float delta_idle_{0.0};
  float cpu_utilization_{0.0};
};

#endif