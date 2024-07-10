#pragma once

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

#include "vulkan/vulkan.hpp"

namespace huahualib {

using CreateSurfaceFunc = std::function<vk::SurfaceKHR(vk::Instance)>;

std::string readWholeFile(const std::string &filename);

}
