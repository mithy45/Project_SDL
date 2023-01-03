#include "Wolf.h"

Wolf::Wolf(SDL_Renderer *window_renderer_ptr) 
    : Animal(wolf_properties, 
            window_renderer_ptr, 
            wolf_path, 
            5, 
            4)
{

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

}

void Wolf::interact(std::shared_ptr<GameObject> game_object)
{
    if (game_object->contains_property(SHEEP) && this->collide(game_object))
        game_object->add_property(DEAD);
}


void Wolf::move()
{
    int width, height;
    renderer_width_height(this->window_renderer_ptr ,&width, &height);
    random_move(&this->rect, this->window_renderer_ptr, this->velocity_x, this->velocity_y, width, height);
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