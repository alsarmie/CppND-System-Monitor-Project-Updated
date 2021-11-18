#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>

class Processor {
 public:
  Processor() { Cores(); }
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int);
  void Cores();
  // TODO: Declare any necessary private members
 private:
  int cores_{-1};  // To discard the aggregate cpu info.
  std::vector<float> agg_cpu_values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<float> prev_agg_cpu_values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float pre_idle{0.0};
  float idle{}
};

#endif