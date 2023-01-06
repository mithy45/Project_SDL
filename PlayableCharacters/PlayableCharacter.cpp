#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(std::initializer_list<GameProperty> properties,
                        SDL_Renderer *window_renderer_ptr,
                        const std::string &file_path,
                        int velocity_x,
                        int velocity_y) 
                : GameObject(properties, 
                            window_renderer_ptr, 
                            file_path, velocity_x, 
                            velocity_y)
{

}

void PlayableCharacter::move()
{
    int width, height;
    renderer_width_height(this->window_renderer_ptr, &width, &height);

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
    {
        if (this->rect.y - this->velocity_y > 0)
            this->rect.y -= this->velocity_y;
    }
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
    {
        if (this->rect.y + this->velocity_y + this->rect.h <= height)
            this->rect.y += this->velocity_y;
    }
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
    {
        if (this->rect.x - this->velocity_x > 0)
            this->rect.x -= this->velocity_x;
    }
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
    {
        if (this->rect.x + this->velocity_x + this->rect.w <= width)
            this->rect.x += this->velocity_x;
    }
}