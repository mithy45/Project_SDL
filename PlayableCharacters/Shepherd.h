#ifndef SHEPHERD_H
#define SHEPHERD_H

#include "PlayableCharacter.h"

constexpr char shepherd_path[] = "../assets/shepherd.png";
constexpr std::initializer_list<GameProperty> shepherd_properties = {SHEPHERD};
constexpr SDL_Color shepherd_rectangle_color = {0, 0, 0, 255};

class Shepherd : public PlayableCharacter
{
    public:
        Shepherd(SDL_Renderer *window_renderer_ptr);
        ~Shepherd() = default;

        // Override method
        void onMouseClick(SDL_MouseButtonEvent &mouse_button_event) override;
        void onLiving() override;
        void interact(const std::shared_ptr<GameObject>& game_object) override;
        void onDying() override;
        void render() override;
};
#endif