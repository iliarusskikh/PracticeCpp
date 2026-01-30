//std::chrono handles time durations. Literals like 1ms create durations easily. Use with sleep or timing.
#include <iostream>
#include <chrono>   // for std::chrono
#include <thread>   // for std::this_thread::sleep_for

using namespace std::chrono_literals;  // Enables 1ms, 2s, etc.

int main() {
    // Constexpr duration literal
    constexpr std::chrono::milliseconds tick_interval = 1ms;  // 1 millisecond

    std::cout << "Tick interval: " << tick_interval.count() << " ms\n";

    // Use in delay
    std::cout << "Sleeping for 500ms...\n";
    std::this_thread::sleep_for(500ms);  // Duration literal in action
    std::cout << "Done!\n";

    return 0;
}
