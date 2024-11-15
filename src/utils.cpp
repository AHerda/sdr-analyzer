#include <utils.hpp>

#include <libairspy/airspy.h>

#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

void error(int errCode, const std::string& message, bool fatal) {
    std::cerr << "ERROR:" << std::endl
        << "\t" << message << std::endl;

    switch (errCode)
    {
    case airspy_error::AIRSPY_SUCCESS:
        return;

    case airspy_error::AIRSPY_TRUE:
        return;

    case airspy_error::AIRSPY_ERROR_INVALID_PARAM:
        std::cerr << "\tInvalid parameter" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_NOT_FOUND:
        std::cerr << "\tNot found" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_BUSY:
        std::cerr << "\tBusy" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_NO_MEM:
        std::cerr << "\tNo memory" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_UNSUPPORTED:
        std::cerr << "\tUnsupported" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_LIBUSB:
        std::cerr << "\tLibUSB" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_THREAD:
        std::cerr << "\tThread" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_STREAMING_THREAD_ERR:
        std::cerr << "\tStreaming thread error" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_STREAMING_STOPPED:
        std::cerr << "\tStreaming stopped" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_OTHER:
        std::cerr << "\tOther" << std::endl;
        break;

    default:
        std::cerr << "\tUnknown error" << std::endl;
        break;
    }

    if (fatal)
        throw std::runtime_error(message);
}

void drawAsciiGraph(const std::vector<float>& data) {
    const int width = 100;//data.size(); // Width of the ASCII graph
    const int graphHeight = 200; // Height of the ASCII graph
    const float maxVal = *std::max_element(data.begin(), data.end());
    const float minVal = *std::min_element(data.begin(), data.end());
    const double scale = (double) (graphHeight / (maxVal - minVal));

    for (size_t x = 0; x < data.size(); ++x) {
        for (int y = graphHeight; y >= 0; --y) {
            float value = data[x];
            int graphY = static_cast<int>((value - minVal) * scale);
            if (graphY > y) {
                std::printf("#");
            } else {
                std::printf(" ");
            }
        }
        std::printf("\n");
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

void logStatsOfVec(
    const std::vector<float>& data,
    const std::string& description,
    std::optional<std::string> fileName,
    bool append
) {
    const float avg = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    const float min = *std::ranges::min_element(data);
    const float max = *std::ranges::max_element(data);
    if (fileName) {
        std::ofstream stream;
        if (append) {
            stream.open(fileName.value(), std::ios_base::app);
        } else {
            stream.open(fileName.value());
            stream << "description;min;max;avg" << std::endl;
        }
        stream << description << ";" << min << ";" << max << ";" << avg << std::endl;
        stream.close();
    }
    else
        std::cout << "min: " << min << std::endl
            << "max: " << max << std::endl
            << "avg: " << avg << std::endl;
}
