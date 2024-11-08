#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

void error(int errCode, const std::string& message, bool fatal = true);
void drawAsciiGraph(const std::vector<float>& data);

#endif // UTILS_HPP
