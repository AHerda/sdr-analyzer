#include "AirSpy.hpp"
#include "units.hpp"

#include <libairspy/airspy.h>

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

int main() { //int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);

    AirSpy airspy;

    auto time = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()) % 1000;
    printf("Time: %ld\n", milliseconds.count());

    airspy.startRx([](airspy_transfer_t* transfer) {
        // std::ostream ss;
        // uint8_t* samples = (uint8_t*) transfer->samples;
        // uint64_t avg = 0;
        // uint8_t max = 0;
        // uint32_t maxIdx = 0;

        // for (int i = 0; i < transfer->sample_count; i++) {
        //     // std::cout << samples[i] << " " << std::flush;
        //     std::printf("%d ", samples[i]);
        //     if (samples[i] > max) {
        //         max = samples[i];
        //         maxIdx = i;
        //     }
        //     avg += samples[i];
        // }
        // printf("\nSamples: %d\nAvg: %ld\nMax: %d\nIndex max: %d\n\n", transfer->sample_count, avg / transfer->sample_count, max, maxIdx);
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // printf("Expected Time: %f\n", (double) transfer->sample_count / (double) 6_MHz);

        auto now = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        printf("Actual Time: 0.%ld\n", milliseconds.count());


        // std::cout << ss.str() << std::endl;

        // delete[] samples;
        return 0;
    }, nullptr);

    while (true) {
    }

    return 0;
}
