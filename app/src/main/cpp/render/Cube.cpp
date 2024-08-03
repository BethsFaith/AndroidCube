//
// Created by VeraTag on 03.08.2024.
//

#include "Cube.h"

namespace Render {
    Cube::Cube(const Settings& settings) : Primitive(36, settings) {
        std::vector<glm::vec3> position = getPosition();
        std::vector<glm::vec3> normals = settings.with_normals ? getNormals() : std::vector<glm::vec3>{};
        std::vector<glm::vec2> texture_coordinates = settings.with_texture_coords ? getTextureCoordinates()
                                                                                  : std::vector<glm::vec2>{};

        std::vector<Buffers::Vertex> vertices;

        if (settings.with_texture_coords && settings.with_normals) {
            for (int i{}; i < 6; ++i) {
                for (int j{}; j < 6; ++j) {
                    vertices.push_back(Buffers::Vertex{.position = position.at(i * 6 + j),
                            .normal = normals.at(i * 6 + j),
                            .tex_coords = texture_coordinates.at(i / 2 * 6 + j)});
                }
            }
        } else if (settings.with_texture_coords) {
            for (int i{}; i < 6; ++i) {
                for (int j{}; j < 6; ++j) {
                    vertices.push_back(Buffers::Vertex{.position = position.at(i * 6 + j),
                            .tex_coords = texture_coordinates.at(i / 2 * 6 + j)});
                }
            }
        } else if (settings.with_normals) {
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

    void Cube::draw() {
        Primitive::draw();

        glDrawArrays(GL_TRIANGLES, 0, vertexNumber);
    }

    void Cube::bindData(const unsigned int& bind_flag) {
        Primitive::bindData(bind_flag);

        int index = 0;

        Buffers::setVertexAttribute(index++,
                                    3,
                                    (int)(sizeof(Buffers::Vertex)),
                                    (void*)offsetof(Buffers::Vertex, position));
        if (settings.with_normals) {
            Buffers::setVertexAttribute(index++,
                                        3,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, normal));
        }
        if (settings.with_texture_coords) {
            Buffers::setVertexAttribute(index++,
                                        2,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, tex_coords));
        }
        if (settings.with_tangent) {
            Buffers::setVertexAttribute(index++,
                                        3,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, tangent));
        }
        if (settings.with_bitangent) {
            Buffers::setVertexAttribute(index++,
                                        3,
                                        (int)(sizeof(Buffers::Vertex)),
                                        (void*)offsetof(Buffers::Vertex, bitangent));
        }

        unbind();
    }

    std::vector<glm::vec3> Cube::getPosition() {
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

    std::vector<glm::vec3> Cube::getNormals() {
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

    std::vector<glm::vec2> Cube::getTextureCoordinates() {
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