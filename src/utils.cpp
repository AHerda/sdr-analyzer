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
    const int width = data.size();
    const int graphHeight = 200;
    const float maxVal = *std::max_element(data.begin(), data.end());
    const float minVal = *std::min_element(data.begin(), data.end());
    const double scale = (double) (graphHeight / (maxVal - minVal));

    for (size_t x = 0; x < width; ++x) {
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
}

void logStatsOfVec(
    const std::vector<float>& data,
    std::optional<Info> dataInfo
) {
    const float avg = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    const float min = *std::min_element(data.begin(), data.end());
    const float max = *std::max_element(data.begin(), data.end());
    if (dataInfo) {
        const Info info = dataInfo.value();
        std::ofstream stream;
        if (info.append) {
            stream.open(info.fileName, std::ios_base::app);
        } else {
            stream.open(info.fileName);
            stream << "description;date;time;duration_s;frequency;min;max;avg" << std::endl;
        }
        tm* ltm = std::localtime(&(info.startTime));


        std::string date = std::to_string(ltm->tm_mday) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(1900 + ltm->tm_year);
        std::string time = std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);

        stream
            << info.description << ";"
            << date << ";"
            << time << ";"
            << info.durationS << ";"
            << info.frequency << ";"
            << min << ";"
            << max << ";"
            << avg << std::endl;
        stream.close();
    }
    else
        std::cout << "min: " << min << std::endl
            << "max: " << max << std::endl
            << "avg: " << avg << std::endl;
}
