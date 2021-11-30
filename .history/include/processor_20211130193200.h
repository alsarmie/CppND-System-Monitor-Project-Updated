#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
class Processor {
 public:
  Processor() {
    setCores();
    per_core_values = new double[cores_][10]();
    prev_per_core_values = new double[cores_][10]();
  }
  ~Processor() {
    delete per_core_values;
    delete prev_per_core_values;
  }
  double Utilization();  // DONE: See src/processor.cpp
  double Utilization(int);
  void setCores();
  auto& getCores() const { return cores_; }
  // DONE: Declare any necessary private members
 private:
  int cores_{-1};  // To discard the aggregate cpu info.
  // For aggregate CPU utilization
  double agg_cpu_values[10] = {};
  double prev_agg_cpu_values[10] = {};

  // For per-CPU utilization
  double (*per_core_values)[10];
  double (*prev_per_core_values)[10];
};

#endif