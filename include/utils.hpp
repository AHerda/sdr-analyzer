#pragma once

#include <cstdint>
#include <string>

void error(int errCode, const std::string& message="", bool fatal=true);
