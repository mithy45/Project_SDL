#include "PredatorObject.h"

PredatorObject::PredatorObject(const std::initializer_list<GameProperty>& prey_list)
{
    this->prey_list = prey_list;
    this->reset_prey();
}


void PredatorObject::letsHunt(const double& prey_distance, const SDL_Rect& prey_rect)
{
    if (this->nearest_prey_distance == 0 
        || prey_distance < this->nearest_prey_distance)
    {
        this->nearest_prey_distance = prey_distance;
        this->nearest_prey_rect = prey_rect;
    }
}

void PredatorObject::reset_prey()
{
    this->nearest_prey_distance = 0;
    this->nearest_prey_rect = {0};
}