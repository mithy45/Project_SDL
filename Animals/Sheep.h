#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

constexpr char sheep_male_path[] = "../assets/sheep_male.png";
constexpr char sheep_female_path[] = "../assets/sheep_female.png";
constexpr uint32_t timing_sheep_sex = 2U * 1000U;
constexpr double distance_sheep_predator = 220.0;
constexpr double distance_sheep_predator_boost = 112.0;
constexpr SDL_Color color_sheep_rectangle =  {0, 0, 255, 255};
constexpr std::initializer_list<GameProperty> sheep_properties = {SHEEP, CAN_SPAWN_SHEEP};
constexpr std::initializer_list<GameProperty> sheep_predators = {WOLF};

class Sheep : public Animal, PreyObject
{
    public:
        // Constructor && Destructor
        Sheep(SDL_Renderer *window_renderer_ptr, const std::string &file_path);
        ~Sheep() = default;

        // Override method
        void onMouseClick(SDL_MouseButtonEvent &mouse_button_event) override;
        void onLiving() override;
        void interact(std::shared_ptr<GameObject> game_object) override;
        void onDying() override;
        void move() override;
        void render() override;
};
#endif