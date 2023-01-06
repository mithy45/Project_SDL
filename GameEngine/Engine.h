#ifndef ENGINE_H
#define ENGINE_H

#include "Objects/GameObject.h"

#include <SDL.h>

#include <memory>
#include <vector>

class Engine
{
    public:
        // Constructor && Destructor
        Engine(SDL_Renderer *window_renderer_ptr, unsigned n_sheep, unsigned n_wolf);
        ~Engine() = default;

        // Public methods
        void add_game_object(std::shared_ptr<GameObject> game_object);
        void update();

        unsigned get_nb_sheep();
        void mouse_pressed(SDL_MouseButtonEvent mouse_button_event);
        unsigned sheep_added_in_game;


    private:
        bool mouse_event;
        SDL_MouseButtonEvent mouse_button_event;

        SDL_Renderer *window_renderer_ptr;
        std::vector<std::shared_ptr<GameObject>> game_objects;

        // Private methods
        void interact_game_objects();
        void handle_interactions();
};
#endif