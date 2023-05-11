#ifndef GAME_FILEREADER_H
#define GAME_FILEREADER_H

#include <engine/utils/FileReadSingleton.h>
#include <SFML/System.hpp>

namespace renderer {
    class FileReader : public engine::IFileReader {
    public:
        FileReader() = default;

        ~FileReader() = default;

        virtual std::string readFile(const std::string &filepath) {
            sf::FileInputStream stream;
            if (stream.open(filepath)) {
                char file[stream.getSize()];
                stream.read(file, stream.getSize());

                return std::string(file).substr(0, stream.getSize());
            } else {
                throw std::runtime_error("Unable to read file");
            }
        };
    };
}

#endif //GAME_FILEREADER_H
