#pragma once

#include <AirSpy.hpp>

#include <libairspy/airspy.h>

// #define FIX(x) ((int)(x*S_CONST))
using IQSample = std::pair<float, float>;

enum class PulseDetectionState
{
    NoPulse,
    FirstPulse,
    Pulse,
    PulseGap
};

struct PulseDetectionData
{
    int lowLevel{0};
    int highLevel{0};

    int spikeCounter{0};

    int pulseThreshold{0};
    int pulseCounter{0};
    int pulsePeriod{0};
};

class DataProcessor
{
public:
    DataProcessor();
    ~DataProcessor();

    void setSampleRate(uint32_t sampleRate_);

    void process(const std::vector<IQSample>& samples);

    void AMDemodulate(int filterOrder = 10);
    void FMDemodulate(int filterOrder = 10);

    void detectPulses();

    void startFirstPulse();
    void startPulse();
    void continuePulse();
    void startPulseGap();
    void endPulse();


    std::vector<float> applyLowPassFilter(const std::vector<float>& signal, int filterOrder) const;

    // static int FILTER_ORDER = 1;
    // static int a[FILTER_ORDER + 1] = {FIX(1.00000), FIX(0.85408)};
    // static int b[FILTER_ORDER + 1] = {FIX(0.07296), FIX(0.07296)};

private:
    uint32_t sampleRate;
    uint32_t lastPhase{0};

    uint32_t maxSpikeCounter{200};

    std::vector<IQSample> samples;
    std::vector<float> AMDemodulated;
    std::vector<float> FMDemodulated;

    PulseDetectionData pulseData;
    PulseDetectionState pulseState{PulseDetectionState::NoPulse};
};
