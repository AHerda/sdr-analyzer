#include <DataProcessor.hpp>
#include <utils.hpp>

#include <libairspy/airspy.h>

#include <cmath>
#include <numeric>
#include <iostream>

void DataProcessor::process(const std::vector<IQSample>& samples) {
    const std::vector<float> magnitude = complexToMagSq(samples);

    const std::vector<float> filtered = applyLowPassFilter(magnitude);

    collectStatistics(filtered);
}

std::vector<float> DataProcessor::complexToMagSq(const std::vector<IQSample>& samples) const {
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
    const std::vector<float>& signal
) {
    std::vector<float> filtered(signal.size(), 0.0);

    for (size_t i = 0; i < signal.size(); ++i) {
        float sum = 0.0;
        for (size_t j = 0; j < filterOrder; ++j) {
            if (i >= j)
                sum += signal[i - j];
            else
                sum += (lastData.size() + i >= j
                    ?   lastData[lastData.size() + i - j]
                    :   0.0);
        }
        filtered[i] = sum / filterOrder;

        if (i + filterOrder == signal.size()) {
            lastData.clear();
        } else if (i + filterOrder > signal.size()) {
            lastData.push_back(signal[i]);
        }
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

void DataProcessor::reset() {
    std::swap(min, max);
    avgs.clear();
}
