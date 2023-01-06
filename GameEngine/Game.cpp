#include "Game.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace
{
    // Create window and its renderer
    void create_window_and_renderer(SDL_Window **window_ptr, SDL_Renderer **renderer_ptr)
    {
        if(SDL_CreateWindowAndRenderer(frame_width,
                                        frame_height,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
                                        window_ptr,
                                        renderer_ptr) != 0)
            throw std::runtime_error("SDL_CreateWindowAndRenderer"
                                    + std::string(SDL_GetError()));
    }

    // Fill the screen
    void draw_color(SDL_Renderer *renderer_ptr, SDL_Color color)
    {
        if (SDL_SetRenderDrawColor(renderer_ptr, color.r, color.g, color.b, color.a) != 0)
            throw std::runtime_error("SDL_SetRenderDrawColor"
                                    + std::string(SDL_GetError()));
    }


    void render_clear(SDL_Renderer *renderer_ptr)
    {
        if (SDL_RenderClear(renderer_ptr) != 0)
            throw std::runtime_error("SDL_RenderClear"
                                    + std::string(SDL_GetError()));
    }
}


void init_sdl()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("SDL_Init"
                                + std::string(SDL_GetError()));

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("IMG_Init"
                                + std::string(IMG_GetError()));
}


void close_sdl()
{
    SDL_Quit();
    IMG_Quit();
}


Game::Game(unsigned n_sheep, unsigned n_wolf)
{
    create_window_and_renderer(&this->window_ptr, &this->window_renderer_ptr);
    SDL_SetWindowPosition(this->window_ptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(this->window_ptr, title);

    this->ground_ptr = std::make_shared<Engine>(this->window_renderer_ptr, n_sheep, n_wolf);
    this->nb_sheep = n_sheep;
}


Game::~Game()
{
    SDL_DestroyRenderer(this->window_renderer_ptr);
    SDL_DestroyWindow(this->window_ptr);
}


int Game::loop(unsigned period)
{
    this->playing = true;
    unsigned time = SDL_GetTicks() + period;

    Uint64 frame_start, frame_end, frequency;
    float capping_frame;

    while (this->playing && !SDL_TICKS_PASSED(SDL_GetTicks(), time))
    {
        frequency = SDL_GetPerformanceFrequency();
        frame_start = SDL_GetPerformanceCounter();

        draw_color(this->window_renderer_ptr, background_color);
        render_clear(this->window_renderer_ptr);

        this->handle_events();
        this->ground_ptr->update();

        SDL_RenderPresent(this->window_renderer_ptr);
        
        frame_end = SDL_GetPerformanceCounter();
        capping_frame = frame_delay - (1000.0f * (frame_end - frame_start) / frequency);
        if (capping_frame > 0)
            SDL_Delay(capping_frame);

    }

    unsigned current_nb_sheep = this->ground_ptr->get_nb_sheep();
    std::cout << "Il y a eu au maximum "
            << this->nb_sheep + this->ground_ptr->sheep_added_in_game << " moutons dont "
            << this->ground_ptr->sheep_added_in_game << " ajoutés en jeu."
            << std::endl;

    std::cout << "Il reste au total : " << current_nb_sheep << " moutons." << std::endl;
    std::cout << "Votre score est de : " 
            << (this->ground_ptr->sheep_added_in_game * 80) + (current_nb_sheep * 50) << std::endl;
    return 0;
}


void Game::handle_events()
{
    SDL_Event window_event;
    while (this->playing && SDL_PollEvent(&window_event))
    {
        switch(window_event.type)
        {
            case SDL_QUIT:
                this->playing = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->ground_ptr->mouse_pressed(window_event.button);
                break;
            default:
                break;
        }
    }
}
