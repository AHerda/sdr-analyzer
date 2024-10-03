cmake_minimum_required(VERSION 3.13)  # Ensure the version is correct
project(sdr-sniffer VERSION 0.1.0) # Set the project name and version

# Add additional configurations or targets as needed
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Find the libaispy library
find_library(
    libairspy_location
    NAMES libairspy.a
    PATHS
        /usr/local/lib
        /usr/lib
)

# Print the location of the libairspy library
message(STATUS "libairspy location: ${libairspy_location}")

# Include the libraries
add_library(airspy STATIC IMPORTED)
set_target_properties(airspy PROPERTIES IMPORTED_LOCATION ${libairspy_location})


# Add the executable for the main application
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(sdr-sniffer ${SOURCES})

# Add the executable for the tests
# file(GLOB_RECURSE TEST_SOURCES test/*.cpp)
# add_executable(sdr-sniffer-tests ${TEST_SOURCES})

# Link the libairspy library
target_link_libraries(sdr-sniffer airspy usb-1.0)
# target_link_libraries(sdr-sniffer-tests airspy)
