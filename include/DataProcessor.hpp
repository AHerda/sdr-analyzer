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

    std::vector<float> complexToMagSq(const std::vector<IQSample>& samples);
    void collectStatistics(const std::vector<float>& data);

    std::vector<float> applyLowPassFilter(const std::vector<float>& signal, int filterOrder) const;

    float getMin() const;
    float getMax() const;
    std::vector<float> getAvgs() const;
private:
    bool logs{false};

    float max;
    float min;
    std::vector<float> avgs;
};
