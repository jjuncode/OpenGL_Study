#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        SPDLOG_ERROR("failed to open file: {}", filename);
        fin.close();
        return {};
    }
    std::stringstream text;
    text << fin.rdbuf();
    fin.close();
    return text.str();
}