#include <DataProcessor.hpp>
#include <utils.hpp>

#include <libairspy/airspy.h>

#include <cmath>
#include <iostream>

DataProcessor::DataProcessor() {
}

DataProcessor::~DataProcessor() {
}

void DataProcessor::setSampleRate(uint32_t sampleRate_) {
    sampleRate = sampleRate_;
}

void DataProcessor::process(const std::vector<IQSample>& samples_) {
    samples = samples_;

    AMDemodulate();
    FMDemodulate();

    // drawAsciiGraph(AMDemodulated);
    // drawAsciiGraph(FMDemodulated);
}

void DataProcessor::AMDemodulate(int filterOrder) {
    AMDemodulated.reserve(samples.size());

    for (const auto& sample : samples) {
        AMDemodulated.push_back(std::sqrt(sample.first * sample.first + sample.second * sample.second));
    }

    AMDemodulated = applyLowPassFilter(AMDemodulated, filterOrder);
    // drawAsciiGraph(AMDemodulated);
}

void DataProcessor::FMDemodulate(int filterOrder) {
    FMDemodulated.reserve(samples.size() - 1);

    double previousPhase = lastPhase;

    // Calculate phase differences to get instantaneous frequency
    for (size_t i = 1; i < samples.size(); i++) {
        // Step 1: Calculate the current phase
        double currentPhase = std::atan2(samples[i].second, samples[i].first);

        // Step 2: Calculate phase difference (instantaneous frequency)
        double phaseDifference = currentPhase - previousPhase;

        // Step 3: Phase unwrapping (handle -π to π discontinuity)
        if (phaseDifference > M_PI) {
            phaseDifference -= 2 * M_PI;
        } else if (phaseDifference < -M_PI) {
            phaseDifference += 2 * M_PI;
        }

        // Store the demodulated frequency (scaled by sample rate)
        FMDemodulated.push_back(phaseDifference * sampleRate / (2 * M_PI));

        // Update previous phase
        previousPhase = currentPhase;
    }

    // Store the last phase for the next iteration
    lastPhase = previousPhase;

    // Step 4: Apply low-pass filter to smooth the demodulated signal
    FMDemodulated = applyLowPassFilter(FMDemodulated, filterOrder);
}

void DataProcessor::detectPulses() {
    for (const auto& signal : AMDemodulated) {
        switch (pulseState) {
            case PulseDetectionState::NoPulse:
                if (signal > pulseData.pulseThreshold) {
                    startFirstPulse();
                }
                break;
            case PulseDetectionState::FirstPulse:
                if (signal > pulseData.pulseThreshold) {
                    continuePulse();
                } else {
                    startPulseGap();
                }
                if (pulseData.lowLevel > 10) {
                    pulseState = PulseDetectionState::PulseGap;
                }
                break;
            case PulseDetectionState::Pulse:
                if (signal > pulseData.pulseThreshold) {
                    pulseData.highLevel++;
                } else {
                    startPulseGap();
                }
                if (pulseData.lowLevel > 10) {
                    pulseState = PulseDetectionState::PulseGap;
                }
                break;
            case PulseDetectionState::PulseGap:
                if (signal > pulseData.pulseThreshold) {
                    startPulse();
                }
                else if (pulseData.spikeCounter > maxSpikeCounter) {
                    endPulse();
                }
                break;
        }
    }
}

void DataProcessor::startFirstPulse() {
    pulseState = PulseDetectionState::FirstPulse;
    pulseData.lowLevel = 0;
    pulseData.highLevel = 0;
    pulseData.pulseCounter = 0;
    pulseData.pulsePeriod = 0;
}

void DataProcessor::startPulse() {
    pulseState = PulseDetectionState::Pulse;
    pulseData.lowLevel = 0;
    pulseData.highLevel = 0;
    pulseData.pulseCounter = 0;
    pulseData.pulsePeriod = 0;
}

void DataProcessor::continuePulse() {
    pulseData.pulseCounter++;
    pulseData.pulsePeriod++;
}

void DataProcessor::startPulseGap() {
    pulseState = PulseDetectionState::PulseGap;
    pulseData.lowLevel = 0;
    pulseData.highLevel = 0;
    pulseData.pulseCounter = 0;
    pulseData.pulsePeriod = 0;
}

void DataProcessor::endPulse() {
    pulseState = PulseDetectionState::NoPulse;
    pulseData.lowLevel = 0;
    pulseData.highLevel = 0;
    pulseData.pulseCounter = 0;
    pulseData.pulsePeriod = 0;
}

std::vector<float> DataProcessor::applyLowPassFilter(
    const std::vector<float>& signal,
    int filterOrder
) const {
    std::vector<float> filtered(signal.size(), 0.0);
    for (size_t i = filterOrder; i < signal.size(); ++i) {
        float sum = 0.0;
        for (int j = 0; j < filterOrder; ++j) {
            sum += signal[i - j];
        }
        filtered[i] = sum / filterOrder;
    }

    return filtered;
}
