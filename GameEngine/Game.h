#ifndef GAME_H
#define GAME_H

#include "Engine.h"

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

// Defintions
constexpr double frame_rate = 60.0;
constexpr double frame_delay = 1000.f / frame_rate;
constexpr unsigned frame_width = 1400;
constexpr unsigned frame_height = 900;
constexpr unsigned frame_boundary = 100;
constexpr char title[] = "Project_SDL";

constexpr SDL_Color background_color = {0, 255, 0, 255};

void init_sdl();
void close_sdl();

// Class for the game
class Game
{
    public:
        // Constructor && Destructor
        Game(unsigned n_sheep, unsigned n_wolf);
        ~Game();

        // Public methods
        int loop(unsigned period);

    private:
        SDL_Window *window_ptr;
        SDL_Renderer *window_renderer_ptr;
        std::shared_ptr<Engine> ground_ptr;
        unsigned nb_sheep;
        bool playing = false;

        // Private method
        void handle_events();
};
#endif