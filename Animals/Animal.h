#ifndef ANIMAL_H
#define ANIMAL_H

#include "Objects/GameObject.h"
#include "Objects/PredatorObject.h"
#include "Objects/PreyObject.h"
#include "Objects/TimerObject.h"

#include <random>

namespace
{    
    void random_move(SDL_Rect *rect, int velocity_x, int velocity_y, int width, int height)
    {
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> direction(1, 4);
        int random = direction(generator);

        if (random == 1)
        {
            if (rect->y + velocity_y + rect->h <= height)
                rect->y += velocity_y;
        }
        else if (random == 2)
        {
            if (rect->y - velocity_y > 0)
                rect->y -= velocity_y;
        }
        else if (random == 3)
        {
            if (rect->x + velocity_x + rect->w <= width)
                rect->x += velocity_x;
        }
        else if (random == 4)
        {
            if (rect->x - velocity_x > 0)
                rect->x -= velocity_x;
        }
    }
}

// Class inheriting from MovingObject
class Animal : public GameObject
{
    public:
        // Constructor && Destructor
        Animal(const std::initializer_list<GameProperty>& properties,
                SDL_Renderer *window_renderer_ptr,
                const std::string &file_path,
                int velocity_x,
                int velocity_y);
        virtual ~Animal(){};
};
#endif