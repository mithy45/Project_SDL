#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

constexpr char sheep_male_path[] = "../assets/sheep_male.png";
constexpr char sheep_female_path[] = "../assets/sheep_female.png";
constexpr SDL_Color color_sheep_rectangle =  {0, 0, 255, 255};
constexpr std::initializer_list<GameProperty> sheep_properties = {SHEEP, CAN_SPAWN_SHEEP};

class Sheep : public Animal
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