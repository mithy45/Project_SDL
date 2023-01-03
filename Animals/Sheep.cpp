#include "Sheep.h"

Sheep::Sheep(SDL_Renderer *window_renderer_ptr, 
            const std::string &sheep_path) 
    : Animal(sheep_properties, 
            window_renderer_ptr, 
            sheep_path, 
            3, 
            3)
{
    if (sheep_path == sheep_male_path)
        this->add_property(MALE);
    else
        this->add_property(FEMALE);
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
    
}

void Sheep::interact(std::shared_ptr<GameObject> game_object)
{
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
    int width, height;
    renderer_width_height(this->window_renderer_ptr ,&width, &height);
    random_move(&this->rect, this->window_renderer_ptr, this->velocity_x, this->velocity_y, width, height);
}


void Sheep::render()
{
    this->render_image();
    if (this->is_selected)
        render_rectangle(color_sheep_rectangle);
}