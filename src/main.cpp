#include <iostream>

#include <libairspy/airspy.h>

typedef struct {
    airspy_device* device;
    airspy_read_partid_serialno_t serial;
} airspy_device_my;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
