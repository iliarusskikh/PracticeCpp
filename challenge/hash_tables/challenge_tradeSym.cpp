#include <iostream>
#include <unordered_set>
#include <string>
#include <iomanip>

int main()
{
    // Simple set of trading symbols
    std::unordered_set<std::string> active_symbols;

    // reserve helps a lot when you know approximate size
    active_symbols.reserve(100);

    // insert various ways
    active_symbols.insert("AAPL");
    active_symbols.emplace("MSFT");
    active_symbols.insert({"GOOGL", "TSLA", "NVDA", "META"});

    // try to insert duplicate
    auto [it, inserted] = active_symbols.insert("AAPL");
    std::cout << "AAPL already present? " << (inserted ? "no" : "yes") << "\n";

    // lookup
    std::string lookup = "AMD";
    if (active_symbols.contains(lookup)) {          // C++20
        std::cout << lookup << " is active\n";
    } else {
        std::cout << lookup << " is NOT active\n";
    }

    // statistics
    std::cout << "\nStats:\n";
    std::cout << "Size:              " << active_symbols.size() << "\n";
    std::cout << "Bucket count:      " << active_symbols.bucket_count() << "\n";
    std::cout << "Load factor:       " << active_symbols.load_factor()
              << "  (max = " << active_symbols.max_load_factor() << ")\n";

    // find longest chain (optional debug)
    size_t max_chain = 0;
    for (size_t i = 0; i < active_symbols.bucket_count(); ++i) {
        max_chain = std::max(max_chain, active_symbols.bucket_size(i));
    }
    std::cout << "Longest chain:     " << max_chain << "\n";

    // iteration (order is arbitrary!)
    std::cout << "\nActive symbols (arbitrary order):\n";
    for (const auto& sym : active_symbols) {
        std::cout << "  " << sym << "\n";
    }

    return EXIT_SUCCESS;
}
