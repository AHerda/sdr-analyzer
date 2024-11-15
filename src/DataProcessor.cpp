#include <DataProcessor.hpp>
#include <utils.hpp>

#include <libairspy/airspy.h>

#include <cmath>
#include <numeric>
#include <iostream>

DataProcessor::DataProcessor() {
}

DataProcessor::~DataProcessor() {
    // for (const auto& avg : avgs) {
    //     std::cout << avg << std::endl;
    // }
}

void DataProcessor::process(const std::vector<IQSample>& samples) {
    const std::vector<float> data = complexToMagSq(samples);
    // logStatsOfVec(magSq);
    //drawAsciiGraph(magSq);
    // FMDemodulate();

    // drawAsciiGraph(magSq);
    // drawAsciiGraph(FMDemodulated);

    collectStatistics(data);
}

std::vector<float> DataProcessor::complexToMagSq(const std::vector<IQSample>& samples) {
    std::vector<float> data;
    data.reserve(samples.size());

    for (const auto& sample : samples) {
        data.push_back(std::norm(sample));
    }

    return data;
}

void DataProcessor::collectStatistics(const std::vector<float>& data) {
    float avg = std::accumulate(data.begin(), data.end(), 0.0) / data.size();

    if (logs) {
        logStatsOfVec(data);
    }

    if (avg > max)
        max = avg;
    if (avg < min)
        min = avg;
    avgs.push_back(avg);
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

float DataProcessor::getMin() const {
    return min;
}
float DataProcessor::getMax() const {
    return max;
}
std::vector<float> DataProcessor::getAvgs() const {
    return avgs;
}
