#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int kCPU);
  int NumCPUs();
  // TODO: Declare any necessary private members
 private:
 
};

#endif