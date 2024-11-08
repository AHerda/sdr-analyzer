#pragma once

#include "DataProcessor.hpp"
#include "AirSpy.hpp"

class App {
public:
    void run();

private:
    DataProcessor dataProcessor{};
    AirSpy airSpy{};

    // uint32_t sampleRate{3_MHz};
    // uint32_t frequency{433'925_kHz};
};
