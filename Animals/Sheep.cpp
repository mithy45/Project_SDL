#include "Sheep.h"

#include <iostream>

Sheep::Sheep(SDL_Renderer *window_renderer_ptr, 
            const std::string &sheep_path) 
    : Animal(sheep_properties, 
            window_renderer_ptr, 
            sheep_path, 
            3, 
            3),
    PreyObject(sheep_predators)
{
    if (sheep_path == sheep_male_path)
        this->add_property(MALE);
    else
        this->add_property(FEMALE);

    this->time_to_sex = TimerObject(timing_sheep_sex);
}


void Sheep::onMouseClick(SDL_MouseButtonEvent &mouse_button_event)
{
    SDL_Rect rect = this->get_rect();
    int x = mouse_button_event.x;
    int y = mouse_button_event.y;
    if (is_point_in_rect(x, y, rect))
    {
        if (this->is_selected)
            this->is_selected = false;
        else
            this->is_selected = true;
    }
}


void Sheep::onLiving()
{
    if (!this->contains_property(CAN_SPAWN_SHEEP) && this->time_to_sex.paused)
        this->time_to_sex.start();

    if (this->time_to_sex.is_time_reached())
    {
        this->add_property(CAN_SPAWN_SHEEP);
        this->time_to_sex.paused = true;
    }   
}

void Sheep::interact(std::shared_ptr<GameObject> game_object)
{
    for (GameProperty property : this->predator_list)
    {
        if (game_object->contains_property(property))
        {
            this->letsRun(this->get_distance(game_object), game_object->get_rect());
            return;
        }
    }

    if (game_object->contains_property(SHEEP)
        && this->contains_property(CAN_SPAWN_SHEEP)
        && game_object->contains_property(CAN_SPAWN_SHEEP)
        && this->collide(game_object))
    {

        if (this->contains_property(MALE) && game_object->contains_property(FEMALE)
            || this->contains_property(FEMALE) && game_object->contains_property(MALE))
        {
            this->add_property(IS_SPAWNING_SHEEP);
            this->remove_property(CAN_SPAWN_SHEEP);
            game_object->add_property(IS_SPAWNING_SHEEP);
            game_object->remove_property(CAN_SPAWN_SHEEP);
        }
    }
}


void Sheep::onDying()
{

}

void Sheep::move()
{
    if (this->nearest_predator_distance == 0 || this->nearest_predator_distance >= distance_sheep_predator)
    {
        random_move(&this->rect, this->window_renderer_ptr, this->velocity_x, this->velocity_y);
        return;
    }

    int boost_x = 0, boost_y = 0;
    if (this->nearest_predator_distance <= distance_sheep_predator_boost)
    {
        boost_x = 2;
        boost_y = 2;
        this->is_selected = true;
    }
    else
    {
        this->is_selected = false;
    }
    int width, height;
    renderer_width_height(this->window_renderer_ptr ,&width, &height);

    // If the predator is on the right
    if (this->rect.x + this->rect.w < this->nearest_predator_rect.x)
    {
        if (this->rect.x - this->velocity_x - boost_x > 0)
            this->rect.x -= (this->velocity_x - boost_x);
    }
    else
    {
        if (this->rect.x + this->rect.w + boost_x <= width)
            this->rect.x += (this->velocity_x + boost_x);
    }
    // If the predator is on the bottom
    if (this->rect.y + this->rect.h < this->nearest_predator_rect.y)
    {
        if (this->rect.y - this->velocity_y - boost_y > 0)
            this->rect.y -= (this->velocity_y - boost_y);
    }
    else
    {
        if (this->rect.y + this->rect.h + boost_y <= height)
            this->rect.y += (this->velocity_y + boost_y);
    }

    this->reset_predator();
}


void Sheep::render()
{
    this->render_image();
    if (this->is_selected)
        render_rectangle(color_sheep_rectangle);
}