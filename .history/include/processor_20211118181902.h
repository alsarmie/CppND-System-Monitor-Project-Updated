#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
class Processor {
 public:
  Processor() {
    setCores();
    per_core_values = new float[cores_][10]();
    prev_per_core_values = new float[cores_][10]();
  }
  ~Processor() {
    delete per_core_values;
    delete prev_per_core_values;
  }
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int);
  void setCores();
  int getCores();
  // TODO: Declare any necessary private members
 private:
  int cores_{-1};  // To discard the aggregate cpu info.
  // For aggregate CPU utilization
  float agg_cpu_values[10]= {};
  float prev_agg_cpu_values[10]= {};

  // For per-CPU utilization
  float (*per_core_values)[10];
  float (*prev_per_core_values)[10];


};

#endif