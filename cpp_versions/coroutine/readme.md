rm -rf build  # Clean old failed build
cmake -S . -B build
cmake --build build
cd build
ctest -V
