#ifndef MAIN_CHARACTER_HPP
#define MAIN_CHARACTER_HPP

#include "../components/transformationComponent.hpp"

struct mainCharacterEntity {
    struct tranformationComponent TC;
    int health = 100;
    int damage = 1;
};

#endif