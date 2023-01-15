#include "Animal.h"

Animal::Animal(const std::initializer_list<GameProperty>& properties,
                SDL_Renderer *window_renderer_ptr,
                const std::string &file_path,
                int velocity_x,
                int velocity_y) 
    : GameObject(properties, 
                window_renderer_ptr, 
                file_path, 
                velocity_x, 
                velocity_y)
{

}