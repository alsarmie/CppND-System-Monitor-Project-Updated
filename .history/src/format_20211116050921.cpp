#include <string>

#include "format.h"

using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  uint32_t h = seconds / 3600;
  unit32_t m = (seconds % 3600)/60;

  return std::format("{:%T}",secs); }