#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  string timeString;
  int hours, mins, secs;
  secs = seconds % 60;
  mins = (seconds/60) % 60;
  hours = (seconds/3600) % 60;
  timeString = std::to_string(hours) + ":" + std::to_string(mins);
  timeString = timeString + ":" + std::to_string(secs);
  return timeString;
}