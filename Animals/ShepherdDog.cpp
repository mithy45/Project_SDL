#include "ShepherdDog.h"

ShepherdDog::ShepherdDog(SDL_Renderer *window_renderer_ptr) 
            : Animal(shepherd_dog_properties, 
                    window_renderer_ptr, 
                    shepherd_dog_path, 
                    3, 
                    3), 
            PredatorObject(shepherd_dog_preys)
{

}

void ShepherdDog::onMouseClick(SDL_MouseButtonEvent &mouse_button_event)
{
    SDL_Rect rect = this->get_rect();
    int x = mouse_button_event.x;
    int y = mouse_button_event.y;
    if (mouse_button_event.button == SDL_BUTTON_LEFT)
    {
        if (is_point_in_rect(x, y, rect) && !this->is_selected)
            this->is_selected = true;
        else
            this->is_selected = false;
    }
    else if (mouse_button_event.button == SDL_BUTTON_RIGHT && this->is_selected)
    {
        this->is_hunting_at_point = true;
        this->x_point = x;
        this->y_point = y;
    }
}


void ShepherdDog::onLiving()
{

}


void ShepherdDog::interact(const std::shared_ptr<GameObject>& game_object)
{
    for (GameProperty property : this->prey_list)
    {
        if (game_object->contains_property(property))
        {
            if (this->collide(game_object))
            {
                game_object->add_property(DEAD);
                // It secures, not a must
                this->reset_prey();
            }
            else
                this->letsHunt(this->get_distance(game_object), game_object->get_rect());
            return;
        }
    }
}


void ShepherdDog::onDying()
{

}


void ShepherdDog::move()
{
    int width, height;
    renderer_width_height(this->window_renderer_ptr ,&width, &height);
    if (this->nearest_prey_distance <= distance_shepherddog_prey && this->nearest_prey_distance != 0)
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
    else if (this->is_hunting_at_point)
    {

        int width, height;
        renderer_width_height(this->window_renderer_ptr ,&width, &height);

        if (this->rect.x + this->rect.w < this->x_point + this->velocity_x)
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
        if (this->rect.y + this->rect.h < this->y_point + this->velocity_y)
        {
            if (this->rect.y + this->rect.h + this->velocity_y <= height)
                this->rect.y += this->velocity_y;
        }
        else
        {
            if (this->rect.y - this->velocity_y > 0)
                this->rect.y -= this->velocity_y;
        }

        if (is_point_in_rect(this->x_point, this->y_point, this->get_rect()))
            this->is_hunting_at_point = false;
    }
    else
        random_move(&this->rect, this->velocity_x, this->velocity_y, width, height);

    this->reset_prey();
}

void ShepherdDog::render()
{
    this->render_image();
    if (this->is_selected)
        this->render_rectangle(color_shepherddog_rectangle);
}