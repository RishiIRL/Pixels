#include "../process/Process.h"
#include <chrono>

enum class EventType {
  ProcessStarted,
  ProcessStopped
};

struct Event {
  std::chrono::system_clock::time_point timestamp;
  EventType type;
  Process process;
};
