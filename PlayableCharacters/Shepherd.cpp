#include "Shepherd.h"

Shepherd::Shepherd(SDL_Renderer *window_renderer_ptr) 
        : PlayableCharacter(shepherd_properties, 
                            window_renderer_ptr, 
                            shepherd_path, 
                            5, 
                            5)
{

}

void Shepherd::onMouseClick(SDL_MouseButtonEvent &mouse_button_event)
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


void Shepherd::onLiving()
{

}


void Shepherd::interact(std::shared_ptr<GameObject> game_object)
{
    
}


void Shepherd::onDying()
{

}


void Shepherd::render()
{
    this->render_image();
    if (this->is_selected)
        this->render_rectangle(shepherd_rectangle_color);
}