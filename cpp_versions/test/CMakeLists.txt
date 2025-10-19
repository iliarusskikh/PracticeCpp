cmake_minimum_required(VERSION 3.10...3.28)
project(WorkshopTests)
enable_testing()
set_property(DIRECTORY PROPERTY LABELS "workshop")
set(CMAKE_CXX_STANDARD 20)

include(CheckIncludeFileCXX)
include(CheckCXXSourceCompiles)

foreach(t IN ITEMS mytest)
  add_executable(workshop_${t} ${t}.cpp)
  add_test(NAME workshop_${t} COMMAND workshop_${t})
endforeach()

# ALL TEST NAMES
set_property(TEST workshop_mytest
PROPERTY PASS_REGULAR_EXPRESSION "counter: 2")