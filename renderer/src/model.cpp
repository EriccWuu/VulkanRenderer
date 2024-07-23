#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>
#include <unordered_map>

namespace huahualib {

Model::Model(const std::string &objFilename, const std::string &mtlBasedir) {
    load(objFilename, mtlBasedir);
}

Model::~Model() {

}

std::vector<Vertex>& Model::vertices() {
    return vertices_;
}

std::vector<uint32_t>& Model::indices() {
    return indices_;
}

void Model::load(const std::string &objFilename, const std::string &mtlBasedir) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err, warn;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objFilename.c_str(), mtlBasedir.c_str())) {
        throw std::runtime_error("Failed to load .obj file: " + objFilename + "\n");
    }

    if (warn != "" || err != "") {
        std::cout << warn << std::endl;
        std::cout << err << std::endl;
    }

    std::cout << materials.size() << std::endl;
    std::cout << shapes.size() << std::endl;

    std::unordered_map<Vertex, size_t> uniqueVertices;
    uint32_t idx = 0;
    for (uint32_t i = 0; i < shapes.size(); ++ i) {
        auto &mesh = shapes[i].mesh;
        uint32_t num_index = mesh.indices.size();
        uint32_t num_face = mesh.num_face_vertices.size();

        submodel_.push_back({indices_.size(), indices_.size() + num_index - 1});
        
        for (uint32_t j = 0; j < num_index; ++ j) {
            auto &index = mesh.indices[j];
            Vertex v = {};

            // Position
            v.pos = {
                attrib.vertices[3 * index.vertex_index],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            // Normal
            v.normal = {
                attrib.normals[3 * index.normal_index],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };

            // Texcoord
            v.texcoord = {
                attrib.texcoords[2 * index.texcoord_index],
                1 - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            if (uniqueVertices.count(v) == 0) {
                uniqueVertices[v] = (uint32_t)vertices_.size();
                vertices_.push_back(v);
            }
            indices_.push_back(uniqueVertices[v]);
        }
    }

    std::cout << "Load Model " + objFilename + " successed!" << std::endl;
}

}