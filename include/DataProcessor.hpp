#pragma once

#include <libairspy/airspy.h>

#include <complex>
#include <vector>

using IQSample = std::complex<float>;

class DataProcessor
{
public:
    void process(const std::vector<IQSample>& samples);

    void collectStatistics(const std::vector<float>& data);
    std::vector<float> complexToMagSq(const std::vector<IQSample>& samples) const;
    std::vector<float> applyLowPassFilter(const std::vector<float>& signal);

    float getMin() const;
    float getMax() const;
    std::vector<float> getAvgs() const;

    void reset();

private:
    int filterOrder{4};
    bool logs{false};

    std::vector<float> lastData;

    float max{0.0};
    float min{1.0};
    std::vector<float> avgs;
};
