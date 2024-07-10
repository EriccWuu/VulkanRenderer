
#include "tool.h"

namespace huahualib {

std::string readWholeFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cout << "Read " << filename << " failed!" << std::endl;
        return std::string();
    }

    auto size = file.tellg();
    std::string content;
    content.resize(size);
    file.seekg(0);
    file.read(content.data(), content.size());

    return content;
}


}