#include "format.h"

#include <string>
#define HR_TO_SECONDS 3600
using std::string;

string HMSformat(long value) { 
  string hms{}
  
  
  
  return hms; }
// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  string hh_mm_ss;
  uint32_t h = seconds / HR_TO_SECONDS;
  uint32_t m = (seconds % HR_TO_SECONDS) / 60;
  uint32_t s = (seconds % HR_TO_SECONDS) % 60;
  if (s >= 10)
    hh_mm_ss =
        std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s);
  else
    hh_mm_ss =
        std::to_string(h) + ":" + std::to_string(m) + ":0" + std::to_string(s);
  return hh_mm_ss;
}