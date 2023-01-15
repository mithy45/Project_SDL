#include "PreyObject.h"

PreyObject::PreyObject(const std::initializer_list<GameProperty>& predator_list)
{
    this->predator_list = predator_list;
    this->reset_predator();
}


void PreyObject::letsRun(const double& predator_distance, const SDL_Rect& prey_rect)
{
    if (this->nearest_predator_distance == 0 
        || predator_distance < this->nearest_predator_distance)
    {
        this->nearest_predator_distance = predator_distance;
        this->nearest_predator_rect = prey_rect;
    }
}


void PreyObject::reset_predator()
{
    this->nearest_predator_distance = 0;
    this->nearest_predator_rect = {0};
}