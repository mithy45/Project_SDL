#ifndef ANIMAL_H
#define ANIMAL_H

#include "Objects/GameObject.h"

// Class inheriting from MovingObject
class Animal : public GameObject
{
    public:
        // Constructor && Destructor
        Animal(std::initializer_list<GameProperty> properties,
                SDL_Renderer *window_renderer_ptr,
                const std::string &file_path,
                int velocity_x,
                int velocity_y);
        virtual ~Animal(){};
};
#endif