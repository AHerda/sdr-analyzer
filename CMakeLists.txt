cmake_minimum_required(VERSION 3.13)  # Ensure the version is correct
project(sdr-sniffer VERSION 0.1.0) # Set the project name and version

# Add additional configurations or targets as needed
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directories
# include_directories(src include ${libairspy_include_dir})

# find_path(
#     libairspy_include_dir
#     NAMES libairspy/airspy.h
#     PATHS
#         /usr/local/include
#         /usr/include
# )

find_library(
    libairspy_location
    NAMES libairspy.a
    PATHS
        /usr/local/lib
        /usr/lib
)

message(STATUS "libairspy location: ${libairspy_location}")
# message(STATUS "libairspy include dir: ${libairspy_include_dir}")

# include_directories(${libairspy_INCLUDE_DIRS})
# link_directories(${libairspy_LIBRARIES})

add_library(airspy STATIC IMPORTED)
set_target_properties(airspy PROPERTIES IMPORTED_LOCATION ${libairspy_location})

# Link libraries if needed
# target_link_libraries(sdr-sniffer <library_name>)
# target_link_libraries(sdr-sniffer-tests <library_name>)

# Add the executable for the main application
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(sdr-sniffer ${SOURCES})

# Add the executable for the tests
# file(GLOB_RECURSE TEST_SOURCES test/*.cpp)
# add_executable(sdr-sniffer-tests ${TEST_SOURCES})

# Link the libairspy library
target_link_libraries(sdr-sniffer airspy)
# target_link_libraries(sdr-sniffer-tests airspy)
