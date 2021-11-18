#include <string>

#include "format.h"

using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  uint32_t h = seconds / 3600;
  uint32_t m = (seconds % 3600)/60;
  uint32_t s = (seconds)

  return std::format("{:%T}",secs); }