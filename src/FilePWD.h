//
// Created by Neo on 25.03.2024.
//

#ifndef GAME_FILEPWD_H
#define GAME_FILEPWD_H

#include <string>
#include <filesystem>
#include <fstream>

class FilePWD {
public:
    static std::string readFile(const std::filesystem::path& path);
};


#endif //GAME_FILEPWD_H
