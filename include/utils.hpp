#pragma once

#include <ctime>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

typedef struct {
    std::string description;
    std::string fileName;
    std::time_t startTime;
    uint32_t frequency;
    uint32_t durationS;
    bool append;
} Info;

void error(int errCode, const std::string& message, bool fatal = true);
void drawAsciiGraph(const std::vector<float>& data);
void logStatsOfVec(
    const std::vector<float>& data,
    std::optional<Info> dataInfo = std::nullopt
);
