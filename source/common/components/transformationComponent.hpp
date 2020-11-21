#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include <glm/glm.hpp>

struct transformationComponent{
    int entityID = -1;
    glm::mat4 position;
};

#endif