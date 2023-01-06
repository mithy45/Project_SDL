#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "Objects/GameObject.h"

class PlayableCharacter : public GameObject
{
    public:
        PlayableCharacter(std::initializer_list<GameProperty> properties,
                        SDL_Renderer *window_renderer_ptr,
                        const std::string &file_path,
                        int velocity_x,
                        int velocity_y);
        virtual ~PlayableCharacter(){};

        // Override method
        void move() override;
};
#endif