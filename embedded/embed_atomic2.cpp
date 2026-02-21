//std::atomic ensures thread-safe access to shared variables without locks (for simple ops). Useful in interrupts or multithreading.

#include <iostream>
#include <atomic>   // for std::atomic
#include <thread>   // for std::thread
#include <chrono>   // for timing

using namespace std::chrono_literals;

// Shared atomic variable
std::atomic<uint32_t> msTicks{0};

// Simulated handler (e.g., interrupt)
void SysTick_Handler() {
    msTicks += 1;  // Atomic increment
}

// Delay function using atomic
void Delay(std::chrono::milliseconds dlyTicks) {
    auto curTicks = std::atomic_load(&msTicks);  // Safe load
    while ((msTicks - curTicks) < static_cast<uint32_t>(dlyTicks.count())) {
        // Busy wait (in real code, add yield or sleep)
    }
}

int main() {
    // Simulate ticking in a thread
    std::thread ticker([] {
        for (int i = 0; i < 5; ++i) {
            SysTick_Handler();
            std::this_thread::sleep_for(100ms);
        }
    });

    Delay(300ms);  // Wait ~300ms (3 ticks)
    std::cout << "After delay: msTicks = " << msTicks.load() << "\n";

    ticker.join();
    return 0;
}
