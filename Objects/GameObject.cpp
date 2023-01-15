#include "GameObject.h"

constexpr unsigned frame_width = 1400;
constexpr unsigned frame_height = 900;

GameObject::GameObject(const std::initializer_list<GameProperty>& properties,
                    SDL_Renderer *window_renderer_ptr,
                    const std::string &file_path,
                    int velocity_x,
                    int velocity_y) : RenderedObject(window_renderer_ptr, file_path), MovingObject(velocity_x, velocity_y)
{
    this->properties = properties;
}


void GameObject::add_property(GameProperty property)
{
    this->properties.insert(property);
}


void GameObject::remove_property(GameProperty property)
{
    this->properties.erase(property);
}


bool GameObject::contains_property(GameProperty property)
{
    return this->properties.find(property) != this->properties.end();
}
