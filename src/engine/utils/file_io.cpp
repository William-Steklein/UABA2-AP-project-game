#include "file_io.h"

namespace engine {
    std::ifstream read_file(const std::string &filepath) {
        std::ifstream f(filepath);

        if (!f.is_open()) {
            throw std::runtime_error("Unable to open file \"" + filepath + "\" to read from");
        }

        return f;
    }

    std::ofstream write_file(const std::string &filepath) {
        std::ofstream f(filepath);

        if (!f.is_open()) {
            throw std::runtime_error("Unable to open file \"" + filepath + "\" to write to");
        }

        return f;
    }

    nlohmann::json loadJsonFromFile(const std::string &filepath) {
        std::ifstream info_file = read_file(filepath);
        nlohmann::json j;
        info_file >> j;
        info_file.close();

        return j;
    }
} // engine