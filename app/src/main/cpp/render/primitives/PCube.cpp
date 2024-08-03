//
// Created by VeraTag on 03.08.2024.
//

#include "PCube.h"

namespace Render::Primitives  {
    PCube::PCube(const Settings& settings) : Primitive(36, settings) {
        std::vector<glm::vec3> position = getPosition();
        std::vector<glm::vec3> normals = settings.withNormals ? getNormals() : std::vector<glm::vec3>{};
        std::vector<glm::vec2> textureCoordinates = settings.withTextureCoords ? getTextureCoordinates()
                                                                               : std::vector<glm::vec2>{};

        std::vector<Buffers::Vertex> vertices;

        if (settings.withTextureCoords && settings.withNormals) {
            for (int i{}; i < 6; ++i) {
                for (int j{}; j < 6; ++j) {
                    vertices.push_back(Buffers::Vertex{.position = position.at(i * 6 + j),
                            .normal = normals.at(i * 6 + j),
                            .tex_coords = textureCoordinates.at(i / 2 * 6 + j)});
                }
            }
        } else if (settings.withTextureCoords) {
            for (int i{}; i < 6; ++i) {
                for (int j{}; j < 6; ++j) {
                    vertices.push_back(Buffers::Vertex{.position = position.at(i * 6 + j),
                            .tex_coords = textureCoordinates.at(i / 2 * 6 + j)});
                }
            }
        } else if (settings.withNormals) {
            for (int i{}; i < 36; ++i) {
                vertices.push_back(Buffers::Vertex{.position = position.at(i), .normal = normals.at(i)});
            }
        } else {
            for (int i{}; i < 36; ++i) {
                vertices.push_back(Buffers::Vertex{
                        .position = position.at(i),
                });
            }
        }
        auto indices = std::vector<unsigned int>{{0, 1, 3, 1, 2, 3}};

        add(std::make_shared<Buffers::Vbo>(vertices));
        add(std::make_shared<Buffers::Ebo>(indices));
    }

    void PCube::draw() {
        Primitive::draw();

        glDrawArrays(GL_TRIANGLES, 0, vertexNumber);
    }

    void PCube::bindData(const unsigned int& bind_flag) {
        Primitive::bindData(bind_flag);

        int index = 0;

        Buffers::setVertexAttribute(index++,
                                    3,
                                    (int)(sizeof(Buffers::Vertex)),
                                    (void*)offsetof(Buffers::Vertex, position));
        if (settings.withNormals) {
            Buffers::setVertexAttribute(index++,
                                        3,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, normal));
        }
        if (settings.withTextureCoords) {
            Buffers::setVertexAttribute(index++,
                                        2,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, tex_coords));
        }
        if (settings.withTangent) {
            Buffers::setVertexAttribute(index++,
                                        3,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, tangent));
        }
        if (settings.withBitangent) {
            Buffers::setVertexAttribute(index++,
                                        3,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, bitangent));
        }

        unbind();
    }

    std::vector<glm::vec3> PCube::getPosition() {
        return {// координаты
                {-1.0f, 1.0f, -1.0f},  {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f},
                {1.0f, -1.0f, -1.0f},  {1.0f, 1.0f, -1.0f},   {-1.0f, 1.0f, -1.0f},

                {-1.0f, -1.0f, 1.0f},  {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
                {-1.0f, 1.0f, -1.0f},  {-1.0f, 1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f},

                {1.0f, -1.0f, -1.0f},  {1.0f, -1.0f, 1.0f},   {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, -1.0f},   {1.0f, -1.0f, -1.0f},

                {-1.0f, -1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f},   {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},    {1.0f, -1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f},

                {-1.0f, 1.0f, -1.0f},  {1.0f, 1.0f, -1.0f},   {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},    {-1.0f, 1.0f, 1.0f},   {-1.0f, 1.0f, -1.0f},

                {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, -1.0f},
                {1.0f, -1.0f, -1.0f},  {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, 1.0f}};
    }

    std::vector<glm::vec3> PCube::getNormals() {
        return {
                {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
                {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},

                {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},
                {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},

                {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
                {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},

                {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},
                {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},

                {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
                {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},

                {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
                {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
        };
    }

    std::vector<glm::vec2> PCube::getTextureCoordinates() {
        return {
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f},
                {0.0f, 0.0f},

                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f},
                {0.0f, 1.0f},
                {0.0f, 0.0f},
                {1.0f, 0.0f},

                {0.0f, 1.0f},
                {1.0f, 1.0f},
                {1.0f, 0.0f},
                {1.0f, 0.0f},
                {0.0f, 0.0f},
                {0.0f, 1.0f},
        };
    }
} // Render