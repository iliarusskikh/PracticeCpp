//manual compilation
# Single source file (most common quick test)
clang++ -std=c++17 -Wall -o myprog main.cpp
./myprog

# Or with g++
g++ -std=c++17 -Wall -o myprog main.cpp
./myprog

# Preprocess only (see expanded macros / includes)
g++ -E main.cpp > preprocessed.cpp

# Compile only → object file
g++ -std=c++17 -c main.cpp     # produces main.o

# Link object file manually (rarely needed)
ld main.o -o myprog -lc++

# Measure build time
time g++ -std=c++17 main.cpp -o myprog

//make || make CC=arm-none-eabi-gcc


//Out-of-Source Build
mkdir -p build
cd build
cmake ..                # or cmake -G Ninja ..  (faster)
cmake --build .         # or make / ninja
# or shorter:
cmake --build . --parallel 8

# Run executable (assuming target name = VS_CPP)
./VS_CPP

# Clean build directory (instead of rm -rf build/)
cmake --build . --target clean
# or just rm -rf build/


//Modern CMakeLists.txt
# CMakeLists.txt (top-level)
cmake_minimum_required(VERSION 3.20)   # Modern baseline — supports C++20/23 well
project(MyProject
  VERSION 0.1.0
  DESCRIPTION "My C++ project"
  LANGUAGES CXX
)

# Global settings (prefer target properties over global)
set(CMAKE_CXX_STANDARD          17)     # or 20 / 23
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)     # no compiler-specific extensions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # generates compile_commands.json → clangd, etc.

# Main executable
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/utils.cpp
  # list sources explicitly — best for maintainability
  # or: file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
)

# Include directories (modern: PUBLIC so dependents inherit)
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: warnings, optimization, etc.
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic -Werror
  $<$<CONFIG:Debug>:-g -O0>
  $<$<CONFIG:Release>:-O3 -march=native>
)

# If you have a library → prefer this pattern
#add_library(myLib STATIC src/lib.cpp)
#target_include_directories(myLib PUBLIC include)
#target_link_libraries(${PROJECT_NAME} PRIVATE myLib)





//Useful CMake Commands Cheat Sheet
Purpose,Command / Pattern,Notes / When to use
Generate build system,cmake -S . -B build  or cmake .. (old style),"-S = source dir, -B = build dir"
Build,cmake --build build  or cmake --build . --parallel 12,Cross-generator
Run target,./myexe or cmake --build . --target myexe,—
Clean,cmake --build . --target clean,Safer than rm -rf
Reconfigure,cmake . (in build dir) or touch CMakeLists.txt,Forces re-run
Change build type,cmake -DCMAKE_BUILD_TYPE=Release ..,Debug / Release / RelWithDebInfo
Cross-compile (toolchain),cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain.cmake ..,"Embedded, ARM, etc."
Specify compiler,cmake -DCMAKE_CXX_COMPILER=clang++ ..,Or env var CXX=clang++
Verbose build,cmake --build . --verbose,See full commands
Install,cmake --install build  or make install,Needs install() rules
Create compile_commands.json,Already enabled above (CMAKE_EXPORT_COMPILE_COMMANDS=ON),"For clangd, YouCompleteMe, etc."
