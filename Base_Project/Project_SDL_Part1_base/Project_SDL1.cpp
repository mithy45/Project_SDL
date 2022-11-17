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
    // Create texture from img loaded given by args and fill the height and width of img
    SDL_Texture *create_texture_from(const std::string &path, SDL_Renderer *renderer_ptr, SDL_Rect *rect)
    {
        SDL_Surface *img_loaded = IMG_Load(path.c_str());
        if (!img_loaded)
            throw std::runtime_error("IMG_Load"
                                    + std::string(IMG_GetError()));
        rect->h = img_loaded->h;
        rect->w = img_loaded->w;
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_ptr, img_loaded);
        if (!texture)
            throw std::runtime_error("SDL_ConvertSurface"
                                    + std::string(IMG_GetError()));
        SDL_FreeSurface(img_loaded);
        return texture;
    }
    // Change the pos of rect
    void random_move(SDL_Rect *rect, SDL_Renderer *renderer_ptr, int speed)
    {
        int height, width;

        // Get the current renderer size
        if (SDL_GetRendererOutputSize(renderer_ptr, &width, &height) != 0)
            throw std::runtime_error("SDL_GetRendererOutputSize"
                                    + std::string(SDL_GetError()));
        
        std::cout << "width: " << width << "height: " << height << std::endl;

        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> direction(1, 4);
        int random = direction(generator);

        if (random == 1)
        {
            if (rect->y + speed + rect->h <= height)
                rect->y += speed;
        }
        else if (random == 2)
        {
            if (rect->y - speed + rect->h > 0)
                rect->y -= speed;
        }
        else if (random == 3)
        {
            if (rect->x + speed + rect->w <= width)
                rect->x += speed;
        }
        else if (random == 4)
        {
            if (rect->x - speed + rect->w > 0)
                rect->x -= speed;
        }
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

// Animal
Animal::Animal(const std::string &file_path, SDL_Renderer *window_renderer_ptr)
{
    std::cout << "Constructor animal" << std::endl;

    this->window_renderer_ptr = window_renderer_ptr;
    // Load img and get the texture for the renderer
    this->image_ptr = create_texture_from(file_path, this->window_renderer_ptr, &this->rect);
    

    // Random pos
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_width(this->rect.w, frame_width - this->rect.w);
    std::uniform_int_distribution<int> dis_height(this->rect.h, frame_height - this->rect.h);

    this->rect.x = dis_width(generator);
    this->rect.y = dis_height(generator);
}


Animal::~Animal()
{
    std::cout << "Desctructor animal" << std::endl;

    SDL_DestroyTexture(this->image_ptr);
}


// Copy the image loaded into the renderer
void Animal::draw()
{
    if (SDL_RenderCopy(this->window_renderer_ptr, this->image_ptr, NULL, &this->rect))
        throw std::runtime_error("SDL_RenderCopy"
                                + std::string(SDL_GetError()));
}


// Sheep
Sheep::Sheep(const std::string &file_path, SDL_Renderer *window_renderer_ptr) : Animal(file_path, window_renderer_ptr)
{
    this->speed = 2;
}


// Random move
void Sheep::move()
{
    random_move(&this->rect, this->window_renderer_ptr, this->speed);
}


// Wolf
Wolf::Wolf(const std::string &file_path, SDL_Renderer *window_renderer_ptr) : Animal(file_path, window_renderer_ptr)
{
    this->speed = 4;
}


// Random move
void Wolf::move()
{
    random_move(&this->rect, this->window_renderer_ptr, this->speed);
}


ShepherdDog::ShepherdDog(const std::string &file_path, SDL_Renderer *window_renderer_ptr) : Animal(file_path, window_renderer_ptr)
{
    this->speed = 3;
}


// Random move
void ShepherdDog::move()
{
    random_move(&this->rect, this->window_renderer_ptr, this->speed);
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
