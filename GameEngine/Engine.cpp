#include "Engine.h"

#include "../Animals/Sheep.h"
#include "../Animals/Wolf.h"
#include "../Animals/ShepherdDog.h"
#include "../PlayableCharacters/Shepherd.h"

#include <algorithm>
#include <iostream>

Engine::Engine(SDL_Renderer *window_renderer_ptr, unsigned n_sheep, unsigned n_wolf)
{
    this->window_renderer_ptr = window_renderer_ptr;
    this->game_objects = std::vector<std::shared_ptr<GameObject>>();

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> direction(1, 2);
    for (unsigned i = 0; i < n_sheep; ++i)
    {
        int random = direction(generator);

        std::string sheep_path;
        if (random == 1)
            sheep_path = sheep_male_path;
        else
            sheep_path = sheep_female_path;
        this->add_game_object(std::make_shared<Sheep>(this->window_renderer_ptr, sheep_path));
    }
    
    for (unsigned i = 0; i < n_wolf; ++i)
    {
        this->add_game_object(std::make_shared<Wolf>(this->window_renderer_ptr));
    }


    this->add_game_object(std::make_shared<Shepherd>(this->window_renderer_ptr));

    for (unsigned i = 0; i < 2; ++i)
    {
        this->add_game_object(std::make_shared<ShepherdDog>(this->window_renderer_ptr));
    }

    this->sheep_added_in_game = 0;
    this->mouse_event = false;
}


void Engine::add_game_object(std::shared_ptr<GameObject> game_object)
{
    this->game_objects.push_back(game_object);
}


void Engine::update()
{
    this->interact_game_objects();
    this->handle_interactions();

    for (std::shared_ptr<GameObject> game_object : this->game_objects)
    {
        game_object->move();
        game_object->render();
    }
}


unsigned Engine::get_nb_sheep()
{
    unsigned nb_sheep = 0;
    for (std::shared_ptr<GameObject> game_object : this->game_objects)
    {
        if (game_object->contains_property(SHEEP))
            nb_sheep += 1;
    }
    return nb_sheep;
}


void Engine::mouse_pressed(SDL_MouseButtonEvent mouse_button_event)
{
    this->mouse_event = true;
    this->mouse_button_event = mouse_button_event;
}


void Engine::interact_game_objects()
{
    for (std::shared_ptr<GameObject> game_object_1 : this->game_objects)
    {
        if (this->mouse_event)
            game_object_1->onMouseClick(this->mouse_button_event);
        game_object_1->onLiving();
        for (std::shared_ptr<GameObject> game_object_2 : this->game_objects)
        {
            if (game_object_1 != game_object_2
                && !game_object_1->contains_property(DEAD)
                && !game_object_2->contains_property(DEAD))
                game_object_1->interact(game_object_2);
        }
    }
    this->mouse_event = false;
}

void Engine::handle_interactions()
{
    this->game_objects.erase(
                            std::remove_if(this->game_objects.begin(), 
                                            this->game_objects.end(), 
                                            [](std::shared_ptr<GameObject> game_object) { 
                                                if (game_object->contains_property(DEAD))
                                                {
                                                    game_object->onDying();
                                                    return true;
                                                }
                                                return false;}),
                            this->game_objects.end());

    bool is_spawning_sheep = true;
    // We must iterate with index because the iterator becomes invalid until add element
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> direction(1, 2);
    for (size_t i = 0; i < this->game_objects.size(); ++i)
    {
        std::shared_ptr<GameObject> game_object = this->game_objects[i];
        if (game_object->contains_property(IS_SPAWNING_SHEEP))
        {
            if (is_spawning_sheep)
            {
                int random = direction(generator);

                std::string sheep_path;
                if (random == 1)
                    sheep_path = sheep_male_path;
                else
                    sheep_path = sheep_female_path;
                this->add_game_object(std::make_shared<Sheep>(this->window_renderer_ptr, sheep_path));
                is_spawning_sheep = false;
                this->sheep_added_in_game += 1;
            }
            else
                is_spawning_sheep = true;
            game_object->remove_property(IS_SPAWNING_SHEEP);
        }
    }
}