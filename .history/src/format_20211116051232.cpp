#include <string>
#include "format.h"
#define HR_TO_SECONDS 3600
using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  uint32_t h = seconds / HR_TO_SECONDS;
  uint32_t m = (seconds % HR_TO_SECONDS)/60;
  uint32_t s = (seconds % HR_TO_SECONDS) % 60;
  string date{to_string(h)+":"+to_string()}
  return }