#ifndef GAME_FILEREADSINGLETON_H
#define GAME_FILEREADSINGLETON_H

#include <string>
#include <memory>
#include <stdexcept>

namespace engine {

    class IFileReader {
    public:
      IFileReader() = default;

      ~IFileReader() = default;

      virtual std::string readFile(const std::string &filepath) = 0;
    };

    class FileReadSingleton {
    public:
        FileReadSingleton(const FileReadSingleton &) = delete;

        FileReadSingleton &operator=(const FileReadSingleton &) = delete;

        static FileReadSingleton &getInstance() {
            static FileReadSingleton instance;
            return instance;
        };

        void setFileReader(const std::shared_ptr<IFileReader> &file_reader) {
            _file_reader = std::move(file_reader);
        }

        std::string readFile(const std::string &filepath) {
            if (!_file_reader.get()) {
                throw std::runtime_error("FileReadSingleton has no file reader");
            }

            return _file_reader->readFile(filepath);
        }

    private:
        FileReadSingleton() = default;

        std::shared_ptr<IFileReader> _file_reader;
    };
}

#endif //GAME_FILEREADSINGLETON_H
