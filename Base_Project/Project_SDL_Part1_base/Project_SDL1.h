// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0;
constexpr double frame_delay = 1000.f / frame_rate;
constexpr unsigned frame_width = 1400;
constexpr unsigned frame_height = 900;

constexpr unsigned frame_boundary = 100;

constexpr char title[] = "Project_SDL";
constexpr char sheep_path[] = "../../media/sheep.png";
constexpr char wolf_path[] = "../../media/wolf.png";
constexpr char shepherd_dog_path[] = "../../media/shepherd_dog.png";

// Helper function to initialize SDL
void init_sdl();
void close_sdl();

// Class inheriting from Animal
class Animal
{
  private:
    // The texture of the image loaded
    SDL_Texture *image_ptr;

  public:
    // Constructor && Destructor
    Animal(const std::string &file_path, SDL_Renderer *window_renderer_ptr);
    ~Animal();

    // Public methods
    // Draw the animal on the screen <-> window_renderer_ptr
    void draw();

    // Public virtual methods
    virtual void move(){};

  protected:
    // Non-owning ptr
    SDL_Renderer *window_renderer_ptr;

    // The rect of img (Pos x, y and height weight)
    SDL_Rect rect;
    int speed;
};


// Class inheriting from Animal
class Sheep : public Animal
{
  public:
    // Constructor && Destructor
    Sheep(const std::string &file_path, SDL_Renderer *window_renderer_ptr);
    ~Sheep(){};

    // Public override methods
    void move() override;
};

// Class inheriting from Animal
class Wolf : public Animal
{
  public:
    // Constructor && Destructor
    Wolf(const std::string &file_path, SDL_Renderer *window_renderer_ptr);
    ~Wolf(){};

    // Public override methods
    void move() override;
};


// Class inheriting from Animal
class ShepherdDog : public Animal
{
  public:
    // Constructor && Destructor
    ShepherdDog(const std::string &file_path, SDL_Renderer *window_renderer_ptr);
    ~ShepherdDog(){};

    void move() override;
};



// Class managing animals
class Ground
{
private:
    // Non-owning ptr
    SDL_Renderer *window_renderer_ptr;
    // Owning ptr
    std::vector<Animal *> animals;

public:
    // Constructor && Destructor
    Ground(SDL_Renderer *window_renderer_ptr, unsigned n_sheep, unsigned n_wolf);
    ~Ground();

    // Public methods
    // Add animal to vector
    void add_animal(Animal *a);
    // Moving animal and draw
    void update();
};

// Class for the game
class Application
{
private:
    // Owning ptr
    SDL_Window *window_ptr;
    SDL_Renderer *window_renderer_ptr;

    // Class managing animals and background of renderer
    Ground *ground_ptr;

public:
    // Constructor && Destructor
    Application(unsigned n_sheep, unsigned n_wolf);
    ~Application();

    // Public methods
    // Main loop of the application.
    // this ensures that the screen is updated at the correct rate.
    int loop(unsigned period);

private:    
    bool playing;

    // Handler events like click or quit game
    void handle_events();
};