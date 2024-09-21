#include <iostream>

#include <libairspy/airspy.h>

typdef struct {
    airspy_device_t *device;
    airspy_read_partid_serialno_t serial;
} airspy_device;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
