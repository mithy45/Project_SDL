#ifndef PREY_OBJECT_H
#define PREY_OBJECT_H

#include <SDL.h>
#include <set>

#include "GameProperty.h"

class PreyObject
{
    public:
        PreyObject(const std::initializer_list<GameProperty>& predator_list);
        ~PreyObject(){};

    protected:
        void letsRun(const double& predator_distance, const SDL_Rect& predator);
        void reset_predator();

        std::set<GameProperty> predator_list;

        double nearest_predator_distance;
        SDL_Rect nearest_predator_rect;
};
#endif