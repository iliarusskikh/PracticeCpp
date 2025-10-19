cmake_minimum_required(VERSION 3.10...3.28)
project(CoroutineTests)
enable_testing()
set_property(DIRECTORY PROPERTY LABELS "coroutine")
set(CMAKE_CXX_STANDARD 20)

include(CheckIncludeFileCXX)
include(CheckCXXSourceCompiles)

# Force enable for AppleClang 17+
set(cpp_impl_coroutine TRUE)
set(have_coroutine TRUE)
message(STATUS "Forcing coroutine support for AppleClang 17.0")

foreach(t IN ITEMS coroutine_handle handle co_return generator promise return yield)
  add_executable(coroutine_${t} ${t}.cpp)
  add_test(NAME coroutine_${t} COMMAND coroutine_${t})
endforeach()

# ALL 7 CORRECT TEST NAMES
set_property(TEST coroutine_coroutine_handle coroutine_handle coroutine_co_return coroutine_generator coroutine_promise coroutine_return coroutine_yield
PROPERTY PASS_REGULAR_EXPRESSION "counter: 2")

if(APPLE)
  target_compile_options(coroutine_handle PRIVATE -Wno-unsequenced)
  target_compile_options(coroutine_coroutine_handle PRIVATE -Wno-unsequenced)
endif()