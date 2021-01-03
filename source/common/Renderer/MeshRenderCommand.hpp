#ifndef MESH_RENDER_COMMAND_HPP
#define MESH_RENDER_COMMAND_HPP

#include <glm/glm.hpp>
#include <mesh/mesh.hpp>
#include <materialClass/material.hpp>

struct MeshRenderCommand
{
    Material *material;
    float depth;
    glm::mat4 transformation;
    gameTemp::Mesh *mesh;

    bool operator<(const MeshRenderCommand &other) const
    {
        const bool IsTransparent = material->getObjProp()->getBlend()->enabled;
        const bool isOtherTransparent = other.material->getObjProp()->getBlend()->enabled;

        // Let opaque objects be drawn before the transparent ones
        if (IsTransparent != isOtherTransparent)
            return IsTransparent < isOtherTransparent;

        // If both are transparent, sort from farthest to nearest
        else if (IsTransparent)
            return depth > other.depth;

        // If both are opaque, sort from nearest to farthest
        else
            return depth < other.depth;
    }
};

#endif