#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <random>
#include <string>
#include <cstring>
#include <unordered_set>

#include <ctime>

#include <future>      // std::async, std::future
#include <thread>      // std::this_thread::sleep_for
#include <chrono>      // std::chrono literals
#include <numeric>     // std::accumulate
#include <cassert>    //for assert - use assert at runtime check

#include "header1.hpp"
#include "timer.hpp"

using namespace std::chrono_literals;


static uint32_t s_AllocCount=0;

void* operator new(size_t size){
    
    s_AllocCount++;
    std::cout << "Allocating "<<size<<" bytes \n";
    return malloc(size);
}



int main() {

    Timer timer; //creating object - starting the timer

    // do some work here

    std::cout << "\nTotal allocations: " << s_AllocCount << "\n";

    
    return EXIT_SUCCESS;
}



//TERMINAL COMMANDS
/* 
from vs_cpp
# compile && run
g++ -std=c++20 -I include -g src/main.cpp -o build/main && build/main
g++ -std=c++20 -I include -g src/*.cpp -o build/main && build/main

./run.sh
mkdir -p build && /usr/bin/g++ -std=c++20 -I include -g src/main.cpp -o build/main && ./build/main

OR CMAKE

cmake -S . -B build && cmake --build build

# from project root
mkdir -p build
cmake -S . -B build            # configure/generate
cmake --build build --config Debug
./build/VS_CPP                 # run the CMake target (project name)

*/


