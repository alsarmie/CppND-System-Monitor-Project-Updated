#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
 Processor(){}
  float Utilization();  // TODO: See src/processor.cpp
  float Utilization(int kCPU);
  int Cores();
  // TODO: Declare any necessary private members
 private:
    
};

#endif