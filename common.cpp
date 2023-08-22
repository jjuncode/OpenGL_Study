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
    
    SPDLOG_INFO("{}파일 내용 :\n {}", filename, text.str());
    return text.str();
}