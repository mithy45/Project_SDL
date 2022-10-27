// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

Application::Application(unsigned n_sheep, unsigned n_wolf)
{
  window_ptr_ = SDL_CreateWindow("Project_SDL_1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, frame_width, frame_height, SDL_WINDOW_SHOWN);
  if (!window_ptr_)
    throw std::runtime_error("Application(): SDL_CreateWindow could create the window" + std::string(SDL_GetError()));
  window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
  if (!window_surface_ptr_)
    throw std::runtime_error("Application(): SDL_GetWindowSurface could not get the windows surface" + std::string(SDL_GetError()));
}

void init()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

namespace
{
  // Defining a namespace without a name -> Anonymous workspace
  // Its purpose is to indicate to the compiler that everything
  // inside of it is UNIQUELY used within this source file.

  SDL_Surface *load_surface_for(const std::string &path,
                                SDL_Surface *window_surface_ptr)
  {

    // Helper function to load a png for a specific surface
    // See SDL_ConvertSurface
  }
} // namespace
