#pragma once

#include "tiny_obj_loader.h"
#include "vertex.h"

namespace huahualib {

class Model {
public:
    Model(const std::string &objFilename, const std::string &mtlBasedir);
    ~Model();

    std::vector<Vertex>& vertices();
    std::vector<uint32_t>& indices();

private:
    struct VerticesRange {
        size_t begin_ = 0, end_ = 0;
    };

    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;
    std::vector<VerticesRange> submodel_;

    void load(const std::string &objFilename, const std::string &mtlBasedir);

};

}