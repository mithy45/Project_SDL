#include "Wolf.h"

Wolf::Wolf(SDL_Renderer *window_renderer_ptr) 
    : Animal(wolf_properties, 
            window_renderer_ptr, 
            wolf_path, 
            5, 
            4),
    PredatorObject(wolf_preys),
    PreyObject(wolf_predators)
{
    this->time_to_die = TimerObject(timing_wolf_die);
    this->time_to_die.start();
}


void Wolf::onMouseClick(SDL_MouseButtonEvent &mouse_button_event)
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


void Wolf::onLiving()
{
    if (this->time_to_die.is_time_reached())
        this->add_property(DEAD);
}

void Wolf::interact(std::shared_ptr<GameObject> game_object)
{
    for (GameProperty property : this->prey_list)
    {
        if (game_object->contains_property(property))
        {
            if (this->collide(game_object))
            {
                game_object->add_property(DEAD);
                this->time_to_die.reset(timing_wolf_die * 2U);
                // It secures, not a must
                this->reset_prey();
            }
            else
                this->letsHunt(this->get_distance(game_object), game_object->get_rect());
            return;
        }
    }

    for (GameProperty property : this->predator_list)
    {
        if (game_object->contains_property(property))
        {
            this->letsRun(this->get_distance(game_object), game_object->get_rect());
            return;
        }
    }
}


void Wolf::move()
{
    int width, height;
    renderer_width_height(this->window_renderer_ptr ,&width, &height);
    if (this->nearest_prey_distance == 0.0 && this->nearest_predator_distance == 0.0)
    {
        random_move(&this->rect, this->window_renderer_ptr, this->velocity_x, this->velocity_y, width, height);
        return;
    }

    if (this->nearest_predator_distance <= distance_wolf_predator && this->nearest_predator_distance != 0)
    {
        // If the predator is on the right
        if (this->rect.x + this->rect.w < this->nearest_predator_rect.x)
        {
            if (this->rect.x - this->velocity_x > 0)
                this->rect.x -= this->velocity_x;
        }
        else
        {
            if (this->rect.x + this->rect.w <= width)
                this->rect.x += this->velocity_x;
        }
        // If the predator is on the bottom
        if (this->rect.y + this->rect.h < this->nearest_predator_rect.y)
        {
            if (this->rect.y - this->velocity_y > 0)
                this->rect.y -= this->velocity_y;
        }
        else
        {
            if (this->rect.y + this->rect.h <= height)
                this->rect.y += this->velocity_y;
        }
    }
    else
    {
        // If the prey is on the right
        if (this->rect.x + this->rect.w < this->nearest_prey_rect.x + this->velocity_x)
        {
            if (this->rect.x + this->rect.w + this->velocity_x <= width)
                this->rect.x += this->velocity_x;
        }
        else
        {
            if (this->rect.x - this->velocity_x > 0)
                this->rect.x -= this->velocity_x;
        }

        // If the prey is on the bottom
        if (this->rect.y + this->rect.h < this->nearest_prey_rect.y + this->velocity_y)
        {
            if (this->rect.y + this->rect.h + this->velocity_y <= height)
                this->rect.y += this->velocity_y;
        }
        else
        {
            if (this->rect.y - this->velocity_y > 0)
                this->rect.y -= this->velocity_y;
        }
    }

    this->reset_predator();
    this->reset_prey();
}


void Wolf::onDying()
{
    // std::cout << "Wolf: i'm dying" << std::endl;
}


void Wolf::render()
{
    this->render_image();
    if (this->is_selected)
        this->render_rectangle(color_wolf_rectangle);
}