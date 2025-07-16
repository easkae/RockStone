#include "TopTracker.h"
#include <algorithm>

TopTracker::TopTracker(size_t max_actions, std::chrono::milliseconds timeout)
    : max_actions_size(max_actions), timeout_size(timeout) {}

void TopTracker::add(const ActionRecord& record) 
{
    auto now = std::chrono::system_clock::now();

    records_deque.emplace_back(now, record);

    clean(now);
}

void TopTracker::clean()
{
    clean(std::chrono::system_clock::now());
}

void TopTracker::clean(TimePoint now)
{
    const auto expired_threshold = now - timeout_size;

    while (!records_deque.empty() && records_deque.front().first <= expired_threshold)
    {
        records_deque.pop_front();
    }

    while (records_deque.size() > max_actions_size)
    {
        records_deque.pop_front();
    }
}

std::vector<ActionRecord> TopTracker::get_actions() const
{
    auto non_const_this = const_cast<TopTracker*>(this);
    non_const_this->clean();
    
    std::vector<ActionRecord> result;
    result.reserve(records_deque.size());
    
    for (const auto& record : records_deque)
    {
        result.push_back(record.second);
    }
    
    return result;
}
