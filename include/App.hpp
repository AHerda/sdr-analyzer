#pragma once

#include <AirSpy.hpp>
#include <DataProcessor.hpp>
#include <units.hpp>

#include <ctime>
#include <string>

class App {
public:
    void run();
    void logData(std::time_t startTime);

    void reset();

    void setDescription(std::string description_);
    void setFileName(std::string fileName_);
    void setDuration(uint32_t duration_);
    void setAppend();

    void setFrequency(uint32_t frequency_);

private:
    /// @brief Description od the measurments taken
    /// @example livingroom-2x3
    std::string description{""};
    /// @brief File name of the output
    std::string fileName{"output.csv"};

    /// @brief Frequency in Hz
    /// @note The frequency must be between 24MHz and 1.75GHz.
    /// @note The default value is 434MHz.
    uint32_t frequency{433'920_kHz};
    /// @brief Duration of the measurments. In minutes
    /// @note The default duration is 1 min
    uint32_t duration{60};
    /// @brief Flag to check if statistics should be appended to the file or just override the existing data
    bool append{false};

    DataProcessor dataProcessor{};
    AirSpy airSpy{frequency};
};
