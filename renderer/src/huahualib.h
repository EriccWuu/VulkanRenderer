#pragma once

#include "tool.h"
#include "vulkan/vulkan.hpp"
#include "context.h"
#include "renderer.h"
#include "model.h"
#include "vertex.h"

namespace huahualib {

void init(const std::vector<const char*> &extensions, CreateSurfaceFunc func, int w, int h);
void quit();
Renderer* getRenderer();

}
