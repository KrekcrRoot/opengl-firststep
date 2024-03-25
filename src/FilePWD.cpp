//
// Created by Neo on 25.03.2024.
//

#include "FilePWD.h"

std::string FilePWD::readFile(const std::filesystem::path &path) {
    std::ifstream in(path, std::ios::binary);
    const auto sz = std::filesystem::file_size(path);
    std::string res(sz, '\0');
    in.read(res.data(), (long long) sz);

    return res;
}