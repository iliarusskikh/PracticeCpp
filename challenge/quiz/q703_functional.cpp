#include <functional>
#include <iostream>
#include <string_view>

// The "state" being transformed at each step
struct Counter {
    int value{};

    void print(std::string_view label) const {
        std::cout << "  [" << label << "] value = " << value << '\n';
    }
};

class Processor {
public:
    using TraceCallback = std::function<void(std::string_view label, const Counter& state)>;

    // trace = {} means "no tracing" (optional)
    [[nodiscard]] int run(int start, TraceCallback trace = {}) const {
        Counter state{start};
        trace_step(trace, "Input", state);

        state.value += 10;
        trace_step(trace, "After +10", state);

        state.value *= 2;
        trace_step(trace, "After *2", state);

        state.value -= 5;
        trace_step(trace, "After -5", state);

        return state.value;
    }

private:
    static void trace_step(const TraceCallback& trace, std::string_view label, const Counter& state) {
        if (trace) {          // only call if a callback was provided
            trace(label, state); // print_trace
        }
    }
};

// Free function callback
void print_trace(std::string_view label, const Counter& state) {
    state.print(label);
}

int main() {
    Processor proc;

    // 1) No callback — silent, just get the result
    std::cout << "Silent: " << proc.run(3) << '\n';

    // 2) Pass a free function
    std::cout << "\nWith trace (function):\n";
    proc.run(3, print_trace);

    // 3) Pass a lambda (inline custom behavior)
    std::cout << "\nWith trace (lambda):\n";
    proc.run(3, [](std::string_view label, const Counter& state) { std::cout << ">> " << label << " => " << state.value << '\n';});

    return 0;
}
