#include "../event/Event.h"
#include <vector>

class ProcessTracker {
  public:
    std::vector<Event> compare(const std::vector<Process>& prev_snapshot, const std::vector<Process>& current_snapshot);
};
