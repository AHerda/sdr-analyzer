#include "AirSpy.hpp"

#include <libairspy/airspy.h>

#include <iostream>

int main(int argc, char* argv[]) {
    AirSpy airspy;

    airspy.startRx([](airspy_transfer_t* transfer) {
        std::cout << "Received " << transfer->sample_count << " samples" << std::endl
            << "Dropped " << transfer->dropped_samples << " samples" << std::endl;
        return 0;
    }, nullptr);

    return 0;
}
