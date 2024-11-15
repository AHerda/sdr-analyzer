#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <optional>
#include <string>
#include <vector>

void error(int errCode, const std::string& message, bool fatal = true);
void drawAsciiGraph(const std::vector<float>& data);
void logStatsOfVec(
    const std::vector<float>& data,
    const std::string& description = "",
    std::optional<std::string> fileName = std::nullopt,
    bool append = false
);

#endif // UTILS_HPP
