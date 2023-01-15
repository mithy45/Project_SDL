#ifndef SHEPHERD_DOG_H
#define SHEPHERD_DOG_H

#include "Animal.h"

constexpr char shepherd_dog_path[] = "../assets/shepherd_dog.png";
constexpr double distance_shepherddog_prey = 270.0;
constexpr SDL_Color color_shepherddog_rectangle = {0, 255, 255, 255};
constexpr std::initializer_list<GameProperty> shepherd_dog_properties = {SHEPHERD_DOG};
constexpr std::initializer_list<GameProperty> shepherd_dog_preys = {WOLF};

class ShepherdDog : public Animal, PredatorObject
{
    public:
        // Constructor && Destructor
        ShepherdDog(SDL_Renderer *window_renderer_ptr);
        ~ShepherdDog() = default;

        // Public override methods
        void onMouseClick(SDL_MouseButtonEvent &mouse_button_event) override;
        void onLiving() override;
        void interact(const std::shared_ptr<GameObject>& game_object) override;
        void onDying() override;
        void move() override;
        void render() override;

    private:
        bool is_hunting_at_point = false;
        int x_point;
        int y_point;
};
#endif