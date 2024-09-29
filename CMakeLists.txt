cmake_minimum_required(VERSION 3.13)  # Ensure the version is correct
project(sdr-sniffer VERSION 0.1.0) # Set the project name and version

# Add additional configurations or targets as needed
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable for the main application
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(sdr-sniffer ${SOURCES})

# Add the executable for the tests
file(GLOB_RECURSE TEST_SOURCES test/*.cpp)
add_executable(sdr-sniffer-tests ${TEST_SOURCES})

# Link libraries if needed
# target_link_libraries(sdr-sniffer <library_name>)
target_link_libraries(sdr-sniffer libairspy)
# target_link_libraries(sdr-sniffer-tests <library_name>)
