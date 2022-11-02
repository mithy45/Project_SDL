  // SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>


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
    void draw_color(SDL_Renderer *renderer_ptr, Uint8 r, Uint8 g, Uint8 b)
    {
        if (SDL_SetRenderDrawColor(renderer_ptr, r, g, b, SDL_ALPHA_OPAQUE) != 0)
            throw std::runtime_error("SDL_SetRenderDrawColor"
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

// Ground
Ground::Ground(SDL_Renderer *window_renderer_ptr, unsigned n_sheep, unsigned n_wolf)
{
    std::cout << "Constructor Ground" << std::endl;

    this->window_renderer_ptr = window_renderer_ptr;
    this->animals = std::vector<Animal*>();

    for (unsigned i = 0; i < n_sheep; ++i)
    {
        this->add_animal(new Sheep(sheep_path, this->window_renderer_ptr));
    }
    
    for (unsigned i = 0; i < n_wolf; ++i)
    {
        this->add_animal(new Wolf(wolf_path, this->window_renderer_ptr));
    }

    this->add_animal(new ShepherdDog(shepherd_dog_path, this->window_renderer_ptr));
}


// Delete all animals
Ground::~Ground()
{
    std::cout << "Destructor Ground" << std::endl;

    for (Animal* animal : this->animals)
    {
        delete animal;
    }
}


// Add an animal
void Ground::add_animal(Animal* a)
{
    this->animals.push_back(a);
}


// Move and draw animals
void Ground::update()
{
    // Fill a green to the renderer before img 
    draw_color(this->window_renderer_ptr, 0x00, 0xFF, 0x00);
    for (Animal* animal : this->animals)
    {
        animal->move();
        animal->draw();
    }
}

// Application
Application::Application(unsigned n_sheep, unsigned n_wolf)
{
    std::cout << "Constructor application" << std::endl;

    create_window_and_renderer(&this->window_ptr, &this->window_renderer_ptr);
    SDL_SetWindowPosition(this->window_ptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(this->window_ptr, title);

    this->ground_ptr = new Ground(this->window_renderer_ptr, n_sheep, n_wolf);
    this->playing = true;
}


Application::~Application()
{
    std::cout << "Destructor application" << std::endl;

    delete this->ground_ptr;

    // Destroy current renderer before window
    SDL_DestroyRenderer(this->window_renderer_ptr);
    SDL_DestroyWindow(this->window_ptr);
}


int Application::loop(unsigned period)
{
    std::cout << "loop" << std::endl;

    unsigned time = SDL_GetTicks() + period;

    Uint64 frame_start, frame_end, frequency;
    float capping_frame;

    // While we play and the current don't pass the timer (Miliseconds)
    while (this->playing && !SDL_TICKS_PASSED(SDL_GetTicks(), time))
    {
        frequency = SDL_GetPerformanceFrequency();
        frame_start = SDL_GetPerformanceCounter();

        // Delete all texture inside render
        SDL_RenderClear(this->window_renderer_ptr);

        this->handle_events();
        // Moving animals and draw them
        this->ground_ptr->update();

        // Refresh renderer
        SDL_RenderPresent(this->window_renderer_ptr);
        
        frame_end = SDL_GetPerformanceCounter();
        capping_frame = frame_delay - (1000.0f * (frame_end - frame_start) / frequency);
        
        // Capping frame to 60 FPS
        if (capping_frame > 0)
            SDL_Delay(capping_frame);

    }
    return 0;
}


void Application::handle_events()
{
    SDL_Event window_event;

    // While we play && handle current events
    while (this->playing && SDL_PollEvent(&window_event))
    {
        switch(window_event.type)
        {
            case SDL_QUIT:
                this->playing = false;
                break;
            default:
                break;
        }
    }
}
