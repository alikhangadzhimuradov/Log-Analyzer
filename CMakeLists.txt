cmake_minimum_required(VERSION 3.10)
project(LogAnalyzer)

set(CMAKE_CXX_STANDARD 17)

add_executable(log_analyzer
    src/LogAnalyzer.cpp
    src/main.cpp
)

target_include_directories(log_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(log_analyzer_tests
    test/test_analyzer.cpp
    src/LogAnalyzer.cpp
)

target_link_libraries(log_analyzer_tests
    GTest::gtest_main
    GTest::gmock
)

enable_testing()
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/logs DESTINATION ${CMAKE_BINARY_DIR})
add_test(NAME log_analyzer_tests COMMAND log_analyzer_tests)