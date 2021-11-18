#include <string>
#include <chrono>
#include "date/date.h"

#include "format.h"

using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  std::chrono::duration<long,std::ratio<1,1>> secs(seconds);
  return std::format("{:%T}",secs); }