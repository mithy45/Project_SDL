#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

constexpr char wolf_path[] = "../assets/wolf.png";
constexpr uint32_t timing_wolf_die = 8U * 1000U;
constexpr double distance_wolf_predator = 255.0;
constexpr SDL_Color color_wolf_rectangle = {255, 0, 0, 255};
constexpr std::initializer_list<GameProperty> wolf_properties = {WOLF};
constexpr std::initializer_list<GameProperty> wolf_predators = {SHEPHERD_DOG};
constexpr std::initializer_list<GameProperty> wolf_preys = {SHEEP};

class Wolf : public Animal, public PredatorObject, public PreyObject
{
    public:
        // Constructor && Destructor
        Wolf(SDL_Renderer *window_renderer_ptr);
        ~Wolf() = default;

        // Override method
        void onMouseClick(SDL_MouseButtonEvent &mouse_button_event) override;
        void onLiving() override;
        void interact(std::shared_ptr<GameObject> game_object) override;
        void onDying() override;
        void move() override;
        void render() override;

    private:
        TimerObject time_to_die;
};
#endif