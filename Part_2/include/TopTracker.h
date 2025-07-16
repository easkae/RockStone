#pragma once

#include <deque>
#include <vector>
#include <chrono>
#include <string>
#include <utility>

using PlayerID = uint64_t;

struct ActionRecord 
{
    PlayerID player_id;
    std::string action;
};

class TopTracker 
{
public:
    using TimePoint = std::chrono::system_clock::time_point;
    
    TopTracker(size_t max_actions, std::chrono::milliseconds timeout);
    
    void add(const ActionRecord& record);
    void clean();
    std::vector<ActionRecord> get_actions() const;

private:
    size_t max_actions_size;
    std::chrono::milliseconds timeout_size;
    std::deque<std::pair<TimePoint, ActionRecord>> records_deque;
    
    void clean(TimePoint now);
};
