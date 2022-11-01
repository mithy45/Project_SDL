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

class Animal {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  // todo: Attribute(s) to define its position
public:
  Animal(const std::string& file_path, SDL_Surface* window_surface_ptr){};
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~Animal(){}; // todo: Use the destructor to release memory and "clean up
               // behind you"

  void draw(){}; // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

  virtual void move(){}; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
};

// Insert here:
// class sheep, derived from animal
class Sheep : public Animal {
  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
};

// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

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