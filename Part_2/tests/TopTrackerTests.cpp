#include "TopTracker.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void print_test_result(const string& test_name, bool passed) 
{
    cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << endl;
}

void test_basic_functionality()
{
    bool passed = true;
    TopTracker tracker(3, chrono::milliseconds(100));
    
    tracker.add({1, "kill"});
    tracker.add({2, "death"});
    tracker.add({3, "respawn"});
    
    auto actions = tracker.get_actions();
    if (actions.size() != 3)
    {
        cerr << "  Error: Expected 3 actions, got " << actions.size() << endl;
        passed = false;
    }

    if (actions.empty() || actions.back().player_id != 3)
    {
        cerr << "  Error: Expected latest action by player 3" << endl;
        passed = false;
    }
    if (actions.size() < 3 || actions.front().player_id != 1)
    {
        cerr << "  Error: Expected oldest action by player 1" << endl;
        passed = false;
    }
    
    tracker.add({4, "heal"});
    actions = tracker.get_actions();
    if (actions.size() != 3)
    {
        cerr << "  Error: Expected 3 actions after overflow, got " << actions.size() << endl;
        passed = false;
    }
    if (actions.empty() || actions.back().player_id != 4)
    {
        cerr << "  Error: Expected latest action by player 4 after overflow" << endl;
        passed = false;
    }
    if (actions.size() < 3 || actions.front().player_id != 2)
    {
        cerr << "  Error: Expected oldest action by player 2 after overflow" << endl;
        passed = false;
    }
    
    print_test_result("test_basic_functionality", passed);
}

void test_timeout_cleanup()
{
    bool passed = true;
    TopTracker tracker(10, chrono::milliseconds(50));
    
    tracker.add({1, "action1"});
    this_thread::sleep_for(chrono::milliseconds(30));
    tracker.add({2, "action2"});
    this_thread::sleep_for(chrono::milliseconds(30));
    
    auto actions = tracker.get_actions();
    if (actions.size() != 1)
    {
        cerr << "  Error: Expected 1 action after timeout, got " << actions.size() << endl;
        passed = false;
    }
    if (actions.empty() || actions[0].player_id != 2)
    {
        cerr << "  Error: Expected remaining action by player 2" << endl;
        passed = false;
    }
    
    print_test_result("test_timeout_cleanup", passed);
}

void test_edge_cases()
{
    bool passed = true;
    
    TopTracker zero_size_tracker(0, chrono::milliseconds(100));
    zero_size_tracker.add({1, "action"});
    if (!zero_size_tracker.get_actions().empty())
    {
        cerr << "  Error: Expected empty actions for zero-size tracker" << endl;
        passed = false;
    }
    
    TopTracker zero_timeout_tracker(3, chrono::milliseconds(0));
    zero_timeout_tracker.add({1, "action"});
    if (!zero_timeout_tracker.get_actions().empty())
    {
        cerr << "  Error: Expected empty actions for zero-timeout tracker" << endl;
        passed = false;
    }
    
    TopTracker full_tracker(1, chrono::hours(24));
    full_tracker.add({1, "first"});
    full_tracker.add({2, "second"});
    auto actions = full_tracker.get_actions();
    if (actions.size() != 1)
    {
        cerr << "  Error: Expected 1 action in full tracker" << endl;
        passed = false;
    }
    if (actions.empty() || actions.back().player_id != 2)
    {
        cerr << "  Error: Expected latest action in full tracker" << endl;
        passed = false;
    }
    
    print_test_result("test_edge_cases", passed);
}

int main() {
    test_basic_functionality();
    test_timeout_cleanup();
    test_edge_cases();
    
    cout << "\nAll tests completed" << endl;
    return 0;
}
