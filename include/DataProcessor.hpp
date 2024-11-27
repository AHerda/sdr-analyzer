#pragma once

#include <AirSpy.hpp>

#include <libairspy/airspy.h>

#include <complex>

using IQSample = std::complex<float>;

class DataProcessor
{
public:
    DataProcessor();
    ~DataProcessor();

    void process(const std::vector<IQSample>& samples);

    std::vector<float> complexToMagSq(const std::vector<IQSample>& samples) const;
    void collectStatistics(const std::vector<float>& data);

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
