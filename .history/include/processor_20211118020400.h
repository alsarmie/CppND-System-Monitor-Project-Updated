#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
using std::vector;
class Processor {
 public:
  Processor() { Cores(); }
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int);
  void Cores();
  // TODO: Declare any necessary private members
 private:
  int cores_{-1};  // To discard the aggregate cpu info.
  vector<float> agg_cpu_values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

#endif