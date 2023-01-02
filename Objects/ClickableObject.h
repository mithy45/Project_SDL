#ifndef CLICKABLE_OBJECT_H
#define CLICKABLE_OBJECT_H

#include <SDL.h>

class ClickableObject
{
    public:
        ClickableObject() = default;
        ~ClickableObject() = default;

        virtual void onMouseClick(SDL_MouseButtonEvent &mouse_button_event) = 0;

    protected:
        bool is_selected = false;
};
#endif