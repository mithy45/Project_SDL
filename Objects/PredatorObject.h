#ifndef PREDATOR_OBJECT_H
#define PREDATOR_OBJECT_H

#include <SDL.h>
#include <set>

#include "GameProperty.h"

class PredatorObject
{
    public:
        PredatorObject(std::initializer_list<GameProperty> prey_list);
        ~PredatorObject(){};

        bool is_prey();

    protected:
        void letsHunt(double prey_distance, SDL_Rect prey_rect);
        void reset_prey();

        std::set<GameProperty> prey_list;

        double nearest_prey_distance;
        SDL_Rect nearest_prey_rect;
};
#endif