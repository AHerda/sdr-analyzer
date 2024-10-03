#include <iostream>

#include <libairspy/airspy.h>

typedef struct {
    airspy_device* device;
    airspy_read_partid_serialno_t serial;
} airspy_device_my;

int main(int argc, char* argv[]) {
    airspy_device_my device;
    int result = airspy_open(&device.device);
    if (result != 0) {
        std::cerr << "Error opening device" << std::endl;
        return 1;
    }

    result = airspy_board_partid_serialno_read(device.device, &device.serial);

    if (result != 0) {
        std::cerr << "Error reading serial number" << std::endl;
        return 1;
    }

    std::cout << "Serial number: " << device.serial.serial_no[0] << std::endl;

    result = airspy_close(device.device);
    if (result != 0) {
        std::cerr << "Error closing device" << std::endl;
        return 1;
    }
    return 0;
}
