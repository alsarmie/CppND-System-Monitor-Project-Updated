#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor() { Cores(); }
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int kCPU);
  void Cores();
  // TODO: Declare any necessary private members
 private:
  int cores_{-1};
};

#endif