#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <glm/glm.hpp>
#include "./transformationComponent.hpp"

#define Head 0 
#define Torso 1
#define Arm 2
#define Leg 3
#define unknown -1

enum ComponentType {Arm , Leg , Head , Torso , unknown};

class Component
{
    private:
        static int id=0;
        transformationComponent TC;
        ComponentType myType;

    public:
        Component(int sentType){
            switch(sentType){
                case Head : this->myType=Head;
                case Torso : this->myType=Torso;
                case Arm : this->myType=Arm;
                case Leg : this->myType=Leg;
                default: this->myType=unknown;

            }
            id++;
        }

        transformationComponent GetTransformationComp(){
            return this->TC;
        }

};

#endif