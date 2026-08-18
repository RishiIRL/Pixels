#include "process/ProcessCollector.h"
#include <iostream>

int main() {
  ProcessCollector collector;
  std::vector<Process> p = collector.collect();
  for (auto i : p) {
    std::cout<<i.pid<<" "<<i.process_name<<std::endl;
  }
  return 0;
}
