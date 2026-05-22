cmake_minimum_required(VERSION 3.16)
project(repo_main CXX)

set(CMAKE_CXX_STANDARD 17)

set(VERSION_MAJOR "0" CACHE STRING "")
set(VERSION_MINOR "0" CACHE STRING "")
set(VERSION_PATCH "0" CACHE STRING "")
set(VERSION_BUILD "0" CACHE STRING "")

configure_file(src/version.h.in ${CMAKE_BINARY_DIR}/version.h @ONLY)

include_directories(${CMAKE_BINARY_DIR})
add_executable(main-demo src/main.cpp)
target_link_libraries(main-demo dl)

include(FetchContent)
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.3)
FetchContent_MakeAvailable(Catch2)
add_executable(tests_main tests/test_main.cpp)
target_link_libraries(tests_main PRIVATE Catch2::Catch2WithMain dl)
target_include_directories(tests_main PRIVATE ${CMAKE_BINARY_DIR})
