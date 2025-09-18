#include <iostream>
#include <vector>
#include <numeric>
#include <stdexcept>

double calculate_average(const std::vector<int>& marks) {
    if (marks.empty()) {
        throw std::invalid_argument("Error: No marks provided.");
    }
    // Use std::accumulate for summing elements
    int sum = std::accumulate(marks.begin(), marks.end(), 0);
    return static_cast<double>(sum) / marks.size();
}

int main() {
    // Use vector for dynamic sizing
    std::vector<int> marks = {23, 45, 55, 22};
    
    try {
        // Calculate and format output to 2 decimal places
        double avg = calculate_average(marks);
        std::cout << "Average marks: " << std::fixed << std::setprecision(2) << avg << '\n';
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
