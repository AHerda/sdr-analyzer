cmake_minimum_required(VERSION 3.13)
project(sdr-analyzer VERSION 0.1.0)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add additional configurations or targets as needed
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

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
file(GLOB_RECURSE HEADERS include/*.hpp)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(sdr-analyzer ${SOURCES} ${HEADERS})

# Include the directories
target_include_directories(sdr-analyzer PRIVATE include)

# Link the libairspy library
target_link_libraries(sdr-analyzer airspy usb-1.0)
